/**
 * @file sensor.h
 * @brief MPU-6050 Gyroscope/Accelerometer sensor driver header
 *
 * MPU-6050 I2C Address: 0x68 (AD0 = GND)
 * SCL -> PB8 (D15), SDA -> PB9 (D14)
 *
 * @author Carlos Villarreal
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include "I2C.h"
#include "GPIO.h"

/* ── MPU-6050 I2C address ───────────────────────────────────────────────── */
#define MPU6050_ADDR            0x68

/* ── MPU-6050 Register map ──────────────────────────────────────────────── */
#define MPU6050_REG_PWR_MGMT_1      0x6B
#define MPU6050_REG_SMPLRT_DIV      0x19
#define MPU6050_REG_CONFIG          0x1A
#define MPU6050_REG_GYRO_CONFIG     0x1B
#define MPU6050_REG_ACCEL_CONFIG    0x1C
#define MPU6050_REG_ACCEL_XOUT_H    0x3B
#define MPU6050_REG_GYRO_XOUT_H     0x43
#define MPU6050_REG_WHO_AM_I        0x75

/* ── Gyroscope full-scale range ─────────────────────────────────────────── */
#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x08
#define MPU6050_GYRO_FS_1000        0x10
#define MPU6050_GYRO_FS_2000        0x18

/* ── Accelerometer full-scale range ─────────────────────────────────────── */
#define MPU6050_ACCEL_FS_2G         0x00
#define MPU6050_ACCEL_FS_4G         0x08
#define MPU6050_ACCEL_FS_8G         0x10
#define MPU6050_ACCEL_FS_16G        0x18

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} mpu6050_gyro_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} mpu6050_accel_t;

void sensor_init(void);
void sensor_config(uint8_t gyro_fs, uint8_t accel_fs);
void sensor_readGyro(mpu6050_gyro_t *gyro);
void sensor_readAccel(mpu6050_accel_t *accel);
uint8_t sensor_whoAmI(void);

#endif /* SENSOR_H */