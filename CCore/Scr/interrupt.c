#include "../Inc/interrupt.h"

void EXTI15_10_IRQnHandler(void)
{
    btnCount++;
    SET_BIT(EXTI->PR, EXTI_PR_PR13);
}