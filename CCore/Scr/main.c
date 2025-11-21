#include "../Inc/init.h"
#include "../Inc/interrupt.h"

int main(void)
{
    GPIO_Init();     // Инициализация портов
    RCC_Init();      // Настройка тактирования
    TIM10_Init();    // Настройка таймера
    IQR_Init();      // Настройка прерывания
    TIM3_PWM_Init(); // Настройка ШИМ
    TIM1_PWM_Init();
    TIM5_PWM_Init();

    while (1)
    {
        // MODIFY_REG(TIM3->CCR1, TIM_CCR1_CCR1_Msk, 200UL);
        // MODIFY_REG(TIM3->CCR2, TIM_CCR2_CCR2_Msk, 200UL);
    }
    return 0;
}
