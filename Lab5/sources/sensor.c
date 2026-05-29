/**
 * @file sensor.c
 * @brief MPU-6050 Gyroscope/Accelerometer sensor driver
 *
 * Hardware connections (STM32F411 Nucleo-64):
 *   PB8  -> SCL (I2C1, D15)
 *   PB9  -> SDA (I2C1, D14)
 *   VCC  -> 3.3V
 *   GND  -> GND
 *   AD0  -> GND  (I2C address = 0x68)
 *
 * @author Carlos Villarreal
 */

#include "sensor.h"

static void mpu_write_reg(uint8_t reg, uint8_t value)
{
    i2c_writeRegDevice(MPU6050_ADDR, reg, &value, 1);
}

static void mpu_read_reg(uint8_t reg, uint8_t *buf, uint32_t len)
{
    i2c_readRegDevice(MPU6050_ADDR, reg, buf, len);
}

void sensor_init(void)
{
    /* 1. Configure PB8 (SCL) and PB9 (SDA) as AF4 (I2C1) */
    gpio_initPort(B);
    gpio_setPinMode(B, 8, 2);
    gpio_setPinMode(B, 9, 2);
    gpio_setAlternateFunction(B, 8, 4);
    gpio_setAlternateFunction(B, 9, 4);

    /* 2. Enable internal pull-ups on PB8 and PB9 */
    GPIOB->PUPDR &= ~((3U << 16) | (3U << 18));
    GPIOB->PUPDR |=  ((1U << 16) | (1U << 18));

    /* 3. Enable I2C1 clock before reset */
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    /* 4. Software reset I2C1 */
    I2C1->CR1 |= I2C_CR1_SWRST;
    for (volatile uint32_t i = 0; i < 10000; i++);
    I2C1->CR1 &= ~I2C_CR1_SWRST;
    for (volatile uint32_t i = 0; i < 10000; i++);

    /* 5. Initialize I2C1 */
    i2c_init();

    /* 6. Delay para que el MPU-6050 arranque */
    for (volatile uint32_t i = 0; i < 500000; i++);

    /* 7. Wake up MPU-6050: clear SLEEP bit */
    mpu_write_reg(MPU6050_REG_PWR_MGMT_1, 0x00);

    /* 8. Delay after wake up */
    for (volatile uint32_t i = 0; i < 100000; i++);

    /* 9. Default ranges: gyro ±250°/s, accel ±2g */
    mpu_write_reg(MPU6050_REG_GYRO_CONFIG,  MPU6050_GYRO_FS_250);
    mpu_write_reg(MPU6050_REG_ACCEL_CONFIG, MPU6050_ACCEL_FS_2G);

    /* 10. Sample rate divider = 0 → 1 kHz */
    mpu_write_reg(MPU6050_REG_SMPLRT_DIV, 0x00);
}

void sensor_config(uint8_t gyro_fs, uint8_t accel_fs)
{
    mpu_write_reg(MPU6050_REG_GYRO_CONFIG,  gyro_fs);
    mpu_write_reg(MPU6050_REG_ACCEL_CONFIG, accel_fs);
}

void sensor_readGyro(mpu6050_gyro_t *gyro)
{
    uint8_t buf[6];
    mpu_read_reg(MPU6050_REG_GYRO_XOUT_H, buf, 6);
    gyro->x = (int16_t)((buf[0] << 8) | buf[1]);
    gyro->y = (int16_t)((buf[2] << 8) | buf[3]);
    gyro->z = (int16_t)((buf[4] << 8) | buf[5]);
}

void sensor_readAccel(mpu6050_accel_t *accel)
{
    uint8_t buf[6];
    mpu_read_reg(MPU6050_REG_ACCEL_XOUT_H, buf, 6);
    accel->x = (int16_t)((buf[0] << 8) | buf[1]);
    accel->y = (int16_t)((buf[2] << 8) | buf[3]);
    accel->z = (int16_t)((buf[4] << 8) | buf[5]);
}

uint8_t sensor_whoAmI(void)
{
    uint8_t id = 0;
    mpu_read_reg(MPU6050_REG_WHO_AM_I, &id, 1);
    return (id != 0) ? 1 : 0;
}