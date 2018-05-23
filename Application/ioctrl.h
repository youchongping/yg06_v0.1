#ifndef _INPUTSIGNAL_H_
#define _INPUTSIGNAL_H_

#include "stm32f10x.h"

/*input*/
#define HandCtrlLeft_GPIO GPIOB
#define HandCtrlLeft_PIN GPIO_Pin_7
#define HandCtrlRight_GPIO GPIOB
#define HandCtrlRight_PIN GPIO_Pin_6
#define HandCtrlFront_GPIO GPIOB
#define HandCtrlFront_PIN GPIO_Pin_5
#define HandCtrlBack_GPIO GPIOB
#define HandCtrlBack_PIN GPIO_Pin_4
#define CatchSignal_GPIO GPIOB
#define CatchSignal_PIN GPIO_Pin_3
#define SetSignal_GPIO GPIOD
#define SetSignal_PIN GPIO_Pin_7
#define CoinIn_GPIO GPIOD
#define CoinIn_PIN  GPIO_Pin_6 
#define LightEye_GPIO GPIOD
#define LightEye_PIN  GPIO_Pin_5
#define Balancer_GPIO GPIOD
#define Balancer_PIN  GPIO_Pin_4
#define LeftMicromone_GPIO GPIOD
#define LeftMicromone_PIN  GPIO_Pin_3
#define RightMicromone_GPIO GPIOD
#define RightMicromone_PIN  GPIO_Pin_2//no this senser
#define UpMicromone_GPIO GPIOD
#define UpMicromone_PIN  GPIO_Pin_0
#define DownMicromone_GPIO GPIOD
#define DownMicromone_PIN  GPIO_Pin_1
#define FrontMicromone_GPIO GPIOC
#define FrontMicromone_PIN  GPIO_Pin_12
#define BackMicromone_GPIO GPIOD
#define BackMicromone_PIN  GPIO_Pin_2//--pd2
/*output*/
#define MotorLeftRightEnable_GPIO GPIOB
#define MotorLeftRightEnable_PIN GPIO_Pin_15// PD12->PB15
#define MotorFrontBackEnable_GPIO GPIOD
#define MotorFrontBackEnable_PIN  GPIO_Pin_11
#define MotorUpDownEnable_GPIO GPIOD
#define MotorUpDownEnable_PIN GPIO_Pin_13
#define MotorGrasp_GPIO GPIOA
#define MotorGrasp_PIN GPIO_Pin_15
#define LightCtrl_GPIO GPIOB
#define LightCtrl_PIN GPIO_Pin_13
#define T3288PowerReset_GPIO GPIOB
#define T3288PowerReset_PIN GPIO_Pin_14
#define KeyLight_GPIO GPIOE
#define KeyLight_PIN GPIO_Pin_1
#define GiftOutRecord_GPIO GPIOE
#define GiftOutRecord_PIN GPIO_Pin_0
#define CoinOutRecord_GPIO GPIOB
#define CoinOutRecord_PIN GPIO_Pin_9
/*output ctrl*/
#define LightCtrl_ON() GPIO_SetBits(LightCtrl_GPIO,LightCtrl_PIN)
#define LightCtrl_OFF() GPIO_ResetBits(LightCtrl_GPIO,LightCtrl_PIN)
void InSignal_GPIO_Init(void);
void OutputSignal_GPIO_Init(void);
void UpSenser_Init(void);
void LightEye_Init(void);
#endif
