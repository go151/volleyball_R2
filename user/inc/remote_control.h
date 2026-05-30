#ifndef __REMOTE_CONTROL_H__
#define __REMOTE_CONTROL_H__

#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include <stdio.h>
#include <string.h>

#define SBUS_RX_BUF_NUM 50u
#define RC_FRAME_LENGTH 25u
#define RC_CH_VALUE_OFFSET 1024U
//R_HORIZONTAL
#define CH1_LOW     240        //LEFT        
#define CH1_HIGH    1807         //RIGHT
#define CH1_MID     1024        //MID
//#define LR_TRANSLATION          data_convert(RCctrl.CH1, CH1_LOW, CH1_HIGH, -ACCEL, ACCEL)
//R_UPRIGHT
#define CH2_LOW     240         //DOWN
#define CH2_HIGH    1807        //UP
#define CH2_MID     1024        //MID
//#define FB_TRANSLATION          data_convert(RCctrl.CH2, CH2_LOW, CH2_HIGH, -ACCEL, ACCEL)
//#define KFS_LIFT                data_convert(RCctrl.CH2, CH2_LOW, CH2_HIGH, -3, 3)
//L_UPRIGHT
#define CH3_LOW     240         //DOWN
#define CH3_HIGH    1807        //UP
//#define ACCEL                   data_convert(RCctrl.CH3, CH3_LOW, CH3_HIGH, 0, 100)
//L_HORIZONTAL
#define CH4_LOW     240         //LEFT
#define CH4_HIGH    1807        //RIGHT
#define CH4_MID     1024         //MID
//#define ROTATION                data_convert(RCctrl.CH4, CH4_LOW, CH4_HIGH, -ACCEL, ACCEL)


//CHANNAL_C
#define CH5_LOW     240         //DOWN
#define CH5_HIGH    1807        //UP
//#define CH5_MID     1024        //MID


//CHANNEL_D
#define CH6_LOW     240        //DOWN
#define CH6_HIGH    1807         //UP

//CHANNEL_G
#define CH7_LOW     240         //BACK
#define CH7_HIGH    1807        //FRONT
#define CH7_MID     1024        //MID


//CHANNEL_H
#define CH8_LOW     240         //PRESS
#define CH8_HIGH    1807        //RELEASE

//CHANNEL_F（改成旋钮）
#define CH9_LOW     240         // 逆时针转到底
#define CH9_HIGH    1807        // 顺时针转到底
//#define VRA_KNOB                data_convert(RCctrl.CH9, CH9_LOW, CH9_HIGH, 0, 1000) // 映射为0-100

//CHANNEL_A（改成旋钮）
#define CH10_LOW    240        // 逆时针转到底
#define CH10_HIGH   1807         // 顺时针转到底 
//#define VRB_KNOB                data_convert(RCctrl.CH10, CH10_LOW, CH10_HIGH, 0, 1000) // 映射为0-1000 


/**
//CHANNEL_F
#define CH9_LOW     306         //BACK
#define CH9_HIGH    1694        //FRONT


//CHANNEL_A
#define CH10_LOW    1692        //UP
#define CH10_HIGH   292         //DOWN
*/
typedef  struct
{
    uint16_t CH1;  
    uint16_t CH2;  
    uint16_t CH3;  
    uint16_t CH4;
    uint16_t CH5;
    uint16_t CH6;
    uint16_t CH7;
    uint16_t CH8;
    uint16_t CH9;
    uint16_t CH10;
	uint16_t CH11;
	uint16_t CH12;
    uint16_t CH13;
    uint16_t CH14;
    uint16_t CH15;
    uint16_t CH16;

	bool rc_lost;   /*!< lost flag */
	uint8_t online_cnt;   /*!< online count */
	bool unlock;//解锁
	bool handle;//手动操作
    int16_t accel;        // 当前油门增益 (0-100)
    int16_t vx;           // 左右平移速度
    int16_t vy;           // 前后平移速度
    int16_t vw;           // 自旋速度
    int16_t lift;         // 升降微调量
    int16_t vra;          // 旋钮A值 (0-1000)
    int16_t vrb;          // 旋钮B值 (0-1000)
} Remote_Info_Typedef;



extern uint8_t SBUS_MultiRx_Buf[2][SBUS_RX_BUF_NUM];
extern Remote_Info_Typedef RCctrl;
void SBUS_TO_RC(volatile const uint8_t *sbus_buf, Remote_Info_Typedef  *Remote_Ctrl);
int16_t data_convert(int src, int src_min, int src_max, float dst_low, float dst_high,float deadband);
// 接口函数：一键获取所有逻辑数据
		void RC_Get_Control_Logic(Remote_Info_Typedef *Remote_Ctrl);
float MYdata_convert(int src, int src_min, int src_max,float dst_low, float dst_high, float deadband  ) ;
#endif
