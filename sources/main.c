#include <stdint.h>

/* ================== BASE ADDRESSES ================== */
#define PERIPH_BASE        0x40000000UL
#define AHB1PERIPH_OFFSET  0x00020000UL
#define AHB1PERIPH_BASE    (PERIPH_BASE + AHB1PERIPH_OFFSET)

/* ================== GPIOA ================== */
#define GPIOA_OFFSET       0x0000UL
#define GPIOA_BASE         (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define GPIOA_MODER_OFFSET 0x00UL
#define GPIOA_ODR_OFFSET   0x14UL

#define GPIOA_MODER        (*(volatile uint32_t *)(GPIOA_BASE + GPIOA_MODER_OFFSET))
#define GPIOA_ODR          (*(volatile uint32_t *)(GPIOA_BASE + GPIOA_ODR_OFFSET))

/* ================== RCC ================== */
#define RCC_BASE           0x40023800UL
#define RCC_AHB1ENR_OFFSET 0x30UL

#define RCC_AHB1ENR        (*(volatile uint32_t *)(RCC_BASE + RCC_AHB1ENR_OFFSET))

/* ================== FPU ================== */
#define SCB_CPACR (*(volatile uint32_t*)0xE000ED88)

/* ================== DELAY ================== */
#define DELAY_LIMIT 10000UL

void delay_ms(uint32_t time)
{
    for (uint32_t i = 0; i < time * DELAY_LIMIT; i++)
    {
        __asm__("nop");
    }
}

/* ================== MAIN ================== */
int main(void)
{
    /* 1. Habilitar FPU (evita warning) */
    SCB_CPACR |= (0xF << 20);

    /* 2. Habilitar reloj GPIOA */
    RCC_AHB1ENR |= (1UL << 0);

    /* 3. Configurar PA5 como salida */
    GPIOA_MODER &= ~(3UL << 10);  // Limpiar bits
    GPIOA_MODER |=  (1UL << 10);  // Output

    while (1)
    {
        GPIOA_ODR |= (1UL << 5);   // LED ON
        delay_ms(200);

        GPIOA_ODR &= ~(1UL << 5);  // LED OFF
        delay_ms(200);
    }
}