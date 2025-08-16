#pragma once

#include "stm32f1xx.h"

void Iwdg_Init(void);
void iwdg_feed(void);

void Wwdg_Init(void);
void wwdg_feed(void);

extern WWDG_HandleTypeDef g_wwdg_handler;