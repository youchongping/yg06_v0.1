#ifndef _MOTOR_CTRL_
#define _MOTOR_CTRL_

#include "stm32f10x.h"
#include "ioctrl.h"
/*Motor Enable Signal ctrl*/
#define MotorLeftRightEnable() GPIO_SetBits(MotorLeftRightEnable_GPIO,MotorLeftRightEnable_PIN)
#define MotorLeftRightDisable() GPIO_ResetBits(MotorLeftRightEnable_GPIO,MotorLeftRightEnable_PIN)
#define MotorFrontBackEnable() GPIO_SetBits(MotorFrontBackEnable_GPIO,MotorFrontBackEnable_PIN)
#define MotorFrontBackDisable() GPIO_ResetBits(MotorFrontBackEnable_GPIO,MotorFrontBackEnable_PIN)
#define MotorUpDownEnable() GPIO_SetBits(MotorUpDownEnable_GPIO,MotorUpDownEnable_PIN)
#define MotorUpDownDisable() GPIO_ResetBits(MotorUpDownEnable_GPIO,MotorUpDownEnable_PIN)
#define MotorGrasp_ON() GPIO_SetBits(MotorGrasp_GPIO,MotorGrasp_PIN)
#define MotorGrasp_OFF() GPIO_ResetBits(MotorGrasp_GPIO,MotorGrasp_PIN)
/*left & right max longth ,foot time*/
#define FOOT_TIME_MS_LR (500)
#define FOOT_LONGTH_LR  (3)
/*forward & back max longth ,foot time*/
#define FOOT_TIME_MS_FB (500)
#define FOOT_LONGTH_FB  (3)
/*up  & down max longth ,foot time*/
#define FOOT_TIME_MS_UD (500)
#define FOOT_LONGTH_UD  (7)
typedef enum
{
	MOTOR_STOP = 0,
	MOTOR_FORWARD,
	MOTOR_BACKWARD
	
}MotorRollDirection_t;

typedef enum
{
	MOTOR_IS_STOP = 0,
	MOTOR_IS_FORWARD,
	MOTOR_IS_BACKWARD
	
}MotorState_t;

typedef enum
{
	MOTOR_AT_MIDDLE= 0,
	MOTOR_AT_TOPPEST,
	MOTOR_AT_LOWEST
	
}MotorPosition_t;
typedef struct 
{
	 s8 foot;
	 MotorState_t runstate;
	 MotorPosition_t motor_position;
	 
}motor_t;
extern motor_t motor_LeftRight;
extern motor_t motor_FrontBack;
extern motor_t motor_UpDown;
s8 MotorLeftRight_Roll(MotorRollDirection_t RollDirection);
s8 MotorFrontBack_Roll(MotorRollDirection_t RollDirection);
s8 MotorUpDown_Roll(MotorRollDirection_t RollDirection);
s8 MotorBackToOriginalPoint(void);
int  MOTOR_Roll(u8 Motor_num , MotorRollDirection_t RollDirection); 
s8 grasp_full(void);
s8 grasp_middle(void);
s8 grasp_zero(void);
void MotorStateCheck_fb(void);
void MotorStateCheck_lr(void);
#endif

