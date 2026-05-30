#include "remote_control.h"
#include <math.h>
//这个文件是SBUS协议信号

	
		//SWA-CH5 SWB-CH6 SWC-CH7 SWD-CH8 VRA-CH9 VRB-CH10
		//SWA-CH5设置为急停或解锁
		//SWB-CH6设置为手动或者自动接发，手动则不会
		//VRA-CH9 VRB-CH10 用于操作接发机构
		//SWD-CH8 VRA-CH9 作为空闲预留
	
 	
uint8_t SBUS_MultiRx_Buf[2][SBUS_RX_BUF_NUM];

#define ABS(x)  ((x) >= 0? (x) : -(x))//绝对值函数

int16_t data_convert(
    int src, int src_min, int src_max,
    float dst_low, float dst_high,
    float deadband  
) {
    if (src_min > src_max) {
        int tmp = src_min; src_min = src_max; src_max = tmp;
    }
    if (src_min == src_max) {
        return (int16_t)roundf(dst_low);
    }

    int clamped = (src < src_min) ? src_min : ((src > src_max) ? src_max : src);
    float ratio = (float)(clamped - src_min) / (float)(src_max - src_min);
    float dst = ratio * (dst_high - dst_low) + dst_low;

    if (fabsf(dst) < deadband) {
        dst = 0.0f;
    }

    return (int16_t)roundf(dst);
}
Remote_Info_Typedef RCctrl={
	.online_cnt = 0xFAU,//计时
	.rc_lost = true,    //默认为离线状态
};

/**
* @brief SBUS数据协议解析
* @param sbus_buf：接收缓冲数组
* @param Remote_Ctrl: 遥控器数据结构体
* @date&author  2025/12/25  zhouxy
*/

void SBUS_TO_RC(volatile const uint8_t *sbus_buf, Remote_Info_Typedef  *Remote_Ctrl)//缓冲区的指针和遥控器的指针，这里注意SBUS协议一个通道有11个BIT
{
	if (sbus_buf == NULL || Remote_Ctrl == NULL) return;//没收到信号就返回

    /* Channel 0, 1, 2, 3 */
	Remote_Ctrl->CH1 = ((((uint16_t)sbus_buf[2] << 8) | (uint16_t)sbus_buf[1]) & 0x07FF);
	Remote_Ctrl->CH2 = ((int16_t)sbus_buf[ 2] >> 3 | ((int16_t)sbus_buf[ 3] << 5 )) & 0x07FF;
	Remote_Ctrl->CH3 = ((int16_t)sbus_buf[ 3] >> 6 | ((int16_t)sbus_buf[ 4] << 2 ) | (int16_t)sbus_buf[ 5] << 10 ) & 0x07FF;
    Remote_Ctrl->CH4 = ((int16_t)sbus_buf[ 5] >> 1 | ((int16_t)sbus_buf[ 6] << 7 )) & 0x07FF;
	Remote_Ctrl->CH5 = ((int16_t)sbus_buf[ 6] >> 4 | ((int16_t)sbus_buf[ 7] << 4 )) & 0x07FF;
	Remote_Ctrl->CH6 = ((int16_t)sbus_buf[ 7] >> 7 | ((int16_t)sbus_buf[ 8] << 1 ) | (int16_t)sbus_buf[9] << 9 ) & 0x07FF;
	Remote_Ctrl->CH7 = ((int16_t)sbus_buf[ 9] >> 2 | ((int16_t)sbus_buf[ 10] << 6)) & 0x07FF;
	Remote_Ctrl->CH8 = ((int16_t)sbus_buf[10] >> 5 | ((int16_t)sbus_buf[ 11] << 3)) & 0x07FF;
	Remote_Ctrl->CH9 = ((int16_t)sbus_buf[12] << 0 | ((int16_t)sbus_buf[13] << 8 )) & 0x07FF;
	Remote_Ctrl->CH10 = ((int16_t)sbus_buf[13] >> 3 | ((int16_t)sbus_buf[14] << 5 )) & 0x07FF;
	Remote_Ctrl->CH11 = ((int16_t)sbus_buf[14] >> 6 | ((int16_t)sbus_buf[15] << 2 ) | (int16_t)sbus_buf[16] << 10 ) & 0x07FF;
	Remote_Ctrl->CH12 = ((int16_t)sbus_buf[16] >> 1 | ((int16_t)sbus_buf[17] << 7 )) & 0x07FF;
    Remote_Ctrl->CH13 = ((int16_t)sbus_buf[17] >> 4 | ((int16_t)sbus_buf[18] << 4 )) & 0x07FF;
    Remote_Ctrl->CH14 = ((int16_t)sbus_buf[18] >> 7 | ((int16_t)sbus_buf[19] << 1 ) | (int16_t)sbus_buf[20] << 9  ) & 0x07FF;
    Remote_Ctrl->CH15 = ((int16_t)sbus_buf[20] >> 2 | ((int16_t)sbus_buf[21] << 6 )) & 0x07FF;
    Remote_Ctrl->CH16 = ((int16_t)sbus_buf[21] >> 5 | ((int16_t)sbus_buf[22] << 3 )) & 0x07FF;
    

    (sbus_buf[23] == 0x00) ? (Remote_Ctrl->rc_lost = false) : (Remote_Ctrl->rc_lost = true);//由标志位判断是否在线
		/* reset the online count */
		Remote_Ctrl->online_cnt = 0xFAU;//重置计时器

		
}
		
		
float MYdata_convert(int src, int src_min, int src_max,float dst_low, float dst_high, float deadband  ) 
{
    if (src_min > src_max) {
        int tmp = src_min; src_min = src_max; src_max = tmp;
    }
    if (src_min == src_max) {
        return dst_low;
    }

    int clamped = (src < src_min) ? src_min : ((src > src_max) ? src_max : src);
    float ratio = (float)(clamped - src_min) / (float)(src_max - src_min);
    float dst = ratio * (dst_high - dst_low) + dst_low;

    if (fabsf(dst) < deadband) {
        dst = 0.0f;
    }

    return dst;
}
		/* reset the lost flag */
//		Remote_Ctrl->rc_lost = false;
