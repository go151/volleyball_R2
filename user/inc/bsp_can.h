#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__

#include "fdcan.h"
extern uint8_t      rx_data[8];
void BSP_CAN_Init(void);
uint8_t fdcanx_send_data(FDCAN_HandleTypeDef *hfdcan, uint16_t id, uint8_t *data, uint32_t len);
#endif

