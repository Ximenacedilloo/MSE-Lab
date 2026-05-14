#include "adc_driver.h"

ADC_Status_t ADC_Init(ADC_TypeDef *adc, uint8_t channel)
{
    if (adc == NULL)   return ADC_ERROR_INVALID_INSTANCE;
    if (channel > 18)  return ADC_ERROR_INVALID_CHANNEL;

    /* 1. Clock del ADC1 */
    if (adc == ADC1) {
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    } else {
        return ADC_ERROR_INVALID_INSTANCE;
    }

    /* 2. Clock del GPIOA y configurar PA0 como Analog */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (3U << (channel * 2));

    /* 3. CR1 — 12 bits, sin scan */
    adc->CR1 &= ~ADC_CR1_RES;
    adc->CR1 &= ~ADC_CR1_SCAN;

    /* 4. CR2 — single, software trigger */
    adc->CR2 &= ~ADC_CR2_CONT;
    adc->CR2 |=  ADC_CR2_EOCS;
    adc->CR2 &= ~ADC_CR2_EXTEN;

    /* 5. Secuencia de 1 conversión */
    adc->SQR1 &= ~ADC_SQR1_L;
    adc->SQR3  =  (channel & 0x1F);

    /* 6. Sample time: 84 ciclos */
    if (channel <= 9) {
        adc->SMPR2 &= ~(0x7U << (channel * 3));
        adc->SMPR2 |=  (0x4U << (channel * 3));
    } else {
        adc->SMPR1 &= ~(0x7U << ((channel - 10) * 3));
        adc->SMPR1 |=  (0x4U << ((channel - 10) * 3));
    }

    /* 7. Encender ADC */
    adc->CR2 |= ADC_CR2_ADON;

    /* 8. Delay de estabilización */
    for (volatile uint32_t i = 0; i < 1000; i++);

    return ADC_OK;
}

ADC_Status_t ADC_StartConversion(ADC_TypeDef *adc)
{
    if (adc == NULL) return ADC_ERROR_INVALID_INSTANCE;
    adc->CR2 |= ADC_CR2_SWSTART;
    return ADC_OK;
}

ADC_Status_t ADC_ReadValue(ADC_TypeDef *adc, uint16_t *value)
{
    if (adc == NULL || value == NULL) return ADC_ERROR_INVALID_INSTANCE;

    uint32_t timeout = 100000U;
    while (!(adc->SR & ADC_SR_EOC)) {
        if (--timeout == 0U) return ADC_ERROR_TIMEOUT;
    }

    *value = (uint16_t)(adc->DR & 0x0FFFU);
    return ADC_OK;
}

uint8_t ADC_IsConversionComplete(ADC_TypeDef *adc)
{
    if (adc == NULL) return 0;
    return (adc->SR & ADC_SR_EOC) ? 1U : 0U;
}

ADC_Status_t ADC_DeInit(ADC_TypeDef *adc)
{
    if (adc == NULL) return ADC_ERROR_INVALID_INSTANCE;
    adc->CR2 &= ~ADC_CR2_ADON;
    return ADC_OK;
}