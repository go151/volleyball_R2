#ifndef __CHASSIS_H__
#define __CHASSIS_H__

#include "global.h"
#include "structure.h"
#include "dji_motor.h"
#include "dm_motor.h"
#include "remote_control.h"
#include "master_control.h"

/************************底盘电机***********************/
//左前
#define CHASSIS_MOTOR1_ID          0x05
#define CHASSIS_MOTOR1_CMD_ID      0x1FF
#define CHASSIS_MOTOR1_FEEDBACK_ID 0x200 + CHASSIS_MOTOR1_ID

//右前
#define CHASSIS_MOTOR2_ID          0x06
#define CHASSIS_MOTOR2_CMD_ID      0x1FF
#define CHASSIS_MOTOR2_FEEDBACK_ID 0x200 + CHASSIS_MOTOR2_ID

//右后
#define CHASSIS_MOTOR3_ID          0x07
#define CHASSIS_MOTOR3_CMD_ID      0x1FF
#define CHASSIS_MOTOR3_FEEDBACK_ID 0x200 + CHASSIS_MOTOR3_ID

//左后
#define CHASSIS_MOTOR4_ID          0x08
#define CHASSIS_MOTOR4_CMD_ID      0x1FF
#define CHASSIS_MOTOR4_FEEDBACK_ID 0x200 + CHASSIS_MOTOR4_ID


/***********************D*底盘电机*D**********************/
//左前PA0
#define CHASSIS_MOTOR1D_ID          0x01
#define CHASSIS_MOTOR1D_CMD_ID      0x200
#define CHASSIS_MOTOR1D_FEEDBACK_ID 0x200 + CHASSIS_MOTOR1D_ID
					  
//右前    PA2            
#define CHASSIS_MOTOR2D_ID          0x02
#define CHASSIS_MOTOR2D_CMD_ID      0x200
#define CHASSIS_MOTOR2D_FEEDBACK_ID 0x200 + CHASSIS_MOTOR2D_ID
					  
//右后  PE13              
#define CHASSIS_MOTOR3D_ID          0x03
#define CHASSIS_MOTOR3D_CMD_ID      0x200
#define CHASSIS_MOTOR3D_FEEDBACK_ID 0x200 + CHASSIS_MOTOR3D_ID
					  
//左后   PE9             
#define CHASSIS_MOTOR4D_ID          0x04
#define CHASSIS_MOTOR4D_CMD_ID      0x200
#define CHASSIS_MOTOR4D_FEEDBACK_ID 0x200 + CHASSIS_MOTOR4D_ID

extern float chassis_motor1_pid_param[PID_PARAMETER_NUM];   
extern float chassis_motor2_pid_param[PID_PARAMETER_NUM];
extern float chassis_motor3_pid_param[PID_PARAMETER_NUM];
extern float chassis_motor4_pid_param[PID_PARAMETER_NUM];

extern float chassis_motor1D_pid_param[PID_PARAMETER_NUM]; 
extern float chassis_motor2D_pid_param[PID_PARAMETER_NUM];
extern float chassis_motor3D_pid_param[PID_PARAMETER_NUM];
extern float chassis_motor4D_pid_param[PID_PARAMETER_NUM];

extern float chassis_motor1DP_pid_param[PID_PARAMETER_NUM]; 
extern float chassis_motor2DP_pid_param[PID_PARAMETER_NUM];
extern float chassis_motor3DP_pid_param[PID_PARAMETER_NUM];
extern float chassis_motor4DP_pid_param[PID_PARAMETER_NUM];

/*******************************************************/


typedef struct{
    float Vx;
    float Vy;
    float Vw;
    float Accel;
    float wheel_out[4];   // 驱动轮目标速度（RPM 或 rad/s）

}Chassis_Param;

typedef struct _Chassis_Module{
    StructureModule super_struct; 
    
    Chassis_Param param;                             
    
    void (*Chassis_Calc)(struct _Chassis_Module *chassis,struct _Chassis_Module *chassisD);
    void (*Chassis_Stop)(struct _Chassis_Module *chassis);
} Chassis_Module;

extern Chassis_Module Chassis;
extern DJI_MotorModule chassis_motor1;  // （左前）
extern DJI_MotorModule chassis_motor2;  // （右前）
extern DJI_MotorModule chassis_motor3;  // （左后）
extern DJI_MotorModule chassis_motor4;  // （右后）

extern Chassis_Module ChassisD;
extern DJI_MotorModule chassis_motor1D;  // （左前）
extern DJI_MotorModule chassis_motor2D;  // （右前）
extern DJI_MotorModule chassis_motor3D;  // （左后）
extern DJI_MotorModule chassis_motor4D;  // （右后）


extern float target_angle_rad[4];
extern float current_angle_rad[4];
extern float angle_diff[4] ;
extern volatile bool is_homed[4] ;
extern volatile bool chassis_is_ready ;
extern uint8_t mode1;
// 函数声明
void usbdata_get();
void Chassis_Calc(Chassis_Module *chassis,Chassis_Module *chassisD);
void Chassis_Stop(Chassis_Module *chassis);
void runbabyrun(void);
float ChangeAngle(float angle);
void Chassis_Homing_Routine(void);
void P_Chassis_Calc(Chassis_Module *chassis,Chassis_Module *chassisD);
#endif
