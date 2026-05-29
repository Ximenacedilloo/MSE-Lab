/**
 * @file I2C.c
 * @brief I2C peripheral driver for STM32F411RE (Master mode, polling)
 *
 * @authors David Mijares, Ximena Cedillo, Xavier Clemente
 */

#include "I2C.h"

uint32_t i2c_calc_ccr(uint32_t scl_freq_hz)
{
    return SystemCoreClock / (2 * scl_freq_hz);
}

uint32_t i2c_trise(uint32_t scl_freq_hz)
{
    uint32_t max_rise_ns;
    if (scl_freq_hz <= 100000)
        max_rise_ns = 1000;
    else if (scl_freq_hz <= 400000)
        max_rise_ns = 300;
    else
        max_rise_ns = 120;

    uint64_t temp = (uint64_t)max_rise_ns * SystemCoreClock;
    uint32_t trise = (uint32_t)(temp / 1000000000UL) + 1;
    return trise;
}

void i2c_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    I2C1->CR1 = 0;
    I2C1->CR2 = 0;
    I2C1->CR2 |= (16 << 0);
    I2C1->CCR   = i2c_calc_ccr(SLC_FREQ);
    I2C1->TRISE = i2c_trise(SLC_FREQ);
    I2C1->CR2 &= ~(I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN | I2C_CR2_ITERREN);
    I2C1->CR1 |= I2C_CR1_PE;
}

void i2c_writeRegDevice(uint8_t device_address, uint8_t register_address, uint8_t *data, uint32_t len)
{
    uint32_t timeout;

    I2C1->CR1 |= I2C_CR1_START;
    timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_SB) && timeout--);

    I2C1->DR = (device_address << 1);
    timeout = 100000; while (!(I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF)) && timeout--);
    if (I2C1->SR1 & I2C_SR1_AF)
    {
        I2C1->SR1 &= ~I2C_SR1_AF;
        I2C1->CR1 |= I2C_CR1_STOP;
        return;
    }
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    I2C1->DR = register_address;
    timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_TXE) && timeout--);

    for (uint32_t i = 0; i < len; i++)
    {
        I2C1->DR = data[i];
        timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_TXE) && timeout--);
    }
    I2C1->CR1 |= I2C_CR1_STOP;
}

void i2c_writeDevice(uint8_t device_address, uint8_t *data, uint32_t len)
{
    uint32_t timeout;

    I2C1->CR1 |= I2C_CR1_START;
    timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_SB) && timeout--);

    I2C1->DR = (device_address << 1);
    timeout = 100000; while (!(I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF)) && timeout--);
    if (I2C1->SR1 & I2C_SR1_AF)
    {
        I2C1->SR1 &= ~I2C_SR1_AF;
        I2C1->CR1 |= I2C_CR1_STOP;
        return;
    }
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    for (uint32_t i = 0; i < len; i++)
    {
        I2C1->DR = data[i];
        timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_TXE) && timeout--);
    }
    I2C1->CR1 |= I2C_CR1_STOP;
}

void i2c_readRegDevice(uint8_t device_address, uint8_t register_address, uint8_t *data, uint32_t len)
{
    uint32_t timeout;

    I2C1->CR1 |= I2C_CR1_START;
    timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_SB) && timeout--);

    I2C1->DR = (device_address << 1);
    timeout = 100000; while (!(I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF)) && timeout--);
    if (I2C1->SR1 & I2C_SR1_AF)
    {
        I2C1->SR1 &= ~I2C_SR1_AF;
        I2C1->CR1 |= I2C_CR1_STOP;
        return;
    }
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    I2C1->DR = register_address;
    timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_TXE) && timeout--);

    I2C1->CR1 |= I2C_CR1_START;
    timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_SB) && timeout--);

    I2C1->DR = (device_address << 1) | 1;
    timeout = 100000; while (!(I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF)) && timeout--);
    if (I2C1->SR1 & I2C_SR1_AF)
    {
        I2C1->SR1 &= ~I2C_SR1_AF;
        I2C1->CR1 |= I2C_CR1_STOP;
        return;
    }
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    I2C1->CR1 |= I2C_CR1_ACK;

    for (uint32_t i = 0; i < len; i++)
    {
        if (i == len - 1)
        {
            I2C1->CR1 &= ~I2C_CR1_ACK;
            I2C1->CR1 |= I2C_CR1_STOP;
        }
        timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_RXNE) && timeout--);
        data[i] = I2C1->DR;
    }
}

void i2c_readDevice(uint8_t device_address, uint8_t *data, uint32_t len)
{
    uint32_t timeout;

    I2C1->CR1 |= I2C_CR1_START;
    timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_SB) && timeout--);

    I2C1->DR = (device_address << 1);
    timeout = 100000; while (!(I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF)) && timeout--);
    if (I2C1->SR1 & I2C_SR1_AF)
    {
        I2C1->SR1 &= ~I2C_SR1_AF;
        I2C1->CR1 |= I2C_CR1_STOP;
        return;
    }
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    I2C1->CR1 |= I2C_CR1_START;
    timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_SB) && timeout--);

    I2C1->DR = (device_address << 1) | 1;
    timeout = 100000; while (!(I2C1->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF)) && timeout--);
    if (I2C1->SR1 & I2C_SR1_AF)
    {
        I2C1->SR1 &= ~I2C_SR1_AF;
        I2C1->CR1 |= I2C_CR1_STOP;
        return;
    }
    (void)I2C1->SR1;
    (void)I2C1->SR2;

    I2C1->CR1 |= I2C_CR1_ACK;

    for (uint32_t i = 0; i < len; i++)
    {
        if (i == len - 1)
        {
            I2C1->CR1 &= ~I2C_CR1_ACK;
            I2C1->CR1 |= I2C_CR1_STOP;
        }
        timeout = 100000; while (!(I2C1->SR1 & I2C_SR1_RXNE) && timeout--);
        data[i] = I2C1->DR;
    }
}