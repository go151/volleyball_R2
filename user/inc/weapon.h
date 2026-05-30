#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "structure.h"
#include "dji_motor.h"
#include "dm_motor.h"

/************************R2Ì§Éýµç»ú***********************/
#define WEAPON_COLLECT_MOTOR_ID           0x04
#define WEAPON_COLLECT_MOTOR_CMD_ID       WEAPON_COLLECT_MOTOR_ID
#define WEAPON_COLLECT_MOTOR_FEEDBACK_ID  WEAPON_COLLECT_MOTOR_ID
#define WEAPON_COLLECT_MOTOR_MASTER_ID    0x10

#define WEAPON_JOINT_MOTOR_ID           0x03                                                                                                                                                                        
#define WEAPON_JOINT_MOTOR_CMD_ID       0x200
#define WEAPON_JOINT_MOTOR_FEEDBACK_ID  0x200 + WEAPON_JOINT_MOTOR_ID

extern float weapon_joint_motor_pid_param[PID_PARAMETER_NUM];
/*******************************************************/

typedef struct _Weapon_Module{
    StructureModule super_struct; 
    
                             
} Weapon_Module;

extern Weapon_Module Weapon;
extern DJI_MotorModule weapon_joint_motor;
extern DM_MotorModule weapon_collect_motor;

#endif
