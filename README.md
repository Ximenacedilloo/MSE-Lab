Push Button: 
    B1 USER: the user button is connected to the I/O PC13 (pin 2) of the STM32
    microcontroller.

    Funciones a implementar en el Push Button
        button_init
        button_get_state
    Utilizar las funciones del GPIO para detectar el estado del boton.

LED: 
    User LD2: the green LED is a user LED connected to ARDUINO® signal D13 corresponding
    to STM32 I/O PA5 (pin 21) or PB13 (pin 34) depending on the STM32 target. Refer to
    Table 11 to Table 23 when:
        • the I/O is HIGH value, the LED is on
        • the I/O is LOW, the LED is off

    Funciones del LED
        led_init
        led_on
        led_off
        led_toggle

        Utilizar las funciones del GPIO internas


Funciones a trabajar: 

    gpio_init
        Description: Initializes the GPIO subsystem.
        Functional Requirements:
        FR-1: The system shall configure all GPIO ports to a default state.

    gpio_initPort
        Description: Initializes a specific GPIO port.
        Functional Requirements:
        FR-2: The system shall enable clocking for the specified port.

    gpio_setPinMode
        Description: Configures the mode of a specific pin.
        Functional Requirements:
        FR-3: The system shall allow configuration of pin direction and mode.

    gpio_setPin
        Description: Sets a pin to logic high.
        Functional Requirements:
            FR-4: The system shall drive the specified pin to a high state.
    
    gpio_clearPin
        Description: Clears a pin to logic low.
        Functional Requirements:
            FR-5: The system shall drive the specified pin to a low state.
    
    gpio_togglePin
        Description: Toggles the state of a pin.
        Functional Requirements:
            FR-6: The system shall invert the current state of the specified pin.
    
    gpio_readPin
        Description: Reads the current state of a pin.
        Functional Requirements:
            FR-7: The system shall return the digital state of the specified pin.




Funcionalidad final: 

    Configurar el LED como la salida y el push button como la entrada
    En el main loop el LED debera hacer toggle cada que se presione el boton
    Agregar logica de Debounce si se requiere