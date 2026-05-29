#include "sensor.h"
#include "serial.h"
#include "Timer.h"
#include "TIM.h"
#include "GPIO.h"
#include "UART.h"

#define PWM_PERIOD      1000
#define PWM_TIM         TIM_2
#define PWM_CHANNEL     1
#define DELAY_TIM       TIM_3
#define SAMPLE_DELAY_MS 100

static uint16_t gyro_to_pwm(int16_t raw)
{
    int32_t abs_val = (raw < 0) ? -raw : raw;
    if (abs_val > 32767) abs_val = 32767;
    return (uint16_t)(((uint32_t)abs_val * PWM_PERIOD) / 32767);
}

static void pwm_init(void)
{
    tim_init();
    tim_initTimer(PWM_TIM);
    gpio_initPort(A);
    gpio_setPinMode(A, 5, 2);
    gpio_setAlternateFunction(A, 5, 1);
    TIM[PWM_TIM]->PSC = 15;
    TIM[PWM_TIM]->ARR = PWM_PERIOD - 1;
    tim_setTimerCompareMode(PWM_TIM, PWM_CHANNEL, 6);
    tim_setTimerCompareChannelValue(PWM_TIM, PWM_CHANNEL, 0);
    tim_enableTimerCompareChannel(PWM_TIM, PWM_CHANNEL);
    tim_enableTimer(PWM_TIM);
}

int main(void)
{
    gpio_initPort(A);
    gpio_setPinMode(A, 2, 2);
    gpio_setPinMode(A, 3, 2);
    gpio_setAlternateFunction(A, 2, 7);
    gpio_setAlternateFunction(A, 3, 7);
    uart_init();
    serial_printf("UART OK\r\n");

    sensor_init();
    serial_printf("SENSOR INIT OK\r\n");

    if (!sensor_whoAmI())
    {
        serial_printf("ERROR: sensor not detected\r\n");
        while (1);
    }

    serial_printf("MPU-6050 OK. Starting...\r\n");
    sensor_config(MPU6050_GYRO_FS_250, MPU6050_ACCEL_FS_2G);
    pwm_init();

    mpu6050_gyro_t  gyro;
    mpu6050_accel_t accel;

    while (1)
    {
        sensor_readGyro(&gyro);
        sensor_readAccel(&accel);

        serial_printf("GYRO  X:%d  Y:%d  Z:%d\r\n",
                      (int)gyro.x, (int)gyro.y, (int)gyro.z);
        serial_printf("ACCEL X:%d  Y:%d  Z:%d\r\n",
                      (int)accel.x, (int)accel.y, (int)accel.z);

        uint16_t duty = gyro_to_pwm(gyro.z);
        tim_setTimerCompareChannelValue(PWM_TIM, PWM_CHANNEL, duty);

        serial_printf("PWM duty: %d / %d\r\n\r\n",
                      (int)duty, (int)PWM_PERIOD);

        timer_init(DELAY_TIM);
        timer_delay_ms(DELAY_TIM, SAMPLE_DELAY_MS);
    }

    return 0;
}
