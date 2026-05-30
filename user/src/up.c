#include "up.h"
#include "dm_motor.h"
#include "cmsis_os.h"
#include "remote_control.h"
DM_MotorModule DM4310[3];
DM_MotorModule_FOUR DM4310_FOUR[3];
DM_MotorModule DM2325[2];
#define MIT_ANGLE2 -0.150
#define MIT_ANGLE3 -0.143
#define MIT_ANGLE1 -0.156
#define MIT_KP 50
#define MIT_KD 0.8

float DM4310_1_P_pid_param[PID_PARAMETER_NUM] = {1.0f,0.0f,1.f,1.8f,5000.0f,10000.0f};     //KP,KI,KD,DEADBAND,LIMITINTEGRAL,LIMITOUTPUT
float DM4310_2_P_pid_param[PID_PARAMETER_NUM] = {1.0f,0.0f,1.f,1.8f,5000.0f,10000.0f};
float DM4310_3_P_pid_param[PID_PARAMETER_NUM] = {1.0f,0.0f,1.f,1.8f,5000.0f,10000.0f};
float DM4310_1_S_pid_param[PID_PARAMETER_NUM] = {0.7f,0.0f,0.5f,10,5000.0f,10000.0f};
float DM4310_2_S_pid_param[PID_PARAMETER_NUM] = {1.5f,0.0f,1.8f,10,10000.0f,10000.0f};
float DM4310_3_S_pid_param[PID_PARAMETER_NUM] = {1.5f,0.0f,1.8f,10,10000.0f,10000.0f};

float DM2325_1_P_pid_param[PID_PARAMETER_NUM] = {0.5f,0.05f,1.1f,0.5,500.0f,10000.0f};
float DM2325_2_P_pid_param[PID_PARAMETER_NUM] = {0.5f,0.05f,1.1f,0.5,500.0f,10000.0f};
float RightAndLeft=0,UpAndDown=0;
float height=10.0;
int flag3=0;
HAL_StatusTypeDef a1;
float v,tar=-1400.0;
float DM4310_FOUR_out[4];
void DMenable()
{
    DM_Motor_CMD(&DM2325[0],Motor_Enable);
	  osDelay(1);
	  DM_Motor_CMD(&DM2325[1],Motor_Enable);
	osDelay(1);
//	  DM_Motor_CMD(&DM4310[0],Motor_Enable);
//	osDelay(1);
//	  DM_Motor_CMD(&DM4310[1],Motor_Enable);
//	osDelay(1);
//	  DM_Motor_CMD(&DM4310[2],Motor_Enable);
//	osDelay(1);
	  
}

void DMdisable()
{
    DM_Motor_CMD(&DM2325[0],Motor_Disable);
	osDelay(1);
    DM_Motor_CMD(&DM2325[1],Motor_Disable);
	osDelay(1);
//	  DM_Motor_CMD(&DM4310[0],Motor_Disable);
//	osDelay(1);
//	  DM_Motor_CMD(&DM4310[1],Motor_Disable);
//	osDelay(1);
//	  DM_Motor_CMD(&DM4310[2],Motor_Disable);
//	osDelay(1);
	
}

void Upbabyup()
{
		RightAndLeft= MYdata_convert(RCctrl.CH1,240,1740,-50,50,10.0);
    UpAndDown= MYdata_convert(RCctrl.CH2,240,1740,0,50,10.0);

		DMset_posvel_data(&DM2325[0],RightAndLeft,7.0);
		DMset_posvel_data(&DM2325[1],UpAndDown,5.0);
}

void Catch()
{
 if(RCctrl.CH9>1000)
 {
	 switch(flag3)
	 {
						case 0:
//							     DMset_mit_data(&DM4310[1],-0.7,0.0,100,0.9,-5);
//		                osDelay(1);
//		               DMset_mit_data(&DM4310[2],-0.72,0.0,100,0.9,-5);
//		                osDelay(1);
//		               DMset_mit_data(&DM4310[0],-0.71,0.0,75,0.8,-5);
//		                osDelay(1);
//		        if(DM4310[0].position<=-0.6&&DM4310[1].position<=-0.6&&DM4310[2].position<=-0.6)
							
		 				DM4310_FOUR_out[0]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[0],tar)*2.5;
						DM4310_FOUR_out[1]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[1],tar)*2.5;
						DM4310_FOUR_out[2]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[2],tar)*2.5;
						DMset_motor_data_FOUR(&hfdcan1,0x4fe,-DM4310_FOUR_out[0],DM4310_FOUR_out[1],DM4310_FOUR_out[2],0 );
		        if(DM4310_FOUR[0].total_angle<=-1300&&DM4310_FOUR[1].total_angle<=-1300&&DM4310_FOUR[2].total_angle<=-1300)
						 
		          flag3=1;
							break;
						case 1:
