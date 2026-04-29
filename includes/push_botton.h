#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <stdint.h>

// Inicializa el botón usando las funciones del driver GPIO
void button_init(void);

// Lee el botón, aplica antirrebote y devuelve 1 si hubo un clic válido, o 0 si no
uint8_t button_get_state(void);

#endif /* PUSH_BUTTON_H */
