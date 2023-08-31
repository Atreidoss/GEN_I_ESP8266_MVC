#ifndef adc_h_
#define adc_h_

#include "Arduino.h"
#include "settings.h"
#include <Adafruit_ADS1X15.h>

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
            tempValue += adcRead(channel);
        }
        tempValue = tempValue / readCount;
        return adcToVoltage(tempValue, divP[channel], divM[channel]);
    }

private:
    Adafruit_ADS1115 _ADS;

    uint16_t divP[4] = {DIV_CH0_P, DIV_CH1_P, DIV_CH2_P, DIV_CH3_P};
    uint16_t divM[4] = {DIV_CH0_M, DIV_CH1_M, DIV_CH2_M, DIV_CH3_M};
    void adcInit(uint8_t addres)
    {
        _ADS.begin(addres);
        _ADS.setGain(GAIN_TWOTHIRDS); // GAIN_ONE = ADS1X15_REG_CONFIG_PGA_4_096V
        _ADS.setDataRate(RATE_ADS1115_475SPS);
    }
    int16_t adcRead(uint8_t channel)
    {
        return _ADS.readADC_SingleEnded(channel);
    }

    float adcToVoltage(uint16_t adcRaw, uint8_t divP, uint8_t divM)
    {
        float voltage = ((divP + divM) * _ADS.computeVolts(adcRaw)) / divM;
        return voltage;
    }
};

#endif