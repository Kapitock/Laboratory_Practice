#include "../Inc/init.h"
#include "../Inc/interrupt.h"

uint8_t btnCount = 0;

int main(void)
{

    RCC_Init();

    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN);

    SET_BIT(GPIOA->MODER, GPIO_MODER_MODER5_0);
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED5_0);
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);

    // Настройка PC13 на прерывания


    // Настройка порта PC9 на MCO2
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER9_1);              // Настраиваем пин на альтернативный режим
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEED9_Msk);       // Настраиваем пин на максимальную скорость работы
    MODIFY_REG(GPIOC->AFR[1], GPIO_AFRH_AFSEL9_Msk, 0x00UL); // Выбираем тип альтернативной функции – Выход MCO2

    while (1)
    {
        SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5);
    }
}