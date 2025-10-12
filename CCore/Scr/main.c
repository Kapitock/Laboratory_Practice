#include "../Inc/init.h"

// Счетчики для работы с кнопками
short int control_pc12 = 0;
short int control_pc13 = 0;

int main(void)
{
    short int click_button_12 = 3;
    short int click_button_13 = 1;
    // Инициализация портов
    GPIO_Ini();
    while (1)
    {
        // Счетчик для работы светодиодов
        if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0)
        {
            control_pc12 = click_counter(control_pc12, click_button_12);
            while (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_12) == 0)
            {
            }
        }

        // Счетчик для изменения параметра работы порта PC12
        if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) == 0)
        {
            control_pc13 = click_counter(control_pc13, click_button_13);
            while (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) == 0)
            {
            }
        }

        for (int timer = 0; timer < 40000; timer++)
        {
        }

        // LED_flickering(control_pc12);  // Доп задание с мерцанием светодиодов
        turning_on_the_LED(control_pc12);
        change_PC12(control_pc13);
    }
}