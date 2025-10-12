#include "../Inc/init.h"

int main(void)
{
    // Счетчики для работы с кнопками
    short int control_pc12 = 0;
    short int control_pc13 = 0;

    // Инициализация портов
    GPIO_Ini();

    while (1)
    {
        // Счетчик для работы светодиодов
        if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0 && control_pc12 == 0)
        {
            control_pc12 = 1;
            while (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0)
            {
            }
        }
        else if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0 && control_pc12 == 1)
        {
            control_pc12 = 2;
            while (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0)
            {
            }
        }
        else if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0 && control_pc12 == 2)
        {
            control_pc12 = 3;
            while (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0)
            {
            }
        }
        else if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0 && control_pc12 == 3)
        {
            control_pc12 = 0;
            while (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0)
            {
            }
        }

        // Счетчик для изменения параметра работы порта PC12
        if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) == 0 && control_pc13 == 0)
        {
            control_pc13 = 1;
            while (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) == 0)
            {
            }
        }
        else if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) == 0 && control_pc13 == 1)
        {
            control_pc13 = 0;
            while (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) == 0)
            {
            }
        }

        for (int timer = 0; timer < 40000; timer++)

        // LED_flickering(control_pc12);  // Доп задание с мерцанием светодиодов
        turning_on_the_LED(control_pc12); 
        change_PC12(control_pc13);
    }
}
