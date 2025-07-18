/*
 *  ********************************************************************************
 *  STEP 1.
 *                      #####       Heading Comments        #####
 *
 *  File name   :   System_Header.h
 *  Developer   :   DAE IL KIM
 *  History     :   Created -   2020/03/16  (DAE IL KIM)
 *  Description :   전역에서 쓰이는 Header를 Link한 Header 파일
 *  ********************************************************************************
*/

/*
 *  ********************************************************************************
 *  STEP 2.
 *                      #####       HEADER_FILE_ID      #####
 *  ********************************************************************************
*/

#ifndef INCLUDE_COMMON_SYSTEM_HEADER_H_
#define INCLUDE_COMMON_SYSTEM_HEADER_H_

/*
 *  ********************************************************************************
 *  STEP 3.
 *              #####       Header File Include Declaration     #####
 *  ********************************************************************************
*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#include "driverlib.h"
#include "device.h"
#include "board.h"


/*
 *  ********************************************************************************
 *  STEP 4.
 *                      #####       FUNCTION declaration      #####
 *  ********************************************************************************
*/

/*
 *  name        :   System_main
 *  description :   Main 무한 루프 프로세스 함수
*/
void System_main(void);

#endif /* INCLUDE_COMMON_SYSTEM_HEADER_H_ */

