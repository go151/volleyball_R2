#include "dm_motor.h"


static float uint_to_float(unsigned short int X_int, float X_min, float X_max, int Bits){//将需要值映射在0到65535（比如）之间
    float span = X_max - X_min;
    float offset = X_min;
    return ((float)X_int)*span/((float)((1<<Bits)-1)) + offset;
}

static uint16_t float_to_uint(float X_float, float X_min, float X_max, int bits){
    float span = X_max - X_min;
    float offset = X_min;
    return (uint16_t) ((X_float-offset)*((float)((1<<bits)-1))/span);
}


/*******************************************************************************************
  * @Func			DM_Motor_CMD(CAN_HandleTypeDef *hcan,moto_info_t *motor,Motor_CMD CMD)
  * @Brief    达妙电机控制帧(未测试)
  * @Param		
  * @Retval		None
  * @Date     2024/12/26
 *******************************************************************************************/
HAL_StatusTypeDef DM_Motor_CMD(DM_MotorModule *obj,Motor_CMD CMD)
{
		uint8_t             tx_data[8];
	
    FDCAN_TxHeaderTypeDef pTxHeader;
//    pTxHeader.Identifier= 2;
    pTxHeader.IdType=FDCAN_STANDARD_ID;
    pTxHeader.TxFrameType=FDCAN_DATA_FRAME;
		pTxHeader.DataLength = 8;
    pTxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    pTxHeader.BitRateSwitch=FDCAN_BRS_ON;
    pTxHeader.FDFormat=FDCAN_FD_CAN;
    pTxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    pTxHeader.MessageMarker=0;
	
	if(obj->super_motor.mode==MIT) pTxHeader.Identifier= obj->super_motor.id;
	else if(obj->super_motor.mode==POSITION) pTxHeader.Identifier= obj->super_motor.id+0x100;
	else pTxHeader.Identifier= obj->super_motor.id+0x200;

	
	tx_data[0] = 0xFF;
	tx_data[1] = 0xFF;
	tx_data[2] = 0xFF;
	tx_data[3] = 0xFF;
	tx_data[4] = 0xFF;
	tx_data[5] = 0xFF;
	tx_data[6] = 0xFF;
	switch(CMD){
		case Motor_Enable ://使能DM电机
			tx_data[7] = 0xFC;
			obj->state = ON;
			break;
		case Motor_Disable ://失能电机
			tx_data[7] = 0xFD;
			obj->state = OFF;
			break;
		case Motor_Save_Zero_Position ://保存零点位置
			tx_data[7] = 0xFE;
			break;
		case Motor_Clear_Error :
			tx_data[7] = 0xFB;
			break;
		default:
			break;
	}
	return HAL_FDCAN_AddMessageToTxFifoQ(&obj->super_motor.hcan, &pTxHeader, tx_data);  

}        



void DMget_motor_measure(DM_MotorModule *obj, uint8_t rx_data[8])//
{
    uint16_t  P_int = ((uint16_t)(rx_data[1]) <<8) | ((uint16_t)(rx_data[2]));
	  uint16_t  V_int = ((uint16_t)(rx_data[3]) <<4) | ((uint16_t)(rx_data[4])>>4);
    uint16_t  T_int = ((uint16_t)(rx_data[4]&0xF) <<8) | ((uint16_t)(rx_data[5]));
    float P_MAX = 12.5f;		
	float V_MAX = 30.f; 			
	float T_MAX = 10.f;
	switch (obj->super_motor.model){
		case DM_J4310:{
			P_MAX = 60.0f;		
			V_MAX = 30.f; 			
			T_MAX = 10.f;				
			break;
		}
		case DM_6220:{
			P_MAX = 12.566f;
			V_MAX = 45.f; 
			T_MAX = 10.f;
			break;
		}
        case DM_2325:{  
			P_MAX = 12.5f;		
			V_MAX = 30.f; 			
			T_MAX = 10.f;				
			break;
        default:
            break;
        }
    }
        obj->state = (Motor_State)(rx_data[0]>>4);
        obj->last_position = obj->position;
		obj->position = uint_to_float(P_int,-P_MAX,P_MAX,16);
		obj->speed_w = uint_to_float(V_int,-V_MAX,V_MAX,12);
		obj->torque =  uint_to_float(T_int,-T_MAX,T_MAX,12);			
		obj->temp_mos  = (float)(rx_data[6]);
		obj->temp_rotor  =(float)(rx_data[7]);
			
			if (obj->position - obj->last_position > 6.28318f)
				obj->round_cnt -= 4;
			else if (obj->position - obj->last_position < -6.28318f)
			{
				obj->round_cnt += 4;
			}
			
			obj->abs_position = fmod(obj->position,6.28318f);
			if (obj->abs_position > 3.14159f)
			{
					obj->abs_position -= 6.28318f;
			}
			else if (obj->abs_position < -3.14159f)
			{
					obj->abs_position += 6.28318f;
			}
			
			if(obj->state == OFF)
			{
				obj->state = ON;
			}
		
	
}

