#include "BUZZER.h"
#include "Motion_Task.h"
uint8_t Song=0;

void OneTime(int Volume,int delay,int which)
{
  __HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_2,Volume);
	htim12.Instance->ARR=which;
	HAL_Delay(delay);
}

void LanTingXuSong(void)
{
 if(!MusicFlag1){
	 
   switch(MusicProcess){
    case 0:
    OneTime( Volume, 500, NOTE_M_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 1:
    OneTime( Volume, 500, NOTE_M_LA);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 2:
    OneTime( Volume, 500, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 3:
    OneTime( Volume, 1500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 4:
    OneTime( Volume, 500, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 5:
    OneTime( Volume, 1000, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 6:
    OneTime( Volume, 500, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 7:
    OneTime( Volume, 500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 8:
    OneTime( Volume, 2000, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 9:
    OneTime( Volume, 500, NOTE_MUTE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 10:
    OneTime( Volume, 500, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 11:
    OneTime( Volume, 500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 12:
    OneTime( Volume, 500, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 13:
    OneTime( Volume, 1500, NOTE_H_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 14:
    OneTime( Volume, 500, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 15:
    OneTime( Volume, 500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 16:
    OneTime( Volume, 500, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 17:
    OneTime( Volume, 500, NOTE_M_LA);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 18:
    OneTime( Volume, 500, NOTE_M_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 19:
    OneTime( Volume, 3000, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 20:
    OneTime( Volume, 500, NOTE_H_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 21:
    OneTime( Volume, 500, NOTE_H_LA);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 22:
    OneTime( Volume, 1500, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 23:
    OneTime( Volume, 100, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 24:
    OneTime( Volume, 100, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 25:
    OneTime( Volume, 300, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 26:
    OneTime( Volume, 100, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 27:
    OneTime( Volume, 400, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 28:
    OneTime( Volume, 500, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 29:
    OneTime( Volume, 500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 30:
    OneTime( Volume, 1500, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 31:
    OneTime( Volume, 500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 32:
    OneTime( Volume, 2500, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 33:
    OneTime( Volume, 500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 34:
    OneTime( Volume, 500, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 35:
    OneTime( Volume, 1500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 36:
    OneTime( Volume, 500, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 37:
    OneTime( Volume, 500, NOTE_M_LA);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 38:
    OneTime( Volume, 500, NOTE_M_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 39:
    OneTime( Volume, 500, NOTE_H_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 40:
    OneTime( Volume, 500, NOTE_H_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
    
    case 41:
    OneTime( Volume, 2000, NOTE_H_DO);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		//前奏，后面正曲开始
		case 42:
    OneTime( Volume, 500, 0);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 43:
    OneTime( Volume, 500, NOTE_M_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 44:
    OneTime( Volume, 500, NOTE_M_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 45:
    OneTime( Volume, 500, NOTE_M_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 46:
    OneTime( Volume, 1000, NOTE_M_LA);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 47:
    OneTime( Volume, 500, NOTE_M_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 48:
    OneTime( Volume, 500, NOTE_M_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 49:
    OneTime( Volume, 500, NOTE_M_LA);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 50:
    OneTime( Volume, 500, NOTE_M_SOL);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 51:
    OneTime( Volume, 500, NOTE_M_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}
		
		case 52:
    OneTime( Volume, 500, NOTE_M_RE);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}

		case 53:
    OneTime( Volume, 2000, NOTE_M_MI);MusicProcess++;
    if(MusicFlag1) {OneTime( Volume, 500, NOTE_MUTE);break;}

		// 55前面 500ms 空音
case 54:
OneTime(Volume, 500, NOTE_MUTE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 55:
OneTime(Volume, 500, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 56:
OneTime(Volume, 500, NOTE_M_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 57:
OneTime(Volume, 500, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 58:
OneTime(Volume, 1000, NOTE_H_DO); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 59:
OneTime(Volume, 500, NOTE_M_LA); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 60:
OneTime(Volume, 500, NOTE_H_DO); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 61:
OneTime(Volume, 500, NOTE_M_LA); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 62:
OneTime(Volume, 500, NOTE_M_SOL); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 63:
OneTime(Volume, 500, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 64:
OneTime(Volume, 500, NOTE_M_DO); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 65:
OneTime(Volume, 250, NOTE_M_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 66:
OneTime(Volume, 250, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 67:
OneTime(Volume, 500, NOTE_M_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 68:
OneTime(Volume, 200, NOTE_H_DO);
OneTime(Volume, 2000, NOTE_M_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 69:
OneTime(Volume, 500, NOTE_M_SOL); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 70:
OneTime(Volume, 500, NOTE_M_SOL); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 71:
OneTime(Volume, 1000, NOTE_M_LA); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 72:
OneTime(Volume, 500, NOTE_M_LA); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 73:
OneTime(Volume, 500, NOTE_H_DO); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 74:
OneTime(Volume, 500, NOTE_H_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 75:
OneTime(Volume, 500, NOTE_H_DO); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 76:
OneTime(Volume, 500, NOTE_M_LA); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 77:
OneTime(Volume, 500, NOTE_M_SOL); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 78:
OneTime(Volume, 500, NOTE_M_LA); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 79:
OneTime(Volume, 500, NOTE_M_SOL); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 80:
OneTime(Volume, 500, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 81:
OneTime(Volume, 500, NOTE_M_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 82:
OneTime(Volume, 500, NOTE_M_SOL); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 83:
OneTime(Volume, 500, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 84:
OneTime(Volume, 200, NOTE_M_RE);
OneTime(Volume, 1000, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 85:
OneTime(Volume, 500, NOTE_M_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 86:
OneTime(Volume, 500, NOTE_M_DO); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 87:
OneTime(Volume, 500, NOTE_M_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 88:
OneTime(Volume, 500, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 89:
OneTime(Volume, 500, NOTE_M_RE); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 90:
OneTime(Volume, 500, NOTE_M_DO); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 91:
OneTime(Volume, 500, NOTE_M_MI); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 92:
OneTime(Volume, 1000, NOTE_M_DO); MusicProcess++;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}

case 93:
OneTime(Volume, 200, NOTE_L_SI);
OneTime(Volume, 1300, NOTE_M_DO); MusicProcess=0;
if(MusicFlag1) {OneTime(Volume, 500, NOTE_MUTE);break;}
    
		
}
	}	
}























