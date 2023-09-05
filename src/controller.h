#ifndef controller_h
#define controller_h

#include "settings.h"
#include "model.h"
#include "keyboard.h"
#include "MCU_hardware/adc.h"
#include "MCU_hardware/ampere.h"

class Controller
{
public:
    Controller(Model *model) : _keyboard()

    {
        _model = model;
        _model->setMenuPos(0);
        _model->execute(BUTTON_ENTER_CODE);
    }

    // Опрос кнопок, отправка соответствующих команд в модель.
    void loop()
    {
        buttonsHandle();
        measureHandle();
    }

private:
    Model *_model;
    Keyboard _keyboard;
    Measure _adc;
    output _out;

    void measureHandle(void)
    {
        static unsigned long curmil = 0;
        if (millis() - curmil > POOL_MEASURMENT_BAT_MS)
        {
            _model->setBatValue(_adc.getValue(ADC_BAT, MEASURMENT_BAT_COUNT));
            curmil = millis();
        }
    }

    void update(bool isEditChanged)
    {
        int type = _model->getType();
        bool edit = _model->getEdit();

        switch (type)
        {
        case 2:
            if (isEditChanged)
            {
                _out.switcher(AMPERE_PS_ON, edit);
                _model->setValue(40);
            }
            else
            {
                _out.setValue(_model->getValue());
            }
        case 3:
            if (isEditChanged)
            {
                _out.switcher(AMPERE_PS_OFF, edit);
                _model->setValue(40);
            }
            else
            {
                _out.setValue(_model->getValue());
            }
        }
    }

    void buttonsHandle(void)
    {
        int input = _keyboard.getState();
        if (input)
        {
            update(_model->execute(input));
        }
    }
};

#endif