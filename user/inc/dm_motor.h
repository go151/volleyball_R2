#ifndef __DM_MOTOR_H__
#define __DM_MOTOR_H__


#include "fdcan.h"
#include "motor.h"
#include "math.h"

typedef enum
{
	Motor_Enable,
	Motor_Disable,
	Motor_Save_Zero_Position,
	Motor_Clear_Error,
}Motor_CMD;

typedef enum
{
	OFF,
	ON,
	OVER_VOL,
	LOW_VOL,
	OVER_CUR,
	MOS_HOT,
	LOSS,
	OVER_LOAD
	
}Motor_State;

typedef struct _DM_MotorModule{
    MotorModule super_motor;
    struct _DM_MotorModule* self;
    Motor_State state;
	uint8_t			Master_ID;
	PID_Info_TypeDef 	pid_pos;
	float 	position;
	float 	last_position;
	float	  abs_position;
	float 	speed_w;
	float 	torque;
	
	uint8_t  	temp_mos;
	uint8_t  	temp_rotor;
	int32_t		round_cnt;
	uint8_t		buf_idx;
	uint16_t	angle_buf[FILTER_BUF_LEN];
	uint16_t	fited_angle;
	uint32_t	msg_cnt;
    
    HAL_StatusTypeDef (*send_cmd)(struct _DM_MotorModule *obj,Motor_CMD CMD);
    void (*get_motor_measure)(struct _DM_MotorModule *obj, uint8_t rx_data[8]);
	HAL_StatusTypeDef (*set_mit_data)(struct _DM_MotorModule *obj, float Position, float Velocity, float KP, float KD, float Torque);
    HAL_StatusTypeDef (*set_posvel_data)(struct _DM_MotorModule *obj, float Position, float Velocity);
}DM_MotorModule;


typedef struct _DM_MotorModule_FOUR{

	PID_Info_TypeDef	pid_spd;
	PID_Info_TypeDef 	pid_pos;
	int16_t	 	speed_rpm;
	uint16_t 	angle;
	int16_t  	real_current;
	uint8_t  	temp;
	int32_t		total_angle;
  uint16_t 	last_angle;
	int32_t		round_cnt;
	uint8_t  	temp_mos;
  uint16_t  offset_angle;
}DM_MotorModule_FOUR;

extern DM_MotorModule DM4310[3];
extern DM_MotorModule DM2325[2];
extern DM_MotorModule_FOUR DM4310_FOUR[3];
void DMmotor_Create_FOUR(DM_MotorModule_FOUR *obj, 
                     PID_Type_e pidType, 
                     float pid_Param_pos[PID_PARAMETER_NUM],
										 float pid_Param_spd[PID_PARAMETER_NUM]);
										 
void DMmotor_Create (DM_MotorModule *obj, uint16_t command_id, uint16_t master_id,FDCAN_HandleTypeDef *hcan, Motor_Model motorModel,Ctrl_mode mode,PID_Type_e pidType,float pid_Param_pos[PID_PARAMETER_NUM]);
HAL_StatusTypeDef DM_Motor_CMD(DM_MotorModule *obj,Motor_CMD CMD);
void DMget_motor_measure(DM_MotorModule *obj, uint8_t rx_data[8]);
HAL_StatusTypeDef DMset_mit_data(DM_MotorModule *obj, float Position, float Velocity, float KP, float KD, float Torque);
HAL_StatusTypeDef DMset_posvel_data(DM_MotorModule *obj, float Position, float Velocity);
void save_pos_zero(DM_MotorModule *obj, uint16_t mode_id);
float Motor_PID_Calculate_FOUR(DM_MotorModule_FOUR *obj, float input);
void DMget_motor_measure_FOUR(DM_MotorModule_FOUR *obj, uint8_t rx_data[8]);
void DMget_moto_offset_FOUR(DM_MotorModule_FOUR *obj, uint8_t rx_data[8]);
HAL_StatusTypeDef DMset_motor_data_FOUR(FDCAN_HandleTypeDef *hcan, uint32_t id, int16_t data1, int16_t data2, int16_t data3, int16_t data4);
#endif
