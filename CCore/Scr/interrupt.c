#include "../Inc/interrupt.h"

extern uint8_t LedState;
uint8_t btnCount = 0;

void EXTI15_10_IRQnHandler(void)
{
    btnCount++;
    if(btnCount >= 2)
    {
        LedState = !LedState;
        btnCount = 0;
    }
    SET_BIT(EXTI->PR, EXTI_PR_PR13);
}