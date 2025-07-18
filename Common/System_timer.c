

#include "System_timer.h"
#include "asdf.h"

Trajectory_Profile g_traj = {0}; // Trajectory 프로파일 구조체 초기화
float getMotorActualPosition(void) {return 0.0f;};
float test_timer1_val =0.0f;
/**
 * @brief 목표 각도까지의 사다리꼴 프로파일을 계산하고 초기화합니다.
 * @param new_target_angle 최종 목표 각도
 * @param max_v 최고 속도 (단위: units/sec)
 * @param accel 가속도 (단위: units/sec^2)
 */
void moveMotorTo(float new_target_angle, float max_v, float accel) {
    DINT;
    // 1. 기본 파라미터 설정
    g_traj.start_position = 0.0f; // 현재 모터 위치 읽기
    g_traj.final_target_position = new_target_angle;
    g_traj.total_distance = (g_traj.final_target_position - g_traj.start_position);
    g_traj.max_velocity = max_v;
    g_traj.acceleration = accel;

    if (g_traj.total_distance < 1e-6) { // 이동 거리가 매우 작으면 실행 안함
        g_traj.active = 0;
        return;
    }

    // 2. 최고 속도에 도달 가능한지 확인
    // v^2 = v0^2 + 2as  =>  v_max^2 = 2 * a * s_accel
    float distance_to_reach_max_v = (max_v * max_v) / accel;

    if (g_traj.total_distance < distance_to_reach_max_v) {
        // "삼각형" 프로파일 (최고 속도에 도달하지 못하고 바로 감속)
        g_traj.t_accel = (g_traj.total_distance / accel);
        g_traj.t_coast = 0.0f;
    } else {
        // "사다리꼴" 프로파일 (최고 속도로 등속 구간 존재)
        g_traj.t_accel = max_v / accel;
        float coast_distance = g_traj.total_distance - distance_to_reach_max_v;
        g_traj.t_coast = coast_distance / max_v;
    }

    g_traj.t_total = 2.0f * g_traj.t_accel + g_traj.t_coast; // 총 시간 = 가속시간 + 등속시간 + 감속시간(가속시간과 동일)

    // 3. Trajectory 활성화
    g_traj.elapsed_time = 0.0f;
    g_traj.current_target_position = g_traj.start_position;
    g_traj.active = 1;
    EINT;
}

//
// Step Pulse Generate Timer 나중에 DMA에서 발생예정
//
//__attribute__((ramfunc))
__interrupt void 
INT_myCPUTIMER0_ISR(void)
{
    
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
    //Do One_Step();
    if(FLAG_STEP_EN == 1)
    {
       motor_step_event(); //모터제어쪽에서 빌려와야할거같은데?
    }


}

//
// ADC 및 encoder READ? 둘다 interrupt로 빼야할듯
//
//__attribute__((ramfunc))
__interrupt void
INT_myCPUTIMER1_ISR(void)
{
    test_timer1_val += 0.001f; // 1ms 단위로 증가
    if (!g_traj.active) {
        return;
    }

    // 경과 시간 업데이트 (ISR 주기가 1ms = 0.001s 라고 가정)
    g_traj.elapsed_time += 0.001f;
    float t = g_traj.elapsed_time;

    // 이동 방향 (+1 또는 -1)
    float direction = (g_traj.final_target_position > g_traj.start_position) ? 1.0f : -1.0f;

    // 변수 로컬 복사
    float ta = g_traj.t_accel;
    float tv = g_traj.t_coast;
    float td = g_traj.t_total;
    float a = g_traj.acceleration;
    float vmax = ta * a; // 실제 도달 가능한 최고 속도

    float pos = 0.0f; // 이동 거리

    // ★★ 현재 시간에 따라 구간별 위치 계산 ★★
    if (t < ta) {
        // --- 1. 가속 구간 ---
        // s = 0.5 * a * t^2
        pos = 0.5f * a * t * t;

    } else if (t < ta + tv) {
        // --- 2. 등속 구간 ---
        // 가속구간 이동거리 + 등속구간 이동거리
        float pos_accel_end = 0.5f * a * ta * ta;
        pos = pos_accel_end + vmax * (t - ta);

    } else if (t < td) {
        // --- 3. 감속 구간 ---
        // 가속구간+등속구간 이동거리 + 감속구간 이동거리
        float pos_accel_end = 0.5f * a * ta * ta;
        float pos_coast_end = pos_accel_end + vmax * tv;
        float t_decel = t - (ta + tv); // 감속 시작 후 경과 시간
        // s = v0*t - 0.5*a*t^2
        pos = pos_coast_end + (vmax * t_decel - 0.5f * a * t_decel * t_decel);

    } else {
        // --- 4. 목표 도달 ---
        pos = g_traj.total_distance;
        g_traj.active = 0; // Trajectory 비활성화
    }

    // 최종 목표 위치 = 시작위치 + 방향 * 계산된 이동거리
    g_traj.current_target_position = g_traj.start_position + direction * pos;

}

//
// MRAC(L1AC) 및 모터 제어, 통신까지 담당중
//
//__attribute__((ramfunc))
__interrupt void
INT_myCPUTIMER2_ISR(void)
{


}

