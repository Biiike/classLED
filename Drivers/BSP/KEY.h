#ifndef __KEY_H_
#define __KEY_H_

#include "sys.h"
#include "delay.h"
void Key_Init(void);
void Key_Exti_Init(void);
uint8_t Key_Read(void);

#endif
