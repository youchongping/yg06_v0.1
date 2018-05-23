#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"

/*key_value*/
#define NO_KEY 0
#define LEFT_ON (1<<0)
#define RIGHT_ON (1<<1)
#define FRONT_ON (1<<2)
#define BACK_ON (1<<3)
#define CATCH_ON (1<<4)
#define SET_ON (1<<5)

extern u8 key_scan(void);
extern void key_deal(u8 *key_value);
#endif

