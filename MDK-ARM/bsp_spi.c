#include "ws2812.h"


#define WS2812_LowLevel    0xC0     // 0Ты
#define WS2812_HighLevel   0xF0     // 1Ты
//uint8_t flag=0;
//uint8_t txbuf[24];
//uint8_t res = 0;
//void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//  if(flag==0)
//   {
//     HAL_SPI_Transmit_DMA(&WS2812_SPI_UNIT, &res, 0);
//		 flag++;
//    }else if(flag==1)
//	 {
//     WS2812_Ctrl(1,2,3);
//		 flag++;
//	 }else if(flag==2)
//	 {
//   for (int i = 0; i < 100; i++)
//    {
//        HAL_SPI_Transmit_DMA(&WS2812_SPI_UNIT, &res, 1);
//			if(i==99)
//			{
//				flag=3;
//			}
//    }
//	 }
//}

