#ifndef __KFS_H__
#define __KFS_H__

#include "structure.h"
#include "dji_motor.h"
#include "dm_motor.h"

/************************KFS抓取机构电机***********************/
#define KFS_LIFT_MOTOR_ID               0x03
#define KFS_LIFT_MOTOR_CMD_ID           KFS_LIFT_MOTOR_ID
#define KFS_LIFT_MOTOR_FEEDBACK_ID      KFS_LIFT_MOTOR_ID
#define KFS_LIFT_MOTOR_MASTER_ID        0x10

#define KFS_FLEX_MOTOR_ID               0x04
#define KFS_FLEX_MOTOR_CMD_ID           KFS_FLEX_MOTOR_ID
#define KFS_FLEX_MOTOR_FEEDBACK_ID      KFS_FLEX_MOTOR_ID
#define KFS_FLEX_MOTOR_MASTER_ID        0x10

/*******************************************************/

typedef struct _Kfs_Module{
    StructureModule super_struct; 
    
                             
    
    void (*Set_Pos)(struct _Kfs_Module *chassis);
    void (*Gravity_Calc)(struct _Kfs_Module *chassis);
} Kfs_Module;


extern Kfs_Module  Kfs;
extern DM_MotorModule kfs_lift_motor;  // kfs抓取机械臂抬升电机
extern DM_MotorModule kfs_flex_motor;  // kfs抓取机械臂伸缩电机

#endif
