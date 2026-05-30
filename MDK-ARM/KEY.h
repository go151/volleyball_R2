#ifndef __KEY_H__
#define __KEY_H__
 
#include "main.h"
extern int count,ifPressed,totaltime,KeyTime;
extern int times;
extern int temp1,temp2,temp3;
extern uint8_t flagKey,lastflagKey;
uint8_t GetTick(void);
uint8_t GetState1(void);
void GetState2(void);
#endif
