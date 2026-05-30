#include "chassis.h"
#include <math.h>
#include "remote_control.h"
#include "bsp_can.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "usbd_cdc_if.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
#define CHASSIS_STEER_GEAR_RATIO  7.0f   // 电机:轮子减速比
// 轮距参数
#define CHASSIS_HALF_LENGTH  0.50f  // L: 从前到后中心距离的一�?
#define CHASSIS_HALF_WIDTH   0.50f  // W: 从左到右中心距离的一�?
#define ABS(x)  ((x) >= 0? (x) : -(x))//绝对值函�?
Chassis_Module Chassis;
Chassis_Module ChassisD;
DJI_MotorModule chassis_motor1;  // （左前）
DJI_MotorModule chassis_motor2;  // （右前）
DJI_MotorModule chassis_motor3;  // （左后）
DJI_MotorModule chassis_motor4;  // （右后）

DJI_MotorModule chassis_motor1D;  // （左前）
DJI_MotorModule chassis_motor2D;  // （右前）
DJI_MotorModule chassis_motor3D;  // （左后）
DJI_MotorModule chassis_motor4D;  // （右后）

float chassis_motor1_pid_param[PID_PARAMETER_NUM] = {4.f, 0.1f, 0.5f, 10, 500.0f, 8000.0f};     //KP,KI,KD,DEADBAND,LIMITINTEGRAL,LIMITOUTPUT
float chassis_motor2_pid_param[PID_PARAMETER_NUM] = {4.f, 0.1f, 0.5f, 10, 500.0f, 8000.0f};
float chassis_motor3_pid_param[PID_PARAMETER_NUM] = {4.f, 0.1f, 0.5f, 10, 500.0f, 8000.0f};
float chassis_motor4_pid_param[PID_PARAMETER_NUM] = {4.f, 0.1f, 0.5f, 10, 500.0f, 8000.0f};

float chassis_motor1D_pid_param[PID_PARAMETER_NUM] = {0.6f, 0.0043f, 10.0f, 10, 5000.0f,30000.0f};     //KP,KI,KD,DEADBAND,LIMITINTEGRAL,LIMITOUTPUT
float chassis_motor2D_pid_param[PID_PARAMETER_NUM] = {0.6f, 0.0043f, 10.0f, 10, 5000.0f,30000.0f};
float chassis_motor3D_pid_param[PID_PARAMETER_NUM] = {0.6f, 0.0043f, 10.0f, 10, 5000.0f,30000.0f};
float chassis_motor4D_pid_param[PID_PARAMETER_NUM] = {0.6f, 0.0043f, 10.0f, 10, 5000.0f,30000.0f};
																																											
//位置环pid参数
float chassis_motor1DP_pid_param[PID_PARAMETER_NUM] = {0.6f,0.0f,20.0f,10,5000.0f,30000.0f};     //KP,KI,KD,DEADBAND,LIMITINTEGRAL,LIMITOUTPUT
float chassis_motor2DP_pid_param[PID_PARAMETER_NUM] = {0.6f,0.0f,20.0f,10,5000.0f,30000.0f};
float chassis_motor3DP_pid_param[PID_PARAMETER_NUM] = {0.6f,0.0f,20.0f,10,5000.0f,30000.0f};
float chassis_motor4DP_pid_param[PID_PARAMETER_NUM] = {0.6f,0.0f,20.0f,10,5000.0f,30000.0f};

float Vx;
float Vy;
float Vw;
int16_t raw_vx ;
int16_t raw_vy ;
int16_t raw_vw ;
float k=1;
float target_angle_rad[4];
float target_angle_rad_change[4];
float current_angle_rad[4];
float angle_diff [4];
float target_speed[4];
int8_t usb_catch;  //usb控制击球

volatile bool is_homed[4] = {false,false,false,false};
volatile bool chassis_is_ready = false;
int n=0;
//寻零动作
	float target_spd_D[4] ;

/*******************************************************************************************
  * @Func		float Motor_PID_Calculate(DJI_MotorModule *obj, float input)
  * @Brief      解算usb传输的数�?
  * @Retval		None
  * @Date     2026/4/22//
 *******************************************************************************************/
