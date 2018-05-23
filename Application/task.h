#ifndef _TASK_H_
#define _TASK_H_
#include "stm32f10x.h"
#define  TASK_NUM (3)
typedef struct _TASK_COMPONENTS
{
    u8 Run;    //1-run   0-not run            
    u16 Count;             
    u16 TotalCount;  //how ofen to check the task         
    void (*TaskHook)(void);    
} TASK_t;      

#endif