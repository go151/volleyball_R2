#include "master_control.h"


//接受数据包
 uint8_t RxPacket8[6];//接受缓存数组
 uint8_t RxFlag8;//接完完数据包后置1
 uint8_t data8;
 uint8_t pRxPacket8=0;
 uint8_t tiaoshi=0;



//移植printf
 int fputc(int ch,FILE *f)
 {
    HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,HAL_MAX_DELAY);
     return ch;
 }
PID_Info_TypeDef* current_pid = &chassis_motor1.pid_spd;  // 可动态切换

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    printf("KOK");
    if (huart->Instance == USART1) {
        static uint8_t RxState8 = 0;
        static uint8_t rx_buffer[6];   // 接收缓冲区，大小与数据包一致
        static uint8_t rx_index = 0;

        if (RxState8 == 0) {
            if (data8 == 0xAA) {        // 帧头
                RxState8 = 1;
                rx_index = 0;
            }
        } else if (RxState8 == 1) {
            rx_buffer[rx_index++] = data8;
            if (rx_index >= 6) {        // 接收完成
                RxState8 = 2;
            }
        } else if (RxState8 == 2) {
            if (data8 == 0x55) {        // 帧尾
                // 解析数据
                uint8_t param_index = rx_buffer[0];       // 参数索引 0~5
                float param_value;
                // 将后4个字节转为float（假设小端模式）
                memcpy(&param_value, &rx_buffer[1], 4);

                // 更新对应的PID参数
                if (current_pid != NULL && param_index < PID_PARAMETER_NUM) {
                    float *para = (float*)&(current_pid->param);
                    para[param_index] = param_value;
                    // 可选：重新初始化PID，清除积分等
                    current_pid->PID_Param_Init(current_pid, para);
                    current_pid->PID_Calc_Clear(current_pid);
                    Chassis_Stop(&Chassis);
                    printf("OK");
                }

                RxState8 = 0;
                RxFlag8 = 1;  // 置标志位通知主循环
            } else {
                // 帧尾错误，重新同步
                RxState8 = 0;
            }
        }

        // 继续接收下一字节
        HAL_UART_Receive_IT(&huart1, &data8, 1);
    }
}