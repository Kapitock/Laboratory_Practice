#include "../Inc/init.h"
#include "../Inc/interrupt.h"

uint8_t LedState = 0;

int main(void)
{
    GPIO_Init();
    RCC_Init();
    IQR_Init();

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
    }

    return 0;
}