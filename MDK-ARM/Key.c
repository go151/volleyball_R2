#include "gpio.h"
#include "KEY.h"


int count=0,ifPressed=0,Key_Num=0,totaltime=0,KeyTime=0;
uint8_t flagKey=0,lastflagKey=0;
int temp1,temp2,temp3,times=0;
uint8_t GetTick(void)
{
	
	return HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);
}



uint8_t GetState1(void)
{
    count++;
	  
	if(count==20)
	{
	  count=0;
		lastflagKey=flagKey;
		flagKey=GetTick();
		if(flagKey==1&&lastflagKey==0) return 1;
		else return 0;
	}return 0;

}

void GetState2(void)
{
    count++;
	  totaltime++;
	  KeyTime++;
	if(count==20)
	{
	  count=0;
		
		lastflagKey=flagKey;
		flagKey=GetTick();
		if(flagKey==0&&lastflagKey==1) 
{KeyTime=0;
ifPressed=lastflagKey;}
		else if(flagKey==1&&lastflagKey==0) 
{temp2=KeyTime;
ifPressed=flagKey;	}	
	}

}

uint8_t GetTimes(void)
{
	GetState2();
  if(ifPressed)
	{
		if(count-temp1<=250)
		{
		times++;
		}else times=1;
		temp1=count;
	}
}













