#include "Step_motor.h"


void motor_step_event(void)
{
    // This function is called to handle step motor events.
    // Implement the logic for handling step motor events here.
    // For example, you might want to check the current state of the motor,
    // update its position, or trigger a step action based on a timer or input signal.
    
    if (motor_is_ready()) {
        One_Step();
    }
}

void One_Step(void)
{
    GPIO_writePin(STEP, HIGH);
    DEVICE_DELAY_US(2); // Delay for 1 second (1000000 microseconds)
    GPIO_writePin(STEP, LOW);
}

bool motor_is_ready(void)
{
    // Check if the motor is ready to take a step.
    // This could involve checking a status flag or a condition.
    // Return true if the motor is ready, false otherwise.
    
    // Placeholder for actual readiness check logic
    return true; // Assume motor is always ready for this example
}

