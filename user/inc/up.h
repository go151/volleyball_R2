#ifndef __UP_H__
#define __UP_H__
#include "dm_motor.h"

extern float DM4310_1_P_pid_param[PID_PARAMETER_NUM] ;
extern float DM4310_2_P_pid_param[PID_PARAMETER_NUM] ;
extern float DM4310_3_P_pid_param[PID_PARAMETER_NUM] ;
extern float DM2325_1_P_pid_param[PID_PARAMETER_NUM] ;
extern float DM2325_2_P_pid_param[PID_PARAMETER_NUM] ;
extern float DM4310_1_P_pid_param[PID_PARAMETER_NUM];    //KP,KI,KD,DEADBAND,LIMITINTEGRAL,LIMITOUTPUT
extern float DM4310_2_P_pid_param[PID_PARAMETER_NUM];
extern float DM4310_3_P_pid_param[PID_PARAMETER_NUM];
extern float DM4310_1_S_pid_param[PID_PARAMETER_NUM];
extern float DM4310_2_S_pid_param[PID_PARAMETER_NUM];
extern float DM4310_3_S_pid_param[PID_PARAMETER_NUM];
void DMenable();
void DMdisable();
void Upbabyup();
void Catch();
#endif
