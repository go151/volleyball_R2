#include "lift.h"

Lift_Module Lift;
DJI_MotorModule balance_motor_left;
DJI_MotorModule balance_motor_right;
DM_MotorModule R2_lift_motor_left;
DM_MotorModule R2_lift_motor_right;
float balance_motor_left_pid_param[PID_PARAMETER_NUM] = {2.5f,0.05f,0.1f,1,500.0f,10000.0f}; 
float balance_motor_right_pid_param[PID_PARAMETER_NUM] = {2.5f,0.05f,0.1f,1,500.0f,10000.0f}; 
