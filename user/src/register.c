#include "register.h"
#include "global.h"
#include "motor.h"
#include "dji_motor.h"
#include "dm_motor.h"
#include "chassis.h"
#include "up.h"
//#include "up.h"

void Chassis_Init(void) 
{
    StructureModule_Create(&Chassis.super_struct, chassis);
    Chassis.super_struct.base.Init(&Chassis.super_struct.base);
    
    DJImotor_Create(&chassis_motor1, CHASSIS_MOTOR1_CMD_ID, CHASSIS_MOTOR1_FEEDBACK_ID, &hfdcan2, DJI_3508, SPEED, PID_POSITION, chassis_motor1_pid_param,NULL);
    DJImotor_Create(&chassis_motor2, CHASSIS_MOTOR2_CMD_ID, CHASSIS_MOTOR2_FEEDBACK_ID, &hfdcan2, DJI_3508, SPEED, PID_POSITION, chassis_motor2_pid_param,NULL);
    DJImotor_Create(&chassis_motor3, CHASSIS_MOTOR3_CMD_ID, CHASSIS_MOTOR3_FEEDBACK_ID, &hfdcan2, DJI_3508, SPEED, PID_POSITION, chassis_motor3_pid_param,NULL);
    DJImotor_Create(&chassis_motor4, CHASSIS_MOTOR4_CMD_ID, CHASSIS_MOTOR4_FEEDBACK_ID, &hfdcan2, DJI_3508, SPEED, PID_POSITION, chassis_motor4_pid_param,NULL);
    
    Chassis.super_struct.AddMotor(&Chassis.super_struct, &chassis_motor1.super_motor);
    Chassis.super_struct.AddMotor(&Chassis.super_struct, &chassis_motor2.super_motor);
    Chassis.super_struct.AddMotor(&Chassis.super_struct, &chassis_motor3.super_motor);
    Chassis.super_struct.AddMotor(&Chassis.super_struct, &chassis_motor4.super_motor); 
    
    Chassis.Chassis_Calc = Chassis_Calc;
    Chassis.Chassis_Stop = Chassis_Stop;
	//D
	StructureModule_Create(&ChassisD.super_struct, chassis);
    ChassisD.super_struct.base.Init(&ChassisD.super_struct.base);
    
    DJImotor_Create(&chassis_motor1D, CHASSIS_MOTOR1D_CMD_ID, CHASSIS_MOTOR1D_FEEDBACK_ID, &hfdcan3, DJI_2006,POSITION,PID_POSITION, chassis_motor1D_pid_param,chassis_motor1DP_pid_param);
    DJImotor_Create(&chassis_motor2D, CHASSIS_MOTOR2D_CMD_ID, CHASSIS_MOTOR2D_FEEDBACK_ID, &hfdcan3, DJI_2006,POSITION,PID_POSITION, chassis_motor2D_pid_param,chassis_motor2DP_pid_param);
    DJImotor_Create(&chassis_motor3D, CHASSIS_MOTOR3D_CMD_ID, CHASSIS_MOTOR3D_FEEDBACK_ID, &hfdcan3, DJI_2006,POSITION,PID_POSITION, chassis_motor3D_pid_param,chassis_motor3DP_pid_param);
    DJImotor_Create(&chassis_motor4D, CHASSIS_MOTOR4D_CMD_ID, CHASSIS_MOTOR4D_FEEDBACK_ID, &hfdcan3, DJI_2006,POSITION,PID_POSITION, chassis_motor4D_pid_param,chassis_motor4DP_pid_param);
    
    ChassisD.super_struct.AddMotor(&ChassisD.super_struct, &chassis_motor1D.super_motor);
    ChassisD.super_struct.AddMotor(&ChassisD.super_struct, &chassis_motor2D.super_motor);
    ChassisD.super_struct.AddMotor(&ChassisD.super_struct, &chassis_motor3D.super_motor);
    ChassisD.super_struct.AddMotor(&ChassisD.super_struct, &chassis_motor4D.super_motor); 
    
    ChassisD.Chassis_Calc = Chassis_Calc;
    ChassisD.Chassis_Stop = Chassis_Stop;

}

