#ifndef _MAIN_H_
#define _MAIN_H_

//1ms per COUNT
#define KEY_TASK_COUNT (20)
#define USARTDEAL_TASK_COUNT (10)
#define MOTORSTATECHECK_TASK_COUNT (500)
//#define DISPLAY_TASK_COUNT (15)
void sys_init(void);
void key_task(void);
void uart_task(void);
void MotorStateCheck_task(void);
void TaskRemarks(void);
void TaskProcess(void);
#endif