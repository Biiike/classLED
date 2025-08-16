#pragma once

#include "stm32f1xx.h"

void UART_INIT(uint32_t baud);

extern uint8_t G_RX_BUFFER;
extern uint8_t G_RX_FLAG;
extern UART_HandleTypeDef UART1;