void up_Init(void)
{
   
	  DMmotor_Create(&DM2325[0],0x004,0,&hfdcan1,DM_2325,POSITION,PID_POSITION,DM2325_1_P_pid_param);
	  DMmotor_Create(&DM2325[1],0x001,1,&hfdcan1,DM_2325,POSITION,PID_POSITION,DM2325_2_P_pid_param);
    DMmotor_Create(&DM4310[0],0x005,0x10,&hfdcan1,DM_J4310,MIT,PID_POSITION,DM4310_1_P_pid_param);
	  DMmotor_Create(&DM4310[1],0x006,0x02,&hfdcan1,DM_J4310,MIT,PID_POSITION,DM4310_2_P_pid_param);
	  DMmotor_Create(&DM4310[2],0x007,0x20,&hfdcan1,DM_J4310,MIT,PID_POSITION,DM4310_3_P_pid_param);
	  DMmotor_Create_FOUR(&DM4310_FOUR[0],PID_POSITION,DM4310_1_P_pid_param,DM4310_1_S_pid_param);
	  DMmotor_Create_FOUR(&DM4310_FOUR[1],PID_POSITION,DM4310_2_P_pid_param,DM4310_2_S_pid_param);
	  DMmotor_Create_FOUR(&DM4310_FOUR[2],PID_POSITION,DM4310_3_P_pid_param,DM4310_3_S_pid_param);
																		 
}

//void Lift_Init(void)//升降电机初始化
//{
////    StructureModule_Create(&Lift.super_struct, lift);
////    Lift.super_struct.base.Init(&Lift.super_struct.base);
////    
////    DMmotor_Create(&R2_lift_motor_left, R2_LIFT_MOTOR_RIGHT_CMD_ID, R2_LIFT_MOTOR_LEFT_MASTER_ID, &hfdcan1, DM_J4310, MIT);
////    DMmotor_Create(&R2_lift_motor_right, R2_LIFT_MOTOR_RIGHT_CMD_ID, R2_LIFT_MOTOR_LEFT_MASTER_ID, &hfdcan1, DM_J4310, MIT);
////    DJImotor_Create(&balance_motor_left, BALANCE_MOTOR_LEFT_CMD_ID,BALANCE_MOTOR_LEFT_FEEDBACK_ID ,&hfdcan2, DJI_2006, SPEED, PID_POSITION, balance_motor_left_pid_param);
////    DJImotor_Create(&balance_motor_right, BALANCE_MOTOR_RIGHT_CMD_ID,BALANCE_MOTOR_RIGHT_FEEDBACK_ID ,&hfdcan2, DJI_2006, SPEED, PID_POSITION, balance_motor_right_pid_param);
////    
////    Lift.super_struct.AddMotor(&Lift.super_struct, &R2_lift_motor_left.super_motor);
////    Lift.super_struct.AddMotor(&Lift.super_struct, &R2_lift_motor_right.super_motor);
////    
////    R2_lift_motor_left.send_cmd(&R2_lift_motor_left,Motor_Enable);
////    R2_lift_motor_right.send_cmd(&R2_lift_motor_right,Motor_Enable);
//}

//void Weapon_Init(void)//武器电机初始化
//{
////    StructureModule_Create(&Weapon.super_struct, weapon);
////    Weapon.super_struct.base.Init(&Weapon.super_struct.base);
////    
////    DMmotor_Create(&weapon_collect_motor, WEAPON_COLLECT_MOTOR_CMD_ID, WEAPON_COLLECT_MOTOR_FEEDBACK_ID, &hfdcan2, DM_2325, MIT);
////    DJImotor_Create(&weapon_joint_motor, WEAPON_JOINT_MOTOR_CMD_ID,WEAPON_JOINT_MOTOR_FEEDBACK_ID ,&hfdcan2, DJI_2006, SPEED, PID_POSITION, weapon_joint_motor_pid_param);
//// 
////    Weapon.super_struct.AddMotor(&Weapon.super_struct, &weapon_collect_motor.super_motor);
////    Weapon.super_struct.AddMotor(&Weapon.super_struct, &weapon_joint_motor.super_motor);
////    
////    weapon_collect_motor.send_cmd(&weapon_collect_motor, Motor_Enable);
//}

void Structue_Init(void)//全部初始化
{
    Chassis_Init();
    HAL_Delay(5);

}