/*******************************************************************************************
  * @Func		DM_Motor_CAN_TxMessage(CAN_HandleTypeDef *hcan,mit_info_t *motor,float Postion, float Velocity, float KP, float KD, float Torque)
	* @Brief    MIT控制达妙电机
  * @Param		标准ID
  * @Retval		None 
  * @Date     2024/12/30
 *******************************************************************************************/

HAL_StatusTypeDef DMset_mit_data(DM_MotorModule *obj, float Position, float Velocity, float KP, float KD, float Torque)
{
	uint8_t             tx_data[8];
    uint16_t Postion_Tmp,Velocity_Tmp,Torque_Tmp,KP_Tmp,KD_Tmp;


	  FDCAN_TxHeaderTypeDef pTxHeader;
    pTxHeader.Identifier=obj->super_motor.id;
    pTxHeader.IdType=FDCAN_STANDARD_ID;
    pTxHeader.TxFrameType=FDCAN_DATA_FRAME;
		pTxHeader.DataLength = 8;
    pTxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    pTxHeader.BitRateSwitch=FDCAN_BRS_ON;
    pTxHeader.FDFormat=FDCAN_FD_CAN;
    pTxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    pTxHeader.MessageMarker=0;

	static float P_MAX,V_MAX,T_MAX;
	
	switch(obj->super_motor.model){
		 
		case DM_MIT:
		case DM_6220 :
			P_MAX = 20.0f; V_MAX = 45.f; T_MAX = 10.f;
			break;
        case DM_J4310 :
			P_MAX = 60.0f; V_MAX = 30.f; T_MAX = 10.f;
			break;
      
		default:
			break;   
	}

	switch (obj->super_motor.mode){
		case POSITION:
			Postion_Tmp  =  float_to_uint(Position,-P_MAX,P_MAX,16) ;
			Velocity_Tmp =  float_to_uint(Velocity,-V_MAX,V_MAX,12);
			Torque_Tmp = float_to_uint(Torque,0,0,12);
			KP_Tmp = float_to_uint(KP,0,500,12);
			KD_Tmp = float_to_uint(KD,0,5,12);
			break;
		case SPEED:
			Postion_Tmp  =  float_to_uint(0,0,0,16) ;
			Velocity_Tmp =  float_to_uint(Velocity,-V_MAX,V_MAX,12);
			Torque_Tmp = float_to_uint(0,0,0,12);
			KP_Tmp = float_to_uint(0,0,0,12);
			KD_Tmp = float_to_uint(KD,0,5,12);
			break;
        case MIT:
      Postion_Tmp  =  float_to_uint(Position,-P_MAX,P_MAX,16) ;
			Velocity_Tmp =  float_to_uint(Velocity,-V_MAX,V_MAX,12);
			Torque_Tmp = float_to_uint(Torque,-T_MAX,T_MAX,12);//转矩
			KP_Tmp = float_to_uint(KP,0,500,12);
			KD_Tmp = float_to_uint(KD,0,5,12);
            break;
	}
		
	tx_data[0] = (Postion_Tmp>>8);
	tx_data[1] = (Postion_Tmp);
	tx_data[2] = (uint8_t)(Velocity_Tmp>>4);
	tx_data[3] = (uint8_t)((Velocity_Tmp&0x0F)<<4) | (uint8_t)(KP_Tmp>>8);
	tx_data[4] = (uint8_t)(KP_Tmp);
	tx_data[5] = (uint8_t)(KD_Tmp>>4);
	tx_data[6] = (uint8_t)((KD_Tmp&0x0F)<<4) | (uint8_t)(Torque_Tmp>>8);
	tx_data[7] = (uint8_t)(Torque_Tmp);

	return 	HAL_FDCAN_AddMessageToTxFifoQ(&obj->super_motor.hcan, &pTxHeader, tx_data); 

}


