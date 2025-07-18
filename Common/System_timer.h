
#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include "System_Header.h"
#include "Step_motor.h"

//test for Trajectory
typedef struct {
    volatile uint8_t active;

    // Profile 파라미터
    float max_velocity;
    float acceleration;

    // 계산된 시간 변수
    float t_accel;
    float t_coast;
    float t_total;

    float start_position;
    float final_target_position;
    float total_distance;

    float current_target_position;
    float current_target_velocity;

    float elapsed_time;

} Trajectory_Profile;
extern Trajectory_Profile g_traj;
extern float test_timer1_val;

void moveMotorTo(float new_target_angle, float max_v, float accel);



#endif // SYSTEM_TIMER_H
