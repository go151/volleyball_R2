#include "Can_Task.h"
#include "Motion_Task.h"
#include "motor.h"
#include "dji_motor.h"
#include "dm_motor.h"
#include "chassis.h"
#include "usart.h"
#include "ws2812.h"
#include "KEY.h"
#include "tim.h"
#include "BUZZER.h"
#include "main.h"
// uint8_t data[25];
// uint8_t b=0;
int mode;
#define WS2812_LowLevel    0xC0     // 0Ты
#define WS2812_HighLevel   0xF0     // 1Ты
uint8_t r=30 , g=0,  b=0,x=0;
uint8_t NextSongFlag=0;
void Can_Task(void const * argument)
{
//    TickType_t Systick = 0;
//    uint32_t can1_free_level = 0;
//    uint32_t can2_free_level = 0;
//    
//    
	
		uint8_t txbuf[24];
    uint8_t res = 0;
     while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY);
	
    for(;;)
    {       


			if(RCctrl.CH7>=1000) mode=0;
			else mode=1;
//			

			
		switch(mode)
		{
			case 0:
				MusicFlag1=1;
			  x=(uint8_t)data_convert(RCctrl.CH3,260,1750,0,255,0.05 );
        if(x<85) {g=(uint8_t)x*3;b=0;r=0;}
					else if(x>=85&&x<=170) {g=255-(x-85)*3;b=(x-85)*3;r=0;}
						else {g=0;b=255-(x-170)*3;r=(x-170)*3;}

        WS2812_Ctrl(r,g,b);
				 break;
			case 1:
				 if(RCctrl.CH8>=1100) {
				 if(NextSongFlag==0){
				 Song++;
					 if(Song==4) Song=0;
				 NextSongFlag=1;}}
				 else if(RCctrl.CH8>=1000){ MusicFlag1=1;
				 Volume=data_convert(RCctrl.CH2,260,1750,0,255,0.05 );
				 NextSongFlag=0;}
			   else MusicFlag1=0;

		
		}
			 if(mode==1)
	{
		
	    delay++;
			switch(Song)
	    {
		    case LanTingXu:
	       LanTingXuSong();
				break;
		    case 1:
	       YiJianMeiSong();
				break;
		    case 2:
	       YiJianMeiSong();
				break;
		    case 3:
	       YiJianMeiSong();
				break;
	     }
			
			switch(Song)
	    {
		    case LanTingXu:
	      LanTingXu_LightChange();
				break;
		    case 1:
	       YiJianMeiSong();
				break;
		    case 2:
	       YiJianMeiSong();
				break;
		    case 3:
	       YiJianMeiSong();
				break;
	     }			 
	}else if(mode==0) OneTime( Volume, 500, NOTE_MUTE);
		osDelay(1);
    }

}