void usbdata_get()
{
     if (USB_RxFlag==1)
    {
        USB_RxFlag=0;
        if(USB_Len==9)
        {
            if (USB_Buffer[0] == 0xAA && USB_Buffer[8] == 0x55)
            {
                
                 raw_vx = (int16_t)((USB_Buffer[2] << 8) | USB_Buffer[1]);
                 raw_vy = (int16_t)((USB_Buffer[4] << 8) | USB_Buffer[3]);
                 raw_vw = (int16_t)((USB_Buffer[6] << 8) | USB_Buffer[5]);
								usb_catch=USB_Buffer[7];
                Vx=-MYdata_convert(raw_vx,-2000,2000,-10,10,1);
                Vy=MYdata_convert(raw_vy,-2000,2000,-10,10,1);
                Vw=MYdata_convert(raw_vw,-2000,2000,-10,10,1);
								CDC_Transmit_HS(USB_Buffer,9);//记得把我们发的数据打印出来，还有一个k;
            }
        }
    }
}

void Chassis_Homing_Routine(void)
{   
	float homing_rpm = 5000.0f;	//寻零速度
	if(is_homed [0]&&is_homed [1]&&is_homed [2]&&is_homed [3])
//		if(is_homed [2])
	{
		chassis_is_ready = true;  //检查光电门是否均被触发后退�?
    DJIset_motor_data(&hfdcan3, 0x200, 0, 0, 0, 0);
		return;
	}
  target_spd_D [0]= is_homed[0] ? 0.0f : homing_rpm;
  target_spd_D [1]= is_homed[1] ? 0.0f : homing_rpm;
  target_spd_D [2]= is_homed[2] ? 0.0f : homing_rpm;
  target_spd_D [3]= is_homed[3] ? 0.0f : homing_rpm;  //四个轮子独立寻零
	f_PID_Calculate(&chassis_motor1D.pid_spd, target_spd_D[0],chassis_motor1D.speed_rpm);
	f_PID_Calculate(&chassis_motor2D.pid_spd, target_spd_D[1],chassis_motor2D.speed_rpm);
	f_PID_Calculate(&chassis_motor3D.pid_spd, target_spd_D[2],chassis_motor3D.speed_rpm);
	f_PID_Calculate(&chassis_motor4D.pid_spd, target_spd_D[3],chassis_motor4D.speed_rpm);
	DJIset_motor_data (&hfdcan3,0X200,
	                   chassis_motor1D.pid_spd.Output,
	                   chassis_motor2D.pid_spd.Output,
	                   chassis_motor3D.pid_spd.Output,
	                   chassis_motor4D.pid_spd.Output);
//		DJIset_motor_data(&hfdcan3, 0X200, 0, 0, 0, 0);
	DJIset_motor_data(&hfdcan2, 0x1FF, 0, 0, 0, 0);
	
}

