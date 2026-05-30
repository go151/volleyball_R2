#include "weapon.h"

DJI_MotorModule weapon_joint_motor;
DM_MotorModule weapon_collect_motor;
Weapon_Module Weapon;

float weapon_joint_motor_pid_param[PID_PARAMETER_NUM] = {2.5f,0.05f,0.1f,1,500.0f,10000.0f}; //定义了一个数组