/*******************************************************************************************
  * @Func			DM_Motor_CAN__POS_TxMessage(CAN_HandleTypeDef *hcan,mit_info_t *motor,float Postion, float Velocity)
* @Brief    位置速度控制达妙电机，本质是控制电机转到指定位置，速度是最大速度
  * @Param		帧ID=CAN ID+0x100
  * @Retval		None 
  * @Date     2024/12/30
 *******************************************************************************************/
HAL_StatusTypeDef DMset_posvel_data(DM_MotorModule *obj, float Position, float Velocity)
{

	uint8_t             tx_data[8];
	
	uint8_t *pbuf,*vbuf;
  pbuf=(uint8_t*)&Position;//把Position的地址给pbuf
	vbuf=(uint8_t*)&Velocity;
	
	  FDCAN_TxHeaderTypeDef pTxHeader;
    pTxHeader.Identifier=obj->super_motor.id+0x100;
    pTxHeader.IdType=FDCAN_STANDARD_ID;
    pTxHeader.TxFrameType=FDCAN_DATA_FRAME;
		pTxHeader.DataLength = 8;
    pTxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    pTxHeader.BitRateSwitch=FDCAN_BRS_ON;
    pTxHeader.FDFormat=FDCAN_FD_CAN;
    pTxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    pTxHeader.MessageMarker=0;
   
	tx_data[0] = *pbuf;
	tx_data[1] = *(pbuf+1);
	tx_data[2] = *(pbuf+2);
	tx_data[3] = *(pbuf+3);
	tx_data[4] = *vbuf;
	tx_data[5] = *(vbuf+1);
	tx_data[6] = *(vbuf+2);
	tx_data[7] = *(vbuf+3);

	return 	HAL_FDCAN_AddMessageToTxFifoQ(&obj->super_motor.hcan, &pTxHeader, tx_data); 

}

/*******************************************************************************************
  * @Func	    Motor_Init(moto_info_t *moto_info, uint16_t motor_id, Motor_Model motorModel, Ctrl_mode ctrlMode, 
													PID_Type_e pidType, float pid_spd_Param[PID_PARAMETER_NUM], float pid_pos_Param[PID_PARAMETER_NUM])
  * @Brief    达妙电机初始化
  * @Param		
  * @Retval		None
  * @Date     2025/07/02
 *******************************************************************************************/
void DMmotor_Create (DM_MotorModule *obj, 
                     uint16_t command_id, 
                     uint16_t master_id,
                     FDCAN_HandleTypeDef *hcan, 
                     Motor_Model motorModel,
                     Ctrl_mode mode,
                     PID_Type_e pidType, 
                     float pid_Param_pos[PID_PARAMETER_NUM])
{
    
    MotorModule_Create(&obj->super_motor, command_id,hcan, motorModel, mode);
    
    obj->Master_ID = master_id;
    obj->send_cmd = DM_Motor_CMD;//使obj里的send_cmd函数指针指向DM_Motor_CMD函数
    obj->set_mit_data = DMset_mit_data;
    obj->set_posvel_data = DMset_posvel_data;
    obj->get_motor_measure = DMget_motor_measure;
    
    obj->position = 0.f;
    obj->last_position = 0.f;
    obj->abs_position = 0.f;
    obj->speed_w = 0.f;
    obj->torque = 0.f;
	switch (obj->super_motor.mode){ 
	  		case POSITION :
			PID_Init(&obj->pid_pos, pidType, pid_Param_pos);
            break;
		    case SPEED :
			break;
        case MIT:
      break;
}
	}