void Chassis_Calc(Chassis_Module *chassis, Chassis_Module *chassisD)
{
    // ==================== 1. 获取控制指令（遥控器或调试值）====================
    // 调试阶段使用固定值，实际使用时取消注释遥控器部分
	float k=1;
//if(mode1==1){
	   k=MYdata_convert(RCctrl.CH3,260,1750,0,10,0.05);
     Vx=MYdata_convert(RCctrl.CH1,284,1750,-10,10,1);



if(RCctrl.CH1<=1100&&RCctrl.CH1>=1200) Vx=0;
     Vy=-MYdata_convert(RCctrl.CH2,275,1775,-10,10,1);
	if(RCctrl.CH2<=1100&&RCctrl.CH2>=1200) Vy=0;
     Vw=MYdata_convert(RCctrl.CH4,290,1800,-10,10,1);
//}
//else {usbdata_get();
//	    float k=0.1;}

//     Vx=(RCctrl.CH3-1020.0f)/780*50.0f ;
//     Vy= -(RCctrl.CH4-1070.0f)/730*50.0f;


    chassis->param.Accel = 5.0f;
    chassis->param.Vx = Vx*k;      // 调试时用小速度，如 0.5 m/s
    chassis->param.Vy = Vy*k;
    chassis->param.Vw = Vw*k;

    chassisD->param.Accel = 5.0f;
    chassisD->param.Vx = Vx*k;
    chassisD->param.Vy = Vy*k;
    chassisD->param.Vw = Vw*k;


    // ==================== 2. 运动学解算（轮子线速度 + 目标角度�?====================
    const float wheel_y[4] = { CHASSIS_HALF_LENGTH,  CHASSIS_HALF_LENGTH, -CHASSIS_HALF_LENGTH, -CHASSIS_HALF_LENGTH };
    const float wheel_x[4] = { CHASSIS_HALF_WIDTH, - CHASSIS_HALF_WIDTH, -CHASSIS_HALF_WIDTH,  CHASSIS_HALF_WIDTH };
//    const float wheel_y[4] = { CHASSIS_HALF_LENGTH,  CHASSIS_HALF_LENGTH, -CHASSIS_HALF_LENGTH, -CHASSIS_HALF_LENGTH };
//    const float wheel_x[4] = { CHASSIS_HALF_WIDTH, - CHASSIS_HALF_WIDTH, -CHASSIS_HALF_WIDTH,  CHASSIS_HALF_WIDTH };若长宽改变，切换这两�?
    // 减速比：电机转 N 圈，轮子�? 1 圈（电机角度 = 轮子角度 * GEAR_RATIO�?
    const float GEAR_RATIO = 144.0f;   // 根据实际机械比修�?
    
    for (int i = 0; i < 4; i++)
    {
        // 轮心速度分量（底盘坐标系�?
        float vx_wheel = chassis->param.Vx - chassis->param.Vw * wheel_y[i];
        float vy_wheel = chassis->param.Vy + chassis->param.Vw * wheel_x[i];
        
        // 原始的驱动轮目标线速度 �? 舵轮目标角度 
         target_speed[i] = sqrtf(vx_wheel * vx_wheel + vy_wheel * vy_wheel);
//         target_angle_rad[i] = -atan2f(vx_wheel, vy_wheel);若长宽改变，这一行也要变�?
         target_angle_rad[i] = atan2f(vx_wheel, vy_wheel);
			if(target_angle_rad[i]==-M_PI) target_angle_rad[i]=M_PI;
        // 获取当前 2006 转向电机的真实累计脉�? 
        float motor_total_ecd = 0.0f;
        switch (i) {
            case 0: motor_total_ecd = chassis_motor1D.total_angle; 
					current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
					break;
            case 1: motor_total_ecd = chassis_motor2D.total_angle; 
					current_angle_rad[i] = (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
					break;
            case 2: motor_total_ecd = chassis_motor3D.total_angle; 
					current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
					break;
            case 3: motor_total_ecd = chassis_motor4D.total_angle; 
					current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
					break;
        }
        
        // 将电机的累计脉冲数，逆向换算为当前轮子的真实弧度
        // 编码器一�?8192，除以减速比 GEAR_RATIO 得到轮子真实的累计弧�?
				 while(current_angle_rad[i]>2*M_PI)  current_angle_rad[i]=current_angle_rad[i]-2*M_PI;
				 while(current_angle_rad[i]<-2*M_PI) current_angle_rad[i]=current_angle_rad[i]+2*M_PI;
         
//				if(target_angle_rad[i]==M_PI) target_angle_rad[i]=-M_PI;
//				if (n==0){
         if(current_angle_rad[i]>M_PI){    
        switch (i) {
            case 0: chassis_motor1D.total_angle=-589824; chassis_motor1D.round_cnt=-72; chassis_motor1D.angle=0;
					break;
            case 1: chassis_motor2D.total_angle=-589824; chassis_motor2D.round_cnt=-72; chassis_motor2D.angle=0;
					break;
            case 2: chassis_motor3D.total_angle=-589824; chassis_motor3D.round_cnt=-72; chassis_motor3D.angle=0;
					break;
            case 3: chassis_motor4D.total_angle=-589824; chassis_motor4D.round_cnt=-72; chassis_motor4D.angle=0;
					break;
					
        }					 
					 current_angle_rad[i]=current_angle_rad[i]-2*M_PI;
				}
				 if(current_angle_rad[i]<-M_PI){   
        switch (i) {
            case 0: chassis_motor1D.total_angle=589824; chassis_motor1D.round_cnt=71; chassis_motor1D.angle=8191;
					break;
            case 1: chassis_motor2D.total_angle=589824; chassis_motor2D.round_cnt=71; chassis_motor2D.angle=8191;
					break;
            case 2: chassis_motor3D.total_angle=589824; chassis_motor3D.round_cnt=71; chassis_motor3D.angle=8191;
					break;
            case 3: chassis_motor4D.total_angle=589824; chassis_motor4D.round_cnt=71; chassis_motor4D.angle=8191;
					break;
					
				}					
				  current_angle_rad[i]=current_angle_rad[i]+2*M_PI;
				
				}
//				 n=2;
//			}

//  if(target_angle_rad[i]<=3&&target_angle_rad[i]>=-3) n=0;
//				 if(target_angle_rad[0]&&target_angle_rad[1]&&target_angle_rad[2]&&target_angle_rad[3]) n=0;
     
//				
//         while(target_angle_rad[i]>M_PI) target_angle_rad[i]=target_angle_rad[i]-2*M_PI;
//				 while(target_angle_rad[i]<-M_PI) target_angle_rad[i]=target_angle_rad[i]+2*M_PI;				
//        /* ==================== 优劣弧优�? ==================== */
//        
//        // 防抽搐优化：如果目标速度极小，保持当前角度不变，防止轮子突然回正
        if (target_speed [i]< 0.05f) {
          
            target_angle_rad[i] = 0;
            target_speed [i]= 0.0f; 
        }

/**************************我的优劣弧逻辑***************************************/
//         angle_diff [i]= ABS(target_angle_rad[i] - current_angle_rad[i]);
//				
//				if(angle_diff[i]>M_PI/2&&angle_diff[i]<3*M_PI/2)
//				{
//				  target_speed[i]=-target_speed[i];
//					if(target_angle_rad[i]>0) target_angle_rad[i]=target_angle_rad[i]-M_PI;
//					if(target_angle_rad[i]<0) target_angle_rad[i]=target_angle_rad[i]+M_PI;
			//	}
//				  
//				angle_diff[i]=target_angle_rad[i] - current_angle_rad[i];
//				if(target_angle_rad[i] - current_angle_rad[i]>=3*M_PI/2)  target_angle_rad[i]=target_angle_rad[i]-current_angle_rad[i]-M_PI*2+current_angle_rad[i];
//				if(target_angle_rad[i] - current_angle_rad[i]<=-3*M_PI/2) target_angle_rad[i]=target_angle_rad[i]-current_angle_rad[i]+M_PI*2+current_angle_rad[i];
				
				
/**************************优劣弧长逻辑*******************************/
                 // 计算目标角度与当前角度的初始差�?
				 angle_diff[i] = target_angle_rad[i] - current_angle_rad[i];
//         if(angle_diff[i]<=3.142&&angle_diff[i]>=3.141)    angle_diff[i]=0; 
//         if(angle_diff[i]>=-3.142&&angle_diff[i]<=-3.141)    angle_diff[i]=0;
        // 将角度差强制限制�? [-PI, PI] 之间
        while (angle_diff[i] >= M_PI)  angle_diff[i] -= 2.0f * M_PI;
        while (angle_diff[i] <=-M_PI) angle_diff[i] += 2.0f * M_PI;

        // 优劣弧反转（确保转向电机旋转绝对值不超过 90 度）
        if (angle_diff [i]> M_PI / 2.0f) 
        {                                        
					  target_angle_rad_change[i] = target_angle_rad[i]-M_PI;                                                                                                                                                                     // 目标角度减去 180 度，转向反面
            target_speed[i] = -target_speed[i];     // 驱动电机速度反转，负负得�?
        } 
        else if (angle_diff [i]< -M_PI / 2.0f) 
        {
            target_angle_rad_change[i]	 =target_angle_rad[i]+ M_PI;         // 目标角度加上 180 度，转向反面
            target_speed[i] = -target_speed[i];     // 驱动电机速度反转，负负得�?
        }else{
					target_angle_rad_change[i]=target_angle_rad[i];
				}
        //将优化后的速度赋值给驱动轮结构体
        chassis->param.wheel_out[i] = target_speed[i];

        //将优化后的轮子目标角度转换为电机侧累计角�?
        chassisD->param.wheel_out[i] = target_angle_rad_change[i] * (8192.0f / (2.0f * M_PI)) * GEAR_RATIO;
    }
		
    // ==================== 3. 3508 驱动轮：线速度 -> 目标转�? -> 速度�? ====================
    float wheel_radius = 0.055f;   // 实际轮子半径（米），请根据实物修�?
    for (int i = 0; i < 4; i++)
    {
        float target_rpm = (chassis->param.wheel_out[i] / (2.0f * M_PI * wheel_radius)) * 60.0f;
        switch (i)
        {
            case 0: chassis_motor1.PID_Calculate(&chassis_motor1, target_rpm); break;
            case 1: chassis_motor2.PID_Calculate(&chassis_motor2, target_rpm); break;
            case 2: chassis_motor3.PID_Calculate(&chassis_motor3, target_rpm); break;
            case 3: chassis_motor4.PID_Calculate(&chassis_motor4, target_rpm); break;
        }	
    }
      chassis_motor1D.PID_Calculate(&chassis_motor1D, chassisD->param.wheel_out[0]); 
      chassis_motor2D.PID_Calculate(&chassis_motor2D, chassisD->param.wheel_out[1]);
      chassis_motor3D.PID_Calculate(&chassis_motor3D, chassisD->param.wheel_out[2]);
      chassis_motor4D.PID_Calculate(&chassis_motor4D, chassisD->param.wheel_out[3]); 

}


void Chassis_Stop(Chassis_Module *chassis)
{
    // �? 3508 驱动轮目标速度设为0
    for(int i = 0; i < 4; i++) {
        chassis->param.wheel_out[i] = 0.f;
    }
    // 2006 转向轮保持当前角度，不强制归�?
}

void runbabyrun()
{
    P_Chassis_Calc(&Chassis, &ChassisD);
    DJIset_motor_data(&hfdcan2, 0X1FF, chassis_motor1.pid_spd.Output, chassis_motor2.pid_spd.Output,chassis_motor3.pid_spd.Output,chassis_motor4.pid_spd.Output);
    DJIset_motor_data(&hfdcan3, 0X200, chassis_motor1D.pid_spd.Output, chassis_motor2D.pid_spd.Output,chassis_motor3D.pid_spd.Output,chassis_motor4D.pid_spd.Output);
//    DJIset_motor_data(&hfdcan3, 0X200,500,500,500,500);
}

float ChangeAngle(float angle)
{
if(angle>=180) angle=M_PI-angle;
return angle;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //1号左�? =================
    if(GPIO_Pin == GPIO_PIN_0) 
    {
        if(!is_homed[0]) {
					  chassis_motor1D.angle=0;
					  chassis_motor1D.round_cnt=0;
            chassis_motor1D.total_angle = 0; 
					  
            is_homed[0] = true;            
        }
    }
    //2号右�? =================
    else if(GPIO_Pin == GPIO_PIN_2) 
    {
        if(!is_homed[1]) {
					  chassis_motor2D.angle=0;
					  chassis_motor2D.round_cnt=0;
            chassis_motor2D.total_angle = 0;
					  
            is_homed[1] = true;
        }
    }
    // 3号左�? =================
    else if(GPIO_Pin == GPIO_PIN_13)
    {
        if(!is_homed[2]) {
					  chassis_motor3D.angle=0;
					  chassis_motor3D.round_cnt=0;
            chassis_motor3D.total_angle = 0;
					  
            is_homed[2] = true;
        }
    }
    //4号右�? =================
    else if(GPIO_Pin == GPIO_PIN_9)
    {
        if(!is_homed[3]) {
					  chassis_motor4D.angle=0;
					  chassis_motor4D.round_cnt=0;
            chassis_motor4D.total_angle = 0;
					  
            is_homed[3] = true;
        }
    }
}

//void MyChassis_Calc(Chassis_Module *chassis, Chassis_Module *chassisD)
//{
//    // ==================== 1. 获取控制指令（遥控器或调试值）====================
//    // 调试阶段使用固定值，实际使用时取消注释遥控器部分

////到时候把操控换成右边的遥杆，通道和通道最大值最小值改一下就行，还有现在�?34通道最大值最小值我忘了，这个是凭印象给�?
//	float k=MYdata_convert(RCctrl.CH3,260,1750,0,10,0.05);
//        Vx=MYdata_convert(RCctrl.CH1,284,1750,-10,10,1);
//        Vy=-MYdata_convert(RCctrl.CH2,275,1775,-10,10,1);
//        Vw=MYdata_convert(RCctrl.CH4,290,1800,-10,10,1);



//    chassis->param.Accel = 5.0f;
//    chassis->param.Vx = Vx*k;      // 调试时用小速度，如 0.5 m/s
//    chassis->param.Vy = Vy*k;
//    chassis->param.Vw = Vw*k;

//    chassisD->param.Accel = 5.0f;
//    chassisD->param.Vx = Vx*k;
//    chassisD->param.Vy = Vy*k;
//    chassisD->param.Vw = Vw*k;


//    // ==================== 2. 运动学解算（轮子线速度 + 目标角度�?====================
//    const float wheel_y[4] = { CHASSIS_HALF_LENGTH,  CHASSIS_HALF_LENGTH, -CHASSIS_HALF_LENGTH, -CHASSIS_HALF_LENGTH };
//    const float wheel_x[4] = { CHASSIS_HALF_WIDTH, - CHASSIS_HALF_WIDTH, -CHASSIS_HALF_WIDTH,  CHASSIS_HALF_WIDTH };

//    const float GEAR_RATIO = 144.0f;   // 根据实际机械比修�?
//    
//    for (int i = 0; i < 4; i++)
//    {
//        // 轮心速度分量（底盘坐标系�?
//        float vx_wheel = chassis->param.Vx - chassis->param.Vw * wheel_y[i];
//        float vy_wheel = chassis->param.Vy + chassis->param.Vw * wheel_x[i];
//        
//        // 原始的驱动轮目标线速度 �? 舵轮目标角度 
//         target_speed[i] = sqrtf(vx_wheel * vx_wheel + vy_wheel * vy_wheel);
////         target_angle_rad[i] = -atan2f(vx_wheel, vy_wheel);若长宽改变，这一行也要变�?
//         target_angle_rad[i] = atan2f(vx_wheel, vy_wheel);
//        // 获取当前 2006 转向电机的真实累计脉�? 
//        float motor_total_ecd = 0.0f;

//        
//        // 将电机的累计脉冲数，逆向换算为当前轮子的真实弧度
//        // 编码器一�?8192，除以减速比 GEAR_RATIO 得到轮子真实的累计弧�?
//				
//         
//				if(target_angle_rad[i]==M_PI) target_angle_rad[i]=-M_PI;
//				
//         if(current_angle_rad[i]>=M_PI){    
//        switch (i) {
//            case 0: chassis_motor1D.total_angle=-589824; chassis_motor1D.round_cnt=-72; chassis_motor1D.angle=0;
//					break;
//            case 1: chassis_motor2D.total_angle=-589824; chassis_motor2D.round_cnt=-72; chassis_motor2D.angle=0;
//					break;
//            case 2: chassis_motor3D.total_angle=-589824; chassis_motor3D.round_cnt=-72; chassis_motor3D.angle=0;
//					break;
//            case 3: chassis_motor4D.total_angle=-589824; chassis_motor4D.round_cnt=-72; chassis_motor4D.angle=0;
//					break;
//        }					 
//					 current_angle_rad[i]=current_angle_rad[i]-2*M_PI;}
//				 if(current_angle_rad[i]<=-M_PI){   
//        switch (i) {
//            case 0: chassis_motor1D.total_angle=589824; chassis_motor1D.round_cnt=71; chassis_motor1D.angle=8191;
//					break;
//            case 1: chassis_motor2D.total_angle=589824; chassis_motor2D.round_cnt=71; chassis_motor2D.angle=8191;
//					break;
//            case 2: chassis_motor3D.total_angle=589824; chassis_motor3D.round_cnt=71; chassis_motor3D.angle=8191;
//					break;
//            case 3: chassis_motor4D.total_angle=589824; chassis_motor4D.round_cnt=71; chassis_motor4D.angle=8191;
//				}					
//				  current_angle_rad[i]=current_angle_rad[i]+2*M_PI;}
//				 
//        switch (i) {
//            case 0: motor_total_ecd = chassis_motor1D.total_angle; 
//					current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
//					break;
//            case 1: motor_total_ecd = chassis_motor2D.total_angle; 
//					current_angle_rad[i] = (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
//					break;
//            case 2: motor_total_ecd = chassis_motor3D.total_angle; 
//					current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
//					break;
//            case 3: motor_total_ecd = chassis_motor4D.total_angle; 
//					current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
//					break;
//        }
//				
//				
////        /* ==================== 优劣弧优�? ==================== */
////        
////        // 防抽搐优化：如果目标速度极小，保持当前角度不变，防止轮子突然回正
//        if (target_speed [i]< 0.05f) {
//          
//            target_angle_rad[i] = 0;
//            target_speed [i]= 0.0f; 
//        }


///**************************优劣弧长逻辑*******************************/
//                 // 计算目标角度与当前角度的初始差�?
//				 angle_diff[i] = target_angle_rad[i] - current_angle_rad[i];
//         if(angle_diff[i]<=3.1416&&angle_diff[i]>=3.1415)    angle_diff[i]=0; 
//         if(angle_diff[i]>=-3.1416&&angle_diff[i]<=-3.1415)    angle_diff[i]=0; 				
//        // 将角度差强制限制�? [-PI, PI] 之间
//        while (angle_diff[i] > M_PI)  angle_diff[i] -= 2.0f * M_PI;
//				
//        while (angle_diff[i] < -M_PI) angle_diff[i] += 2.0f * M_PI;

//        // 优劣弧反转（确保转向电机旋转绝对值不超过 90 度）
//        if (angle_diff [i]> M_PI / 2.0f) 
//        {                                        
//					  target_angle_rad[i] -= M_PI;         // 目标角度减去 180 度，转向反面
//            target_speed[i] = -target_speed[i];     // 驱动电机速度反转，负负得�?
//        } 
//        else if (angle_diff [i]< -M_PI / 2.0f) 
//        {
//            target_angle_rad[i]	 += M_PI;         // 目标角度加上 180 度，转向反面
//            target_speed[i] = -target_speed[i];     // 驱动电机速度反转，负负得�?
//        }
//        //将优化后的速度赋值给驱动轮结构体
//        chassis->param.wheel_out[i] = target_speed[i];

//        //将优化后的轮子目标角度转换为电机侧累计角�?
//        chassisD->param.wheel_out[i] = target_angle_rad[i] * (8192.0f / (2.0f * M_PI)) * GEAR_RATIO;
//    }
//		
//    // ==================== 3. 3508 驱动轮：线速度 -> 目标转�? -> 速度�? ====================
//    float wheel_radius = 0.055f;   // 实际轮子半径（米），请根据实物修�?
//    for (int i = 0; i < 4; i++)
//    {
//        float target_rpm = (chassis->param.wheel_out[i] / (2.0f * M_PI * wheel_radius)) * 60.0f;
//        switch (i)
//        {
//            case 0: chassis_motor1.PID_Calculate(&chassis_motor1, target_rpm); break;
//            case 1: chassis_motor2.PID_Calculate(&chassis_motor2, target_rpm); break;
//            case 2: chassis_motor3.PID_Calculate(&chassis_motor3, target_rpm); break;
//            case 3: chassis_motor4.PID_Calculate(&chassis_motor4, target_rpm); break;
//        }	
//    }
//      chassis_motor1D.PID_Calculate(&chassis_motor1D, chassisD->param.wheel_out[0]); 
//      chassis_motor2D.PID_Calculate(&chassis_motor2D, chassisD->param.wheel_out[1]);
//      chassis_motor3D.PID_Calculate(&chassis_motor3D, chassisD->param.wheel_out[2]);
//      chassis_motor4D.PID_Calculate(&chassis_motor4D, chassisD->param.wheel_out[3]); 

//}

void P_Chassis_Calc(Chassis_Module *chassis, Chassis_Module *chassisD)
{
    // ==================== 1. 获取控制指令（遥控器或调试值）====================
		
	k=MYdata_convert(RCctrl.CH3,260,1750,0,10,0.05);
if(mode1==1){
	   
     Vy=MYdata_convert(RCctrl.CH1,284,1750,-10,10,1);
     Vx=-MYdata_convert(RCctrl.CH2,275,1775,-10,10,1);
	   Vw=MYdata_convert(RCctrl.CH4,290,1800,-10,10,1);}
else {usbdata_get();
	    }
    chassis->param.Accel = 5.0f;
    chassis->param.Vx = Vx*k;      // 调试时用小速度，如 0.5 m/s
    chassis->param.Vy = Vy*k;
    chassis->param.Vw = Vw*k;

    chassisD->param.Accel = 5.0f;
    chassisD->param.Vx = Vx*k;
    chassisD->param.Vy = Vy*k;
    chassisD->param.Vw = Vw*k;


    // ==================== 2. 运动学解算（轮子线速度 + 目标角度�?====================
    const float wheel_x[4] = { CHASSIS_HALF_LENGTH,  CHASSIS_HALF_LENGTH, -CHASSIS_HALF_LENGTH, -CHASSIS_HALF_LENGTH };
    const float wheel_y[4] = { CHASSIS_HALF_WIDTH,  -CHASSIS_HALF_WIDTH, -CHASSIS_HALF_WIDTH,  CHASSIS_HALF_WIDTH };
    
    // 减速比：电机转 N 圈，轮子�? 1 圈（电机角度 = 轮子角度 * GEAR_RATIO�?
    const float GEAR_RATIO = 144.0f;   // 根据实际机械比修�?
    
    for (int i = 0; i < 4; i++)
    {
        // 轮心速度分量（底盘坐标系�?
        float vx_wheel = chassis->param.Vx - chassis->param.Vw * wheel_y[i];
        float vy_wheel = chassis->param.Vy + chassis->param.Vw * wheel_x[i];
        
        // 原始的驱动轮目标线速度 �? 舵轮目标角度 
         target_speed[i] = sqrtf(vx_wheel * vx_wheel + vy_wheel * vy_wheel);
         target_angle_rad[i] = atan2f(vy_wheel, vx_wheel);
        
        // 获取当前 2006 转向电机的真实累计脉�? 
        float motor_total_ecd = 0.0f;
        switch (i) {
            case 0:
                     motor_total_ecd = chassis_motor1D.total_angle; 					
                    current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
					break;
            case 1: 
                    motor_total_ecd = chassis_motor2D.total_angle; 					
                    current_angle_rad[i] = (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
					break;
            case 2: 
                    motor_total_ecd = chassis_motor3D.total_angle; 					
                    current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
					break;
            case 3: 
                    motor_total_ecd = chassis_motor4D.total_angle; 				
                    current_angle_rad[i]= (motor_total_ecd / 8192.0f) * (2.0f * M_PI) / GEAR_RATIO;
					break;
        }
       


  // 计算目标角度与当前角度的初始差�?
        float angle_diff = target_angle_rad[i] - current_angle_rad[i];

        // 将角度差强制限制�? [-PI, PI] 之间
        while (angle_diff > M_PI)  angle_diff -= 2.0f * M_PI;
        while (angle_diff < -M_PI) angle_diff += 2.0f * M_PI;

        // 优劣弧反转（确保转向电机旋转绝对值不超过 90 度）
        if (angle_diff > M_PI / 2.0f) 
        {
            angle_diff -= M_PI;         // 目标角度减去 180 度，转向反面
            target_speed[i] = -target_speed[i];     // 驱动电机速度反转，负负得�?
        } 
        else if (angle_diff < -M_PI / 2.0f) 
        {
            angle_diff += M_PI;         // 目标角度加上 180 度，转向反面
            target_speed[i] = -target_speed[i];     // 驱动电机速度反转，负负得�?
        }

    float optimized_target_angle_rad = current_angle_rad[i] + angle_diff;

        //将优化后的速度赋值给驱动轮结构体
        chassis->param.wheel_out[i] = target_speed[i];

        //将优化后的轮子目标角度转换为电机侧累计角�?
        chassisD->param.wheel_out[i] = optimized_target_angle_rad * (8192.0f / (2.0f * M_PI)) * GEAR_RATIO;

    }
		
    // ==================== 3. 3508 驱动轮：线速度 -> 目标转�? -> 速度�? ====================
    float wheel_radius = 0.055f;   // 实际轮子半径（米），请根据实物修�?
    for (int i = 0; i < 4; i++)
    {
        float target_rpm = (chassis->param.wheel_out[i] / (2.0f * M_PI * wheel_radius)) * 60.0f;
        switch (i)
        {
            case 0: chassis_motor1.PID_Calculate(&chassis_motor1, target_rpm); break;
            case 1: chassis_motor2.PID_Calculate(&chassis_motor2, target_rpm); break;
            case 2: chassis_motor3.PID_Calculate(&chassis_motor3, target_rpm); break;
            case 3: chassis_motor4.PID_Calculate(&chassis_motor4, target_rpm); break;
        }	
    }
      chassis_motor1D.PID_Calculate(&chassis_motor1D, chassisD->param.wheel_out[0]); 
      chassis_motor2D.PID_Calculate(&chassis_motor2D, chassisD->param.wheel_out[1]);
      chassis_motor3D.PID_Calculate(&chassis_motor3D, chassisD->param.wheel_out[2]);
      chassis_motor4D.PID_Calculate(&chassis_motor4D, chassisD->param.wheel_out[3]); 

}
