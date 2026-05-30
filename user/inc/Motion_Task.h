#ifndef __MOTION_TASK_H__
#define __MOTION_TASK_H__
#include <stdbool.h>
#include "main.h"

typedef enum{
    motion_none,
    weapon_collect,
    kfs_collect,
    R2_lift,
}Motion_mode;

typedef enum{
    remote_control,
    master_control
}Control_mode;                                                              

typedef enum{
    remote_none,
    chassis_move,
    motion_switch,
    cowork
}Remote_mode;


extern Motion_mode motion_mode;
extern Control_mode control_mode;
extern Remote_mode remote_mode;
extern volatile bool chassis_is_ready;
extern volatile bool is_homed[4];
extern uint8_t mode1;
#endif
