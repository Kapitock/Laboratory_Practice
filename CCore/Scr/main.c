#include "../Inc/init.h"
#include "../Inc/interrupt.h"

int main(void)
{
    GPIO_Init();        // Инициализация портов
    RCC_Init();         // Настройка тактирования
    TIMER_Init();       // Настройка таймера
    IQR_Init();         // Настройка прерывания

    while (1)
    {
        
    }
    return 0;
}
