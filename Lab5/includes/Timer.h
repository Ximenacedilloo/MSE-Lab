#ifndef TIMER_H
#define TIMER_H

#include "TIM.h"

void timer_init(tim_t t);
void timer_delay_ms(tim_t t, uint16_t delay_ms);

#endif