/**
************************************************************************
* @brief:      	save_pos_zero: 保存位置零点函数
* @param[in]:   hcan:     指向CAN_HandleTypeDef结构的指针
* @param[in]:   motor_id: 电机ID，指定目标电机
* @param[in]:   mode_id:  模式ID，指定要保存位置零点的模式
* @retval:     	void
* @details:    	通过CAN总线向特定电机发送保存位置零点的命令
************************************************************************
**/
void save_pos_zero(DM_MotorModule *obj, uint16_t mode_id)
{
	uint8_t data[8];
	
	
	data[0] = 0xFF;
	data[1] = 0xFF;
	data[2] = 0xFF;
	data[3] = 0xFF;
	data[4] = 0xFF;
	data[5] = 0xFF;
	data[6] = 0xFF;
	data[7] = 0xFE;
	
		FDCAN_TxHeaderTypeDef pTxHeader;
    pTxHeader.Identifier=obj->super_motor.id+mode_id;
    pTxHeader.IdType=FDCAN_STANDARD_ID;
    pTxHeader.TxFrameType=FDCAN_DATA_FRAME;
		pTxHeader.DataLength = 8;
    pTxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    pTxHeader.BitRateSwitch=FDCAN_BRS_ON;
    pTxHeader.FDFormat=FDCAN_FD_CAN;
    pTxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    pTxHeader.MessageMarker=0;
	 	HAL_FDCAN_AddMessageToTxFifoQ(&obj->super_motor.hcan, &pTxHeader, data); 
}


/***********************一拖四模式*********************/


void DMmotor_Create_FOUR(DM_MotorModule_FOUR *obj, 
                     PID_Type_e pidType, 
                     float pid_Param_pos[PID_PARAMETER_NUM],
										 float pid_Param_spd[PID_PARAMETER_NUM])
{
          obj->angle=0;
	        obj->speed_rpm=0;
	        obj->round_cnt=0;
	        obj->temp=0;
	        obj->temp_mos=0;
	        obj->total_angle=0;
          
					PID_Init(&obj->pid_pos, pidType, pid_Param_pos);
				  PID_Init(&obj->pid_spd, pidType, pid_Param_spd);

}

float Motor_PID_Calculate_FOUR(DM_MotorModule_FOUR *obj, float input)
{
	
	static float output,v;
	v=f_PID_Calculate(&obj->pid_pos, input, obj->total_angle);

	output = f_PID_Calculate(&obj->pid_spd,v , obj->speed_rpm);
	return output;
}

void DMget_motor_measure_FOUR(DM_MotorModule_FOUR *obj, uint8_t rx_data[8])//
{
	    obj->last_angle = obj->angle;
      obj->angle= (int16_t)(rx_data[0]<<8 | rx_data[1]);
	    obj->speed_rpm = ((int16_t)(rx_data[2]<<8 | rx_data[3]));
      obj->real_current = (int16_t)(rx_data[4]<<8 | rx_data[5])/-5;
	    
      if(obj->angle - obj->last_angle > 4096)//逆着转了一圈
			obj->round_cnt --;
			else if (obj->angle - obj->last_angle < -4096)//顺着转了一圈
			obj->round_cnt ++;
			obj->total_angle = obj->round_cnt * 8192 + obj->angle - obj->offset_angle;
}

HAL_StatusTypeDef DMset_motor_data_FOUR(FDCAN_HandleTypeDef *hcan, uint32_t id, int16_t data1, int16_t data2, int16_t data3, int16_t data4)
{

    FDCAN_TxHeaderTypeDef pTxHeader;
    pTxHeader.Identifier=id;
    pTxHeader.IdType=FDCAN_STANDARD_ID;
    pTxHeader.TxFrameType=FDCAN_DATA_FRAME;//?
		pTxHeader.DataLength = 8;
    pTxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;//?
    pTxHeader.BitRateSwitch=FDCAN_BRS_OFF;//?
    pTxHeader.FDFormat=FDCAN_CLASSIC_CAN;
    pTxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    pTxHeader.MessageMarker=0;
    uint8_t             tx_data[8];//发送的数据
	
	tx_data[1] = (data1>>8)&0xff;//把函数传进来的数据给tx_data，再发出去
	tx_data[0] =    (data1)&0xff;
	tx_data[3] = (data2>>8)&0xff;
	tx_data[2] =    (data2)&0xff;
	tx_data[5] = (data3>>8)&0xff;
	tx_data[4] =    (data3)&0xff;
	tx_data[7] = (data4>>8)&0xff;
	tx_data[6] =    (data4)&0xff;
//	while((hfdcan1.Instance->TXFQS&FDCAN_TXFQS_TFQF)!=0U);
	return HAL_FDCAN_AddMessageToTxFifoQ(hcan, &pTxHeader, tx_data); 

}

void DMget_moto_offset_FOUR(DM_MotorModule_FOUR *obj, uint8_t rx_data[8])
{
	obj->angle = (uint16_t)(rx_data[0]<<8 | rx_data[1]) ;
	obj->offset_angle = obj->angle;//将当前读取到的绝对角度值记录为“零点”。
}



