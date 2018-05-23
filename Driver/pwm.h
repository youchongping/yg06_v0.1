#ifndef _PWM_H_
#define _PWM_H_
#include "stm32f10x.h"
 #define CCR_NORMAL (500)
 #define CCR_ZERO (0)
 #define CCR_FULL (1000)
 
 //grasp_CCR
 #define CCR_GRASP_FULL (300)
 #define CCR_GRASP_MIDDLE (200)
 #define CCR_GRASP_ZERO (0)

extern void TIM3_PWM_Init(void);
extern void TIM4_PWM_Init(void);
#endif 
