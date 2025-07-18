/*
 *  ********************************************************************************
 *  STEP 1.
 *                      #####       Heading Comments        #####
 *
 *  File name   :   System_main.cpp
 *  Developer   :   DAE IL KIM
 *  History     :   Created -   2020/03/16  (DAE IL KIM)
 *  Description :   메인 루프 관리 Source 파일
 *  ********************************************************************************
*/

/*
 *  ********************************************************************************
 *  STEP 2.
 *              #####       include for include header file     #####
 *  ********************************************************************************
*/
#include "System_Header.h"
#include "System_timer.h"
#include "lab_shared.h"
#include "Ringbuffer.h"

/*
 *  ********************************************************************************
 *  STEP 3.
 *              #####       Function Prototypes     #####
 *  ********************************************************************************
*/
char * msg;
uint8_t receivedChar = 0;
bool newCommand = false;

typedef enum {
    FSM_STATE_INIT     = 0, // 초기화 상태 HOMING 동작
    FSM_STATE_IDLE     = 1, // 대기 상태
    FSM_STATE_OPERATE  = 2, // MOTOR ENABLE 상태 모터 동작
    FSM_STATE_POSITION = 3, // 모터 위치 제어 모드
    FSM_STATE_PRESSURE = 4, // 모터 압력 제어 모드
    FSM_STATE_ERROR    = 5, // 에러 상태
 
} FSM_State;

typedef enum {
    CMD_MOTOR_ENABLE  = 0, // 모터 ENABLE
    CMD_MODE_POSITION = 1,
    CMD_MODE_PRESSURE = 2,
    CMD_MOVE_TARGET   = 3, // 모터 이동, POSITION 및 PRESSURE 모드 모두 사용
    CMD_MOTOR_STOP    = 4, // 모터 STOP
    CMD_RESET         = 5,   // 시스템 리셋
    CMD_UNKNOWN       = 6, // 알 수 없는 명령
} CMD_Type;
//구조체는 전부 asdf.h로 가야함.

// 각 상태를 처리하고, 다음 상태를 반환하는 함수들을 미리 선언합니다.
FSM_State run_init_state(void);
FSM_State run_idle_state(CMD_Type cmd);
FSM_State run_operate_state(CMD_Type cmd);
FSM_State run_position_state(CMD_Type cmd);
FSM_State run_pressure_state(CMD_Type cmd);
FSM_State run_error_state(CMD_Type cmd);


CMD_Type GetCommand(void);
uint32_t    LedCtr      = 0;

#pragma DATA_SECTION(filter_out,"Cla1ToCpuMsgRAM");
float filter_out;

#pragma DATA_SECTION(filter_in,"Cla1ToCpuMsgRAM");
volatile float filter_in;

__interrupt void cla1Isr1(void)
{
    // Clear interrupt flags.
    Interrupt_clearACKGroup(INT_myCLA01_INTERRUPT_ACK_GROUP);
    CLA_clearTaskFlags(myCLA0_BASE, CLA_TASKFLAG_1);
    // Toggle LED1 at a rate of 1Hz.
    if (LedCtr++ >= 5000000) {
        GPIO_togglePin(myBoardLED0_GPIO);
        LedCtr = 0;
    }


}

__interrupt void 
INT_mySCI0_RX_ISR(void)
{

    receivedChar = SCI_readCharNonBlocking(SCIA_BASE);
    
    newCommand = true;
    ringbuffer_write(&rb, receivedChar);

    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

}

void System_main(void)
{
    FSM_State current_state = FSM_STATE_IDLE;
    FSM_State previous_state = FSM_STATE_ERROR;
    uint8_t cli_buffer[BUF_LEN];
    uint16_t cli_buffer_index = 0;

    ringbuffer_init(&rb);
    CLA_performSoftReset(myCLA0_BASE);
    CLA_enableTasks(myCLA0_BASE, CLA_TASKFLAG_1);
    while(1) {
        // 1. 외부에서 커맨드를 받습니다.
        CLA_forceTasks(myCLA0_BASE, CLA_TASKFLAG_1); // CLA Task 1을 강제로 실행

        // =====================================================================================
        // 블록 1: STATE 진입 시 단 한번 동작하는 것들
        // =====================================================================================
        if(current_state != previous_state){
            switch(current_state) {
                case FSM_STATE_INIT:
                    msg = "\r\nSystem : INITIALIZING...\0";
                    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 28);
                    break;
                case FSM_STATE_IDLE:
                    msg = "\r\nSystem : IDLE\0";
                    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 17);
                    break;
                case FSM_STATE_OPERATE:
                    msg = "\r\nSystem : OPERATING\0";
                    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 20);
                    break;
                case FSM_STATE_POSITION:
                    msg = "\r\nSystem : POSITION MODE\0";
                    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 25);
                    break;
                case FSM_STATE_PRESSURE:
                    msg = "\r\nSystem : PRESSURE MODE\0";
                    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 25);
                    break;
                case FSM_STATE_ERROR:
                    msg = "\r\nSystem : ERROR!\0";
                    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 19);
                    break;
                // 초기화 상태는 별도로 처리합니다.

            }previous_state = current_state;
        }
                // =====================================================================================
                // 블록 2: 상태 전이 로직
                // =====================================================================================
            //if ( newCommand == true)// newCommand -> ringbuffer boolean으로 새로운 커맨드 확인
            if (ringbuffer_read(&rb, &receivedChar)) // ringbuffer에서 커맨드 읽기
            {   
                SCI_writeCharBlockingNonFIFO(SCIA_BASE, receivedChar);
                cli_buffer[cli_buffer_index++] = receivedChar;
                if (receivedChar == '\n' || receivedChar == '\r') {
                    cli_buffer[cli_buffer_index - 1] = '\0'; // 문자열 종료
                    cli_buffer_index = 0; // 인덱스 초기화
                    newCommand = true; // 새로운 커맨드가 있다고 표시
                } else if (cli_buffer_index >= BUF_LEN) {
                    cli_buffer_index = 0; // 버퍼 오버플로우 방지
                }
                //newCommand = false;
                //CMD_Type cmd = GetCommand();
                //for fake command
                CMD_Type cmd = CMD_UNKNOWN; // 기본값은 알 수 없는 명령
                switch(current_state) {
                    case FSM_STATE_INIT:
                        current_state = run_init_state(); // 초기화 후 IDLE 상태로 전환
                        break;
                    case FSM_STATE_IDLE:
                        current_state = run_idle_state(cmd);
                        break;
                    case FSM_STATE_OPERATE:
                        current_state = run_operate_state(cmd);
                        break;
                    case FSM_STATE_POSITION:
                        current_state = run_position_state(cmd);
                        break;
                    case FSM_STATE_PRESSURE:
                        current_state = run_pressure_state(cmd);
                        break;
                    case FSM_STATE_ERROR:
                        current_state = run_error_state(cmd);
                        break;
                    // 초기화 상태는 별도로 처리합니다.

                }
            }

    }

}
FSM_State run_init_state(void)
{
    return FSM_STATE_IDLE;  // 초기화 후 IDLE 상태로 전환
}


