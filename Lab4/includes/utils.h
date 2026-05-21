/******************************************************************************
 * Copyright (C) 2026 by Carlos Villarreal - CETYS Universidad
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Carlos Villarreal and CETYS Universidad are not liable for any
 * misuse of this material.
 *
 *****************************************************************************/
/**
 * @file utils.h
 * @brief Utility library with helper functions.
 *
 * Utils module has helper functions to treat strings, ASCII conversions, and
 * printing utilities.
 *
 * @author Ximena Cedillo, Kheara Kieley, Michelle Urbina
 * @date 04/29/2026
 *
 */

#ifndef __UTILS_H__
#define __UTILS_H__

/*** Includes ***/
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

/*** Preprocessor Definitions ***/

/*** Type Prototypes ***/

/*** Global Variables ***/

/*** Function Prototypes ***/

void utils_snprintf(char *dst, const char *format, ...);

uint32_t utils_itoa(int32_t data, uint8_t *ptr, uint8_t sign, uint8_t base);

int32_t utils_atoi(uint8_t *ptr, uint32_t digits, uint8_t sign, uint8_t base);

void * utils_memCpy(void *dst, void *src, size_t length);

void * utils_memReverse(void *src, size_t length);

#endif /* __UTILS_H__ */