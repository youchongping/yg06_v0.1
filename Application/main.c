#include <stdio.h> 
#include "rtc.h"
#include "base_conf.h"
#include "t3288.h"
#include "uart_dma.h"
#include "key.h"
#include "pwm.h"
#include "motor_ctrl.h"
#include "ioctrl.h"
#include "task.h"
#include "main.h"
#include "tim2.h"
/*
NVIC_PriorityGroup_0 
RTC: 0
usart1-3 :1
UpSenser:13
LightEye:13
timer2:14
systick:15
*/
TASK_t TaskList[]=
{
	{0,KEY_TASK_COUNT,KEY_TASK_COUNT,key_task},
	{0,USARTDEAL_TASK_COUNT,USARTDEAL_TASK_COUNT,uart_task},
	{0,MOTORSTATECHECK_TASK_COUNT,MOTORSTATECHECK_TASK_COUNT,MotorStateCheck_task}
};
int main(void)
{
	sys_init();
	while(1)
	{
		TaskProcess();	
	}
}

void sys_init(void)
{
	RCC_Configuration();
	SysTick_Configuration();
	//RTC_Init();
	NVIC_Configuration();
  //IWDG_Init(12000);//max time 12000ms
	serial_init();
	TIM3_PWM_Init();
	TIM4_PWM_Init();
	InSignal_GPIO_Init();
	OutputSignal_GPIO_Init();
	MCO_Init();
	LightCtrl_ON();
	TIM2_init();
	UpSenser_Init();
	LightEye_Init();
	UART_PutStr(USART2,(u8 *)"system is ready!\x0d\x0a");
}


void key_task(void)
{
	  u8 key_value =0 ;
	  /*key deal*/
		key_value =key_scan();
		key_deal(&key_value);
}

void uart_task(void)
{
	  /*Usart1 deal*/
    if(t3288.rxflag != 0)
		{
			t3288_RcvDeal(t3288.rxdata,t3288.rxcnt);
			memset(t3288.rxdata,0,t3288.rxcnt);
			t3288.rxflag = 0;
		}
		
		/*Usart2 deal*/
		if(debug_t.rxflag != 0)
		{
			t3288_RcvDeal(debug_t.rxdata,debug_t.rxcnt);
			memset(debug_t.rxdata,0,debug_t.rxcnt);
			debug_t.rxflag = 0;
		}
}

void MotorStateCheck_task(void)
{
	MotorStateCheck_fb();
	MotorStateCheck_lr();
	
}
void TaskRemarks(void)
{
    u8 i;

    for (i=0; i<TASK_NUM; i++)         
    {
         if (TaskList[i].Count)          
        {
            TaskList[i].Count--;         
            if (TaskList[i].Count == 0)      
            {
                 TaskList[i].Count = TaskList[i].TotalCount;       
                 TaskList[i].Run = 1;      //mark    
            }
        }
   }
}

void TaskProcess(void)
{
    u8 i;

    for (i=0; i<TASK_NUM; i++)           
    {
         if (TaskList[i].Run)           
        {
             TaskList[i].TaskHook();         
             TaskList[i].Run = 0;          
        }
    }   
}