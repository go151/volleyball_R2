#include "Motion_Task.h"
#include "remote_control.h"
#include "chassis.h"
#include "cmsis_os.h"
#include "register.h"
#include "ws2812.h"
#include "up.h"
Motion_mode motion_mode;
Control_mode control_mode;
Remote_mode remote_mode;
uint8_t mode1=1;
HAL_StatusTypeDef a;
volatile int flag2=0;
float t;
void Motion_Task(void const * argument)
{
	

	
	  up_Init();
	 
		while(DM_Motor_CMD(&DM2325[0],Motor_Enable)!=HAL_OK&&DM_Motor_CMD(&DM2325[1],Motor_Enable)!=HAL_OK&&DM_Motor_CMD(&DM4310[0],Motor_Enable)!=HAL_OK)
			
    huart5.RxState = HAL_UART_STATE_READY;
		
//		save_pos_zero(&DM4310[0],0x0000);
//		save_pos_zero(&DM4310[1],0x0000);
//		save_pos_zero(&DM4310[2],0x0000);
		save_pos_zero(&DM2325[0],0x0000);
		save_pos_zero(&DM2325[1],0x0000);
		
		
		chassis_is_ready = false;
    is_homed[0] = false;
    is_homed[1] = false;
    is_homed[2] = false;
    is_homed[3] = false;
  for(;;)
  {
		if(RCctrl.CH5>=1000){mode1=1;}
		else mode1=2;
		
    if(RCctrl.CH10>=1000)
		{
			flag2=0;
//			if(DM2325[0].state!=ON|DM2325[1].state!=ON|DM4310[0].state!=ON|DM4310[1].state!=ON|DM4310[2].state!=ON) DMenable();
			if(DM2325[0].state!=ON|DM2325[1].state!=ON) DMenable();
			Catch();
			
    if(RCctrl.CH7>=1000)
		    {
		     runbabyrun();

     
				 DMset_posvel_data(&DM2325[0],0,5.0);
		     DMset_posvel_data(&DM2325[1],50,5.0);

		    }else
				 {
				 
				  Upbabyup();
				  

         }
		}
    else
	 {
//      if(DM2325[0].state!=OFF|DM2325[1].state!=OFF|DM4310[0].state!=OFF|DM4310[1].state!=OFF|DM4310[2].state!=OFF) DMdisable();
				if(DM2325[0].state!=OFF|DM2325[1].state!=OFF) DMdisable();
	     if (!chassis_is_ready) 
      {
	     flag2=1;
       Chassis_Homing_Routine();
       osDelay(1);
       continue; 
      }
	     if(flag2==0){
		  chassis_is_ready = false;
      is_homed[0] = false;
      is_homed[1] = false;
      is_homed[2] = false;
      is_homed[3] = false;

		}
	}

	osDelay(1);

  }

}
