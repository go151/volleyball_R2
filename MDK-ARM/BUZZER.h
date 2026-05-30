#ifndef __BUZZER_H__
#define __BUZZER_H__
 
/*********************************************************
 *  STM32H723 蜂鸣器/喇叭 PWM 音符宏定义
 *  固定配置：TIM总线时钟240MHz  PSC = 239
 *  切换音调：修改 ARR
 *  控制音量：CCR = ARR / 2 固定50%占空比
 *********************************************************/

//==================== 低音 ARR ====================
#define NOTE_L_DO     3816U    // 低音1 Do  262Hz
#define NOTE_L_RE     3400U    // 低音2 Re  294Hz
#define NOTE_L_MI     3029U    // 低音3 Mi  330Hz
#define NOTE_L_FA     2864U    // 低音4 Fa  349Hz
#define NOTE_L_SOL    2550U    // 低音5 Sol 392Hz
#define NOTE_L_LA     2272U    // 低音6 La  440Hz
#define NOTE_L_SI     2023U    // 低音7 Si  494Hz

//==================== 中音 ARR ====================
#define NOTE_M_DO     1911U    // 中音1 Do  523Hz
#define NOTE_M_RE     1703U    // 中音2 Re  587Hz
#define NOTE_M_MI     1516U    // 中音3 Mi  659Hz
#define NOTE_M_FA     1432U    // 中音4 Fa  698Hz
#define NOTE_M_SOL    1275U    // 中音5 Sol 784Hz
#define NOTE_M_LA     1135U    // 中音6 La  880Hz
#define NOTE_M_SI     1011U    // 中音7 Si  988Hz

//==================== 高音 ARR ====================
#define NOTE_H_DO      954U    // 高音1 Do  1047Hz
#define NOTE_H_RE      850U    // 高音2 Re  1175Hz
#define NOTE_H_MI      757U    // 高音3 Mi  1319Hz
#define NOTE_H_FA      715U    // 高音4 Fa  1397Hz
#define NOTE_H_SOL     637U    // 高音5 Sol 1568Hz
#define NOTE_H_LA      567U    // 高音6 La  1760Hz
#define NOTE_H_SI      505U    // 高音7 Si  1976Hz

//==================== 静音/休止符 ====================
#define NOTE_MUTE       0U     // 不发声

//==================== 通用50%音量宏 ====================
// 传入对应音符ARR，自动计算50%占空比CCR
#define PWM_VOLUME_HALF(ARR)    ((ARR) / 2U)
#define LanTingXu 0
#include "main.h"
#include "tim.h"

extern uint8_t Song;
extern int delay;
extern uint16_t MusicFlag1,MusicProcessLanTingxu,MusicProcessBirth,MusicProcessYIJianMei;
extern int Volume;
void OneTime(int Volume,int delay,int which);
void LanTingXuSong(void);
void YiJianMeiSong(void);








#endif
