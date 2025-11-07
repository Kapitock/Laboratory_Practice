#include "../Inc/init.h"
#include "../Inc/interrupt.h"

#define FLICKER_PERIOD 2000

uint16_t GlobalTickCount = 0;
uint16_t DelayTickCount = 0;
uint8_t btnCount = 0;
bool LedState = false;

int main(void)
{
    GPIO_Init();
    RCC_Init();
    IQR_Init();
    SysTick_Init();

    while (1)
    {
        if (LedState)
        {
            SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5);
        }
        else
        {
            SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);
        }
        // if (GlobalTickCount >= FLICKER_PERIOD / 2)
        // { // Если прошло 1000 прерываний системного таймера = 1 секунда
        //         SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5); // Включаем светодиод
        //     if (GlobalTickCount >= FLICKER_PERIOD)
        //     { // Если прошло 2000 прерываний системного таймера = 2 секунды
        //             GlobalTickCount = 0; // Обнуляем переменную счётчика системного таймера
        //     }
        // }
        // else
        // {
        //     SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5); // Иначе выключаем светодиод
        // }
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5);
        delay(1000);
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);
        delay(1000);
    }
    return 0;
}