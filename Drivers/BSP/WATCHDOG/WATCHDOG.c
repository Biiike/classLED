#include "WATCHDOG.h"

IWDG_HandleTypeDef g_iwdg_handler;
WWDG_HandleTypeDef g_wwdg_handler;

void Iwdg_Init(void)
{
    g_iwdg_handler.Instance = IWDG;
    g_iwdg_handler.Init.Prescaler = IWDG_PRESCALER_32;
    g_iwdg_handler.Init.Reload = 1250;

    HAL_IWDG_Init(&g_iwdg_handler);

}

void iwdg_feed(void)
{
    HAL_IWDG_Refresh(&g_iwdg_handler);
}

void Wwdg_Init(void)
{
    g_wwdg_handler.Instance = WWDG;
    g_wwdg_handler.Init.EWIMode =  WWDG_EWI_ENABLE;
    g_wwdg_handler.Init.Counter = 0x7f;
    g_wwdg_handler.Init.Prescaler = WWDG_PRESCALER_8;
    g_wwdg_handler.Init.Window = 0x5f;

    HAL_WWDG_Init(&g_wwdg_handler);
}

void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();
    HAL_NVIC_SetPriority(WWDG_IRQn,1,1);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}

void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_wwdg_handler);

}

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5);
    //HAL_WWDG_Refresh(&g_wwdg_handler);
}

