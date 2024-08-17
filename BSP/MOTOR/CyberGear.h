#ifndef __CYBERGEAR_H
#define __CYBERGEAR_H

#ifdef __cplusplus
extern {
#endif

#include "stm32f4xx.h"
#include "stm32f4xx_can.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>  
#include <math.h>  
#include "delay.h"
#include "debug.h"	//调试打印开关


//作者邮箱：fanghui20220@163.com
//CSDN:奔跑的蜗牛！	https://blog.csdn.net/weixin_49337111?type=blog


#ifndef M_PI  
#define M_PI 3.14159265358979323846  
#endif

//限位参数值
#define P_MIN 	-12.5f 
#define P_MAX 	12.5f 
#define V_MIN 	-30.0f 
#define V_MAX 	30.0f 
#define KP_MIN 	0.0f
#define KP_MAX 	500.0f 
#define KD_MIN 	0.0f 
#define KD_MAX 	5.0f 
#define T_MIN 	-12.0f 
#define T_MAX 	12.0f

//4种运行模式
#define RUN_CNTL_MODE 0	//运控模式
#define POSITION_MODE 1	//位置模式
#define SPEED_MODE	  2 //速度模式
#define CURRENT_MODE  3 //电流模式

//可读写单个参数列表宏定义
#define RUN_MODE 	  0x7005 //0: 运控模式 1: 位置模式 2: 速度模式 3: 电流模式
#define IQ_REF	 	  0x7006 //电流模式Iq指令
#define SPD_REF	 	  0x700A //转速模式转速指令
#define LIMIT_TORQUE  0x700B //转矩限制
#define CUR_KP		  0x7010 //电流的 Kp
#define CUR_KI		  0x7011 //电流的 Ki
#define CUR_FILT_GAIN 0x7014 //电流滤波系数filt_gain
#define LOC_REF		  0x7016 //位置模式角度指令
#define LIMIT_SPD	  0x7017 //位置模式速度设置
#define LIMIT_CUR	  0x7018 //速度位置模式电流设置

//CyberGear的CAN 32位扩展Ext_ID帧结构
typedef struct{
	uint32_t  dst_id:8;	// Bit 0  - Bit 7, 	8位表示目标地址 
    uint32_t  data:16;	// Bit 8  - Bit 23,	16位表示数据区 （用于标识主机CAN ID） 
	uint32_t  mode:5;	// Bit 24 - Bit 28,	5位表示通信类型  
	uint32_t  res:3;	// Bit 29 - Bit 32,	3位多余的
}CyberGear_CAN_Id_t;

//CyberGear通信数据格式
typedef struct{
	CyberGear_CAN_Id_t id; //CAN ID
	uint8_t data[8];	   //8 Byte数据区	
}CyberGear_Info_t;

//CyberGear电机反馈数据结构体
typedef struct{
	float angle;	  //当前角度
	float speed;	  //当前角速度
	float torque;	  //当前力矩
	float temperature;//当前温度
}CyberGear_FeedBack_t;

//CyberGear电机运行模式
enum MOTOR_MODE_TYPE{
	GET_MOTOR_ID	= 0, //获取设备 ID
	MOTOR_MOVE_CNL	= 1, //运控模式电机控制指令
	MOTOR_FEEDBACK	= 2, //电机反馈数据
	MOTOR_RUN		= 3, //电机使能运行
	MOTOR_STOP		= 4, //电机停止运行
	MOTOR_ZERO_POS	= 6, //设置电机机械零位
	SET_MOTOR_ID	= 7, //设置电机 CAN_ID
	READ_ONE_PARAM	= 17,//单个参数读取 
	WRITE_ONE_PARAM	= 18,//单个参数写入
	ERR_FEEDBACK	= 21 //故障反馈帧
};

//电机运行状态
enum MOTOR_RUN_STATE{
	OK				  = 0, //正常
	LOW_VOLTAGE 	  = 1, //欠压故障
	OVER_CURRENT 	  = 2, //过流
	OVER_TEMP 		  = 3, //过温
	MAGNETIC_CODE_ERR = 4, //磁编码故障
	HALL_CODE_ERR 	  = 5, //HALL编码故障
	UNMARKED		  = 6  //未标定
};

//电机模式
enum MOTOR_MODE{
	RESET_Mode = 0,	//Reset 模式[复位]
	CALI_Mode  = 1,	//Cali  模式[标定]
	RUN_Mode   = 2	//Motor 模式[运行]
};

extern CanTxMsg CAN1_TxMessage;
extern CanRxMsg CAN1_RxMessage;
extern uint8_t master_id;				//主控制设备的CAN ID
extern uint8_t motor_id;				//电机的CAN通信ID
extern uint16_t motor_read_id;			//读取到电机的CAN ID
extern uint8_t motor_mcu_id[8];			//电机内部的MCU唯一标识符
extern uint8_t motor_state;				//电机运行状态
extern CyberGear_Info_t recv_data;		//接收电机返回数据结构
extern CyberGear_FeedBack_t motor_info;	//CyberGear电机反馈数据信息

#define WAIT_CAN_HANDLE 0x01	//等待CAN数据处理
#define OVER_CAN_HANDLE 0x00	//CAN数据处理完毕

int float_to_uint(float f_val, float f_val_min, float f_val_max, int int_bits);
double radians_to_degrees(double radians);
double degrees_to_radians(double degrees);

void CyberGear_CAN_Init(void);
void CyberGear_Init(void);
int CyberGear_Motor_Send_Data(CyberGear_Info_t *data);
void CyberGear_ID_Get(uint8_t motor_id, uint8_t master_id, uint16_t *can_id, uint8_t *mcu_id);
void CyberGear_Change_Mode(uint8_t motor_id, uint8_t master_id, uint8_t mode);
void CyberGear_Control_Mode(uint8_t motor_id, uint8_t master_id, float torque, float target_pos, float speed, float kp, float kd);
void CyberGear_Control_Mode_Change_Torque(uint8_t motor_id, uint8_t master_id,float torque);
void CyberGear_Control_Mode_Turn_Certain_Position(uint8_t motor_id, uint8_t master_id,float target_pos, float kp, float kd);
void CyberGear_Control_Mode_Change_Speed(uint8_t motor_id, uint8_t master_id, float speed, float kd);
void CyberGear_Return_Zero_Position(uint8_t motor_id, uint8_t master_id);
void CyberGear_Position_Control_Mode_Init(uint8_t motor_id, uint8_t master_id, float max_speed, float target_pos);
void CyberGear_Position_Control_Mode_Change_Speed(uint8_t motor_id, uint8_t master_id, float max_speed);
void CyberGear_Position_Control_Mode_Change_Position(uint8_t motor_id, uint8_t master_id, float target_pos);
void CyberGear_Speed_Control_Mode_Init(uint8_t motor_id, uint8_t master_id, float max_current,float target_speed);
void CyberGear_Speed_Control_Mode_Change_Max_Current(uint8_t motor_id, uint8_t master_id, float max_current);
void CyberGear_Speed_Control_Mode_Change_speed(uint8_t motor_id, uint8_t master_id, float target_speed);
void CyberGear_Current_Control_Mode_Init(uint8_t motor_id, uint8_t master_id, float current_val);
void CyberGear_Current_Control_Mode_Change_current(uint8_t motor_id, uint8_t master_id, float current_val);
void CyberGear_Decode_Ret_Data(CyberGear_Info_t *recv_data, uint8_t *motor_state, CyberGear_FeedBack_t *motor_info);
void CyberGear_Eanble_Run(uint8_t motor_id, uint8_t master_id);
void CyberGear_Stop_Run(uint8_t motor_id, uint8_t master_id);
void CyberGear_Set_Zero_Position(uint8_t motor_id, uint8_t master_id);
void CyberGear_Change_CAN_ID(uint8_t old_motor_id, uint8_t new_motor_id, uint8_t master_id);
void CyberGear_Read_Single_Param(uint8_t motor_id, uint8_t master_id, uint16_t index);
void CyberGear_Write_Single_Param(uint8_t motor_id, uint8_t master_id, uint16_t index, uint32_t param_val);
void CyberGear_Change_Run_Mode(uint8_t motor_id, uint8_t master_id, uint16_t index, uint32_t run_mode);
void CyberGear_Read_Speed(uint8_t motor_id, uint8_t master_id, float *speed);
void CAN1_RX0_IRQHandler(void);


#ifdef __cplusplus
}
#endif
#endif