FSM_State run_idle_state (CMD_Type cmd)
{
    if(cmd == CMD_MOTOR_ENABLE){
        
        return FSM_STATE_OPERATE;
    }
    else if (cmd == CMD_MOTOR_STOP) {
        // 모터 정지 명령이 오면 IDLE 상태로 전환
        return FSM_STATE_IDLE;
    }
    else if(cmd == CMD_RESET){

        return FSM_STATE_INIT;
    }

    return FSM_STATE_IDLE;
}

FSM_State run_operate_state (CMD_Type cmd)
{
    if(cmd == CMD_MOTOR_STOP){
        return FSM_STATE_IDLE;
    } 
    else if(cmd == CMD_RESET){
        return FSM_STATE_INIT;
    }
    else if(cmd == CMD_MODE_POSITION){
        return FSM_STATE_POSITION;
    }
    else if(cmd == CMD_MODE_PRESSURE){
        return FSM_STATE_PRESSURE;
    }
    return FSM_STATE_OPERATE;
}

FSM_State run_position_state(CMD_Type cmd)
{
    if(cmd == CMD_MOTOR_STOP){
        return FSM_STATE_IDLE; // 모터 정지 명령이 오면 IDLE 상태로 전환
    }
    else if(cmd == CMD_RESET){
        return FSM_STATE_INIT; // 리셋 명령이 오면 초기화 상태로 전환
    }
    else if(cmd == CMD_MOVE_TARGET){
        // 목표 위치로 이동하는 로직을 여기에 구현합니다.
        // 예시로 45도까지 이동한다고 가정합니다.
        moveMotorTo(45.0f, 10.0f, 5.0f);
        msg = "\r\nSystem : MOVING..\0";
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 21);

        return FSM_STATE_POSITION; // 이동 후에도 POSITION 상태 유지
    }
    
    return FSM_STATE_POSITION;
}

FSM_State run_pressure_state(CMD_Type cmd)
{
    if(cmd == CMD_MOTOR_STOP){
        return FSM_STATE_IDLE; // 모터 정지 명령이 오면 IDLE 상태로 전환
    }
    else if(cmd == CMD_RESET){
        return FSM_STATE_INIT; // 리셋 명령이 오면 초기화 상태로 전환
    }
    else if (cmd == CMD_MOVE_TARGET)
    {
        //L1AC_Control();
        return FSM_STATE_PRESSURE; // 이동 후에도 PRESSURE 상태 유지
    }
        
    return FSM_STATE_PRESSURE;
}

FSM_State run_error_state(CMD_Type cmd)
{
    if(cmd == CMD_RESET){
        return FSM_STATE_INIT; // 에러 상태에서 리셋 명령이 오면 초기화 상태로 전환
    }

    return FSM_STATE_ERROR;
}



CMD_Type GetCommand(void)
{
    uint8_t command = 0;

    msg = "\r\nEnter command (0: MOTOR_EN, 1: MODE_POS, 2: MODE_PRE 3: TARGET 4: STOP 5: RST): \0";
    SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 84);
    //receivedChar = SCI_readCharNonBlocking(SCIA_BASE);
    //interrupt 방식으로 수신된 문자를 처리해서 여기서 사용하지 않음.
        command = receivedChar - '0';
        switch(command) {
            case 0:
                //SCI_writeCharBlockingNonFIFO(SCIA_BASE, receivedChar);
                return CMD_MOTOR_ENABLE;
            case 1:
                //SCI_writeCharBlockingNonFIFO(SCIA_BASE, receivedChar);
                return CMD_MODE_POSITION;
            case 2:
                //SCI_writeCharBlockingNonFIFO(SCIA_BASE, receivedChar);
                return CMD_MODE_PRESSURE;
            case 3:
                //SCI_writeCharBlockingNonFIFO(SCIA_BASE, receivedChar);
                return CMD_MOVE_TARGET;
            case 4:
                //SCI_writeCharBlockingNonFIFO(SCIA_BASE, receivedChar);
                return CMD_MOTOR_STOP;
            case 5: 
                //SCI_writeCharBlockingNonFIFO(SCIA_BASE, receivedChar);
                return CMD_RESET;
            default:
                msg = "\r\nInvalid command. Defaulting to IDLE.\0";
                SCI_writeCharArray(SCIA_BASE, (uint16_t*)msg, 40);

                return CMD_UNKNOWN; // Default to stop if invalid input
        }

}

