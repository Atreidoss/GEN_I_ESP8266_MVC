#ifndef controller_h
#define controller_h

#include "settings.h"
#include "model.h"
#include "keyboard.h"
#include "MCU_hardware/adc.h"
#include "MCU_hardware/ampere.h"
#include "MCU_hardware/web.h"

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
        measureHandle(_isWifiOn);
        updateHandle(_isWifiOn);
    }

private:
    Model *_model;
    Keyboard _keyboard;
    Measure _adc;
    output _out;
    web _update;

    bool _isWifiOn = false;

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
            break;
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
            break;
        case 4:
            if (isEditChanged)
            {
                _update.setMode(edit);
                _model->setIP(_update.getIP());
                _isWifiOn = edit;
            }
            else
            {
            }
            break;
        case 5:
            break;
        }
    }

    void buttonsHandle(void)
    {
        int input = _keyboard.getState();
        if (input)
        {
            this->update(_model->execute(input));
        }
    }

    void measureHandle(bool mode)
    {
        static unsigned long curmil = 0;
        if (!mode)
        {
            if (millis() - curmil > POOL_MEASURMENT_BAT_MS)
            {
                _model->setBatValue(_adc.getValue(ADC_BAT, MEASURMENT_BAT_COUNT));
                curmil = millis();
            }
        }
    }
    void updateHandle(bool mode)
    {
        if (mode)
        {
            _update.handle();
        }
        else
        {
        }
    }
};

#endif