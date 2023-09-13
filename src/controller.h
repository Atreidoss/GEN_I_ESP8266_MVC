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
        measureHandle();
        wifiHandle(_isWifiOn);
    }

private:
    Model *_model;
    Keyboard _keyboard;
    Measure _adc;
    output _out;
    web _update;

    bool _isWifiOn = false;

    void updateCustomMenu(bool isEditSwitched)
    {
        int type = _model->getType();
        bool edit = _model->getEdit();

        switch (type)
        {
        case MENU_TYPE_MENU:
            break;
        case MENU_TYPE_NUMBER:
            break;
        case MENU_TYPE_CURRENT_INTERNAL:
            currentControl(isEditSwitched, edit, AMPERE_PS_ON);
            break;
        case MENU_TYPE_CURRENT_EXTERNAL:
            currentControl(isEditSwitched, edit, AMPERE_PS_OFF);
            break;
        case MENU_TYPE_WIFI:
            wifiControl(isEditSwitched, edit);
            break;
        case MENU_TYPE_SOFT_VERSION:
            break;
        case MENU_TYPE_CAL_4MA:
            calControl(isEditSwitched, edit);
            break;
        }
    }

    // Включает/выключает напряжение и генерацию тока при входе/выходе из этого меню
    // Задает ШИМ эквивалентный заданному выходному току (пересчет тока в 10бит ШИМ в объекте _out)
    void currentControl(bool isSwitched, bool isEdit, int mode)
    {
        if (isSwitched)
        {
            _out.switcher(mode, isEdit);
            _model->setValue(CURRENT_4MA_INT_X10);
        }
        else
        {
            _out.setValue(_model->getValue());
        }
    }

    // Включает/выключает WIFI, подключается к точке доступа и получает IP при входе/выходе из этого меню
    void wifiControl(bool isSwitched, bool isEdit)
    {
        if (isSwitched)
        {
            _update.setMode(isEdit);
            _isWifiOn = isEdit;
            if (isEdit)
            {
                _model->setIP(_update.getIP());
            }
            _model->setWifiState(isEdit);
        }
    }

    void calControl(bool isSwitched, bool isEdit)
    {
        if (isSwitched)
        {
            _out.switcher(AMPERE_PS_ON, isEdit);
            _out.set4(_model->getValue());
        }
        else
        {
            _out.setPwm(_model->getValue());
        }
    }

    // Крутится в цикле, получает события нажатий/зажатий кнопок от клавиатуры
    // Передает событие в модель для обновления состояния
    // По событию формирует управление переферией (измерение нарпяжений, шим генерация тока,
    // вкл/выкл внутреннего источника питания, запуск веб интерфейса)
    void buttonsHandle(void)
    {
        int input = _keyboard.getState();
        if (input)
        {
            updateCustomMenu(_model->execute(input));
        }
    }

    void measureHandle(void)
    {
        static unsigned long curmil = 0;
        if (millis() - curmil > POOL_MEASURMENT_BAT_MS)
        {
            _model->setBatValue(_adc.getValue(ADC_BAT, MEASURMENT_BAT_COUNT));
            curmil = millis();
        }
    }
    void wifiHandle(bool mode)
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