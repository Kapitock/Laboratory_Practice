#include "../Inc/init.h"
#include "../Inc/interrupt.h"

uint16_t GlobalTickCount = 0;
uint16_t ButtonTickCount = 0;
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
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS12 | GPIO_BSRR_BS11 | GPIO_BSRR_BS10 |
                                    GPIO_BSRR_BS8 | GPIO_BSRR_BS6 | GPIO_BSRR_BS5);
        }
        else
        {
            SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR12 | GPIO_BSRR_BR11 | GPIO_BSRR_BR10 |
                                    GPIO_BSRR_BR8 | GPIO_BSRR_BR6 | GPIO_BSRR_BR5);
        }
    }
    return 0;
}