//							     DMset_mit_data(&DM4310[0],0.1,0.0,10,MIT_KD,-1);
//						       osDelay(1);
//		               DMset_mit_data(&DM4310[1],0,0.0,10,MIT_KD,-1);
//						       osDelay(1);
//		               DMset_mit_data(&DM4310[2],0,0.0,10,MIT_KD,-1);
//						       osDelay(1);
		 				DM4310_FOUR_out[0]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[0],-200)*0.8;
						DM4310_FOUR_out[1]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[1],-200)*0.8;
						DM4310_FOUR_out[2]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[2],-200)*0.8;
            DMset_motor_data_FOUR(&hfdcan1,0x4fe,-DM4310_FOUR_out[0],DM4310_FOUR_out[1],DM4310_FOUR_out[2],0 );						
							break;
						


//						case 2:DMset_mit_data(&DM4310[0],MIT_ANGLE1,0.0,MIT_KP,MIT_KD,-2);
//		                osDelay(1);
//		               DMset_mit_data(&DM4310[1],MIT_ANGLE2,0.0,MIT_KP,MIT_KD,-2);
//		 osDelay(1);
//		               DMset_mit_data(&DM4310[2],MIT_ANGLE3,0.0,MIT_KP,MIT_KD,-2);
//osDelay(1);flag3++;break;
//						case 1:DMset_mit_data(&DM4310[1],MIT_ANGLE1,0.0,MIT_KP,MIT_KD,-2);
//		                osDelay(1);
//		               DMset_mit_data(&DM4310[0],MIT_ANGLE1,0.0,MIT_KP,MIT_KD,-2);
//		 osDelay(1);
//		               DMset_mit_data(&DM4310[2],MIT_ANGLE3,0.0,MIT_KP,MIT_KD,-2);
//osDelay(1);flag3++;break;
//						case 0:DMset_mit_data(&DM4310[2],MIT_ANGLE3,0.0,MIT_KP,MIT_KD,-2);
//		                osDelay(1);
//		               DMset_mit_data(&DM4310[1],MIT_ANGLE2,0.0,MIT_KP,MIT_KD,-2);
//		 osDelay(1);
//		               DMset_mit_data(&DM4310[0],MIT_ANGLE1,0.0,MIT_KP,MIT_KD,-2);
//osDelay(1);flag3++;break;
//						case 5:DMset_mit_data(&DM4310[0],MIT_ANGLE1,0.0,MIT_KP,MIT_KD,-2);
//		                osDelay(1);
//		               DMset_mit_data(&DM4310[2],MIT_ANGLE3,0.0,MIT_KP,MIT_KD,-2);
//		 osDelay(1);
//		               DMset_mit_data(&DM4310[1],MIT_ANGLE3,0.0,MIT_KP,MIT_KD,-2);
//osDelay(1);flag3++;break;
//						case 4:DMset_mit_data(&DM4310[1],MIT_ANGLE2,0.0,MIT_KP,MIT_KD,-2);
//		                osDelay(1);
//		               DMset_mit_data(&DM4310[2],MIT_ANGLE3,0.0,MIT_KP,MIT_KD,-2);
//		 osDelay(1);
//		               DMset_mit_data(&DM4310[0],MIT_ANGLE1,0.0,MIT_KP,MIT_KD,-2);
//osDelay(1);flag3++; break;
//						case 3:DMset_mit_data(&DM4310[2],MIT_ANGLE3,0.0,MIT_KP,MIT_KD,-2);
//		                osDelay(1);
//		               DMset_mit_data(&DM4310[0],MIT_ANGLE1,0.0,MIT_KP,MIT_KD,-2);
//		 osDelay(1);
//		               DMset_mit_data(&DM4310[1],MIT_ANGLE2,0.0,MIT_KP,MIT_KD,-2);
//osDelay(1);flag3++;break;

}
//	 if(flag3==6) flag3=0;
 	 
 }else 
 {flag3=0;
 		 				DM4310_FOUR_out[0]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[0],-200);
						DM4310_FOUR_out[1]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[1],-200);
						DM4310_FOUR_out[2]=Motor_PID_Calculate_FOUR(&DM4310_FOUR[2],-200);
            DMset_motor_data_FOUR(&hfdcan1,0x4fe,-DM4310_FOUR_out[0],DM4310_FOUR_out[1],DM4310_FOUR_out[2],0 );
 }
	
	 
	 
	 
	 
}















