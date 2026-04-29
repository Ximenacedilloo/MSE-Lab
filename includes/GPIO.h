/**
 * @file register.h
 * @brief Module that manipulates a GPIO for a STM23
 * 
 * The user may use multiple functions to perform bit manipulations
 * on a given register.
 *
 * @author David Mijares
 * @date 
 *
 */

#include <stdint.h>
#include "stm32f4xx.h" 

/*
 
    Description: initializes de GPIO subsytem
    Functional Requirements: 
        FR-1: The system shall configure all GPIO ports to a default state. 
 
 */

void gpio_init(); 



/*
 
    Description: Initializes a specifit GPIO port
    Functional Requirements: 
        FR-2: The system shall enable clockinf for the specified port 
 
 */

void gpio_initPort(GPIO_TypeDef *port); 


 
/*
 
    Description: Configures the mode of a specific pin.
    Functional Requirements: 
        FR-3: The system shall allow configuration of pin direction and mode. 
 
 */

void gpio_setPinMode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);



/*
 
    Description: Sets a pin to logic high.
    Functional Requirements: 
        FR-4: The system shall drive the specified pin to a high state.
 
 */

void gpio_setPin(GPIO_TypeDef *port, uint8_t pin);



/*
 
    Description: Clears a pin to logic low.
    Functional Requirements: 
        FR-5: The system shall drive the specified pin to a low state.
 
 */

void gpio_clearPin(GPIO_TypeDef *port, uint8_t pin);



/*
 
    Description: Toggles the state of a pin.
    Functional Requirements: 
        FR-6: The system shall invert the current state of the specified pin.
 
 */

void gpio_togglePin(GPIO_TypeDef *port, uint8_t pin);



/*
 
    Description: Reads the current state of a pin.
    Functional Requirements: 
        FR-7: The system shall return the digital state of the specified pin.
 
 */

uint8_t gpio_readPin(GPIO_TypeDef *port, uint8_t pin);