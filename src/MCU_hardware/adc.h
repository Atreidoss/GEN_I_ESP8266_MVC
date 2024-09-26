#ifndef adc_h_
#define adc_h_

#include "Arduino.h"
#include "settings.h"
#include <Adafruit_ADS1X15.h>

#ifndef SETTINGS_ADC
#define ADC_ADDR 0x48 // Адресс по шине i2c
// CH0 - I value, делитель канала 0 (в кОм), измерение тока
#define ADC_I 0
#define DIV_CH0_M 10
#define DIV_CH0_P 100
// CH1 - U value, делитель канала 1 (в кОм), измерение внешнего напряжения
#define ADC_U 1
#define DIV_CH1_M 10
#define DIV_CH1_P 10
// CH2 - Bat value, делитель канала 2 (в кОм), измерение напряжения аккумулятора
#define ADC_BAT 2
#define DIV_CH2_M 10
#define DIV_CH2_P 10
// CH3 - value, делитель канала 3 (в кОм), измерение напряжения
#define ADC_CH3 3    // reserved
#define DIV_CH3_M 10 // reserved
#define DIV_CH3_P 10 // reserved

#define POOL_MEASURMENT_BAT_MS 500 // Период измерения напряжения батареи, мс
#define MEASURMENT_BAT_COUNT 15    // Количество измерений напряжения батареи, мс
#endif

class Measure
{
public:
    Measure()
    {
        adcInit(ADC_ADDR);
    }

    float getValue(uint8_t channel, uint8_t readCount = 1)
    {
        uint32_t tempValue = 0;
        for (int i = 0; i < readCount; i++)
        {
            tempValue += _ADS.readADC_SingleEnded(channel);
        }
        _rawValue[channel] = tempValue / readCount;
        return adcToVoltage(_rawValue[channel], channel);
    }

    uint32_t getRawValue(uint8_t channel)
    {
        return _rawValue[channel];
    }

    void setOffset(uint8_t channel, int offset)
    {
        _offset[channel] = offset;
    }

private:
    Adafruit_ADS1115 _ADS;
    int _offset[4] = {100, 100, 100, 100};
    uint32_t _rawValue[4];
    const uint16_t divP[4] = {DIV_CH0_P, DIV_CH1_P, DIV_CH2_P, DIV_CH3_P};
    const uint16_t divM[4] = {DIV_CH0_M, DIV_CH1_M, DIV_CH2_M, DIV_CH3_M};

    void adcInit(uint8_t addres)
    {
        _ADS.begin(addres);
        _ADS.setGain(GAIN_TWOTHIRDS); // GAIN_TWOTHIRDS = ADS1X15_REG_CONFIG_PGA_6_144V
        _ADS.setDataRate(RATE_ADS1115_475SPS);
    }

    float adcToVoltage(uint16_t adcRaw, uint8_t channel)
    {
        float coef = ((float)divP[channel] + (float)divM[channel]) / (float)divM[channel];
        float voltage = (coef * _ADS.computeVolts(adcRaw));// * ((float)_offset[channel] / 100.00));
        return voltage;
    }
};

#endif