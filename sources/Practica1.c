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