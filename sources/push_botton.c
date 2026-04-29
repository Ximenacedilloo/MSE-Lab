#include "push_button.h"
#include "GPIO_stm32f4.h"

#define BUTTON_PORT PORTC 
#define BUTTON_PIN  PIN13 
#define MODE_INPUT  0   
#define DEBOUNCE_DELAY 20000

// función para delay antirrebote
static void delay(void)
{
    for(volatile int i = 0; i < DEBOUNCE_DELAY; i++);
}

void button_init(void) 
{
    gpio_initPort(BUTTON_PORT);
    gpio_setPinMode(BUTTON_PORT, BUTTON_PIN, MODE_INPUT);
}

uint8_t button_get_state(void) 
{
    // leer estado inicial
    if (gpio_readPin(BUTTON_PORT, BUTTON_PIN) == 0) 
    {
        delay();

        // confirmar que sigue presionado
        if (gpio_readPin(BUTTON_PORT, BUTTON_PIN) != 0)
            return 0;

        // esperar a que se libere el botón
        while (gpio_readPin(BUTTON_PORT, BUTTON_PIN) == 0);

        delay();

        return 1;
    }

    return 0;
}