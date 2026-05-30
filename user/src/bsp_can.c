#include "bsp_can.h"
#include "dji_motor.h"
#include "dm_motor.h"
#include "chassis.h"
#include "kfs.h"
#include "lift.h"
#include "weapon.h"

FDCAN_FilterTypeDef  can1_filter;     //can1滤波器
FDCAN_FilterTypeDef  can2_filter;     //can2滤波器
FDCAN_FilterTypeDef  can3_filter; 
uint16_t FOURflag[4]={0,0,0,0};


/**
* @brief can通信滤波器配置
* @param hcanx：can句柄
* @param can_filter: 滤波器句柄
* @date&author  2025/12/24  zhouxy
*/
static void Can_Filter_Config(FDCAN_HandleTypeDef *hfdcanx, FDCAN_FilterTypeDef *fdcan_filter)
{
	                      // filter 0
	fdcan_filter->IdType = FDCAN_STANDARD_ID;                       //标准ID
	fdcan_filter->FilterIndex = 0;                                  //滤波器索引                   
	fdcan_filter->FilterType = FDCAN_FILTER_MASK;                   
	fdcan_filter->FilterConfig = FDCAN_FILTER_TO_RXFIFO0;           //过滤器0关联到FIFO0  
	fdcan_filter->FilterID1 = 0x00;                               
	fdcan_filter->FilterID2 = 0x00;          // enable can filter    滤波器配置

    
	HAL_FDCAN_ConfigFilter(hfdcanx,fdcan_filter);    //滤波器初始化
	HAL_FDCAN_ConfigGlobalFilter(hfdcanx,FDCAN_REJECT,FDCAN_REJECT,FDCAN_REJECT_REMOTE,FDCAN_REJECT_REMOTE);
	HAL_FDCAN_ConfigFifoWatermark(hfdcanx, FDCAN_CFG_RX_FIFO0, 1);
	HAL_FDCAN_Start(hfdcanx);    
	HAL_FDCAN_ActivateNotification(hfdcanx, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);  //开启接收中断
}


/**
* @brief can初始化
* @date&author  2025/12/24  zhouxy
*/
void BSP_CAN_Init(void)
{
    Can_Filter_Config(&hfdcan1, &can1_filter);
    Can_Filter_Config(&hfdcan2, &can2_filter);  //滤波器初始化
    Can_Filter_Config(&hfdcan3, &can3_filter);
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan,uint32_t RxFifo0ITs)  //接收中断
{	
    FDCAN_RxHeaderTypeDef pRxHeader;  //  定义一个结构体，接收电调传来的报文头
	 uint8_t rx_data[8];
   HAL_FDCAN_GetRxMessage(hfdcan,FDCAN_RX_FIFO0, &pRxHeader, rx_data);  //接收从FIFO传来的报文，rx_header和rx_data被放进去赋值通过寄存器
    
	    if(hfdcan->Instance == FDCAN1)//如果是通过CAN1发过来的
	{
		switch (pRxHeader.Identifier){//选择对应ID的底盘电机
//            case 0x10:DMget_motor_measure(&DM4310[0],rx_data);break;
//            case 0x02:DMget_motor_measure(&DM4310[1],rx_data);break;
//			      case 0x20:DMget_motor_measure(&DM4310[2],rx_data);break;
			case 0x305:
              if(FOURflag[0]==0)
							{
								FOURflag[0]=1;
							  DMget_moto_offset_FOUR(&DM4310_FOUR[0],rx_data);
							}
							DMget_motor_measure_FOUR(&DM4310_FOUR[0],rx_data);
			break;
			case 0x306:
              if(FOURflag[1]==0)
							{
								FOURflag[1]=1;
							  DMget_moto_offset_FOUR(&DM4310_FOUR[1],rx_data);
							}							
							DMget_motor_measure_FOUR(&DM4310_FOUR[1],rx_data);
							break;
			case 0x307:
              if(FOURflag[2]==0)
							{
								FOURflag[2]=1;
							  DMget_moto_offset_FOUR(&DM4310_FOUR[2],rx_data);
							}	
							DMget_motor_measure_FOUR(&DM4310_FOUR[2],rx_data);						
							break;
    }}
	
    if(hfdcan->Instance == FDCAN2)//如果是通过CAN1发过来的
	{
		switch (pRxHeader.Identifier){//选择对应ID的底盘电机
            case CHASSIS_MOTOR1_FEEDBACK_ID:{
				DJIget_motor_measure(&chassis_motor1,rx_data);//接收电机通过CAN发过来的信息
				break;
			}
			case CHASSIS_MOTOR2_FEEDBACK_ID:{
				DJIget_motor_measure(&chassis_motor2,rx_data);
				break;
			}
      case CHASSIS_MOTOR3_FEEDBACK_ID:{
				DJIget_motor_measure(&chassis_motor3,rx_data);
				break;
			}
			case CHASSIS_MOTOR4_FEEDBACK_ID:{
				DJIget_motor_measure(&chassis_motor4,rx_data);
				break;
			}
			
		}
        
    }
     if(hfdcan->Instance == FDCAN3)//如果是通过CAN2发过来的
    {

        switch (pRxHeader.Identifier){
					  case CHASSIS_MOTOR1D_FEEDBACK_ID:
				        DJIget_motor_measure(&chassis_motor1D,rx_data);
//              if(RCctrl.CH10<=1000)
//							{
//							  DJIget_moto_offset(&chassis_motor1D,rx_data);
//								DJImotor_Create(&chassis_motor1D, CHASSIS_MOTOR1D_CMD_ID, CHASSIS_MOTOR1D_FEEDBACK_ID, &hfdcan3, DJI_2006,POSITION,PID_POSITION, chassis_motor1D_pid_param,chassis_motor1DP_pid_param);
//							
//							}
				        break;
                      case CHASSIS_MOTOR2D_FEEDBACK_ID:
				        DJIget_motor_measure(&chassis_motor2D,rx_data);
//              if(RCctrl.CH10<=1000)
//							{
//							  DJIget_moto_offset(&chassis_motor2D,rx_data);
//								DJImotor_Create(&chassis_motor2D, CHASSIS_MOTOR2D_CMD_ID, CHASSIS_MOTOR2D_FEEDBACK_ID, &hfdcan3, DJI_2006,POSITION,PID_POSITION, chassis_motor2D_pid_param,chassis_motor2DP_pid_param);
//							
//							}
				        break;
                      case CHASSIS_MOTOR3D_FEEDBACK_ID:
				        DJIget_motor_measure(&chassis_motor3D,rx_data);
//              if(RCctrl.CH10<=1000)
//							{
//							  DJIget_moto_offset(&chassis_motor3D,rx_data);
//								DJImotor_Create(&chassis_motor3D, CHASSIS_MOTOR3D_CMD_ID, CHASSIS_MOTOR3D_FEEDBACK_ID, &hfdcan3, DJI_2006,POSITION,PID_POSITION, chassis_motor3D_pid_param,chassis_motor3DP_pid_param);
//							
//							}
				        break;
                      case CHASSIS_MOTOR4D_FEEDBACK_ID:
				        DJIget_motor_measure(&chassis_motor4D,rx_data);
//              if(RCctrl.CH10<=1000)
//							{
//							  DJIget_moto_offset(&chassis_motor4D,rx_data);
//								DJImotor_Create(&chassis_motor4D, CHASSIS_MOTOR4D_CMD_ID, CHASSIS_MOTOR4D_FEEDBACK_ID, &hfdcan3, DJI_2006,POSITION,PID_POSITION, chassis_motor4D_pid_param,chassis_motor4DP_pid_param);
//							
//							}
				        break;

        }
			
    }

}

uint8_t fdcanx_send_data(FDCAN_HandleTypeDef *hfdcan, uint16_t id, uint8_t *data, uint32_t len)
{	
    FDCAN_TxHeaderTypeDef pTxHeader;
    pTxHeader.Identifier=id;
    pTxHeader.IdType=FDCAN_STANDARD_ID;
    pTxHeader.TxFrameType=FDCAN_DATA_FRAME;
	
	if(len<=8)
		pTxHeader.DataLength = len;
	if(len==12)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_12;
	if(len==16)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_16;
	if(len==20)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_20;
	if(len==24)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_24;
	if(len==32)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_32;
	if(len==48)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_48;
	if(len==64)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_64;
	
    pTxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    pTxHeader.BitRateSwitch=FDCAN_BRS_ON;
    pTxHeader.FDFormat=FDCAN_FD_CAN;
    pTxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    pTxHeader.MessageMarker=0;
 
	if(HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &pTxHeader, data)!=HAL_OK) 
		return 1;//发送
	return 0;	
}























