#ifndef controller_h
#define controller_h

#include "settings.h"
#include "model.h"
#include "view.h"
#include "keyboard.h"

class Controller
{
public:
    Controller(Model *model) : _keyboard()

    {
        _model = model;
        _model->setMenuPos(0);
    }

    // Опрос кнопок, отправка соответствующих команд в модель.
    void loop()
    {
        buttonsHandle();
    }

    void init(void)
    {
        
    }

private:
    Model *_model;
    Keyboard _keyboard;

    void buttonsHandle(void)
    {
        int input = _keyboard.getState();
        switch (input)
        {
        case BUTTON_UP_CODE: // Стрелка вверх
        {
            _model->moveUp();
            break;
        }
        case BUTTON_DOWN_CODE: // Стрелка вниз
        {
            _model->moveDown();
            break;
        }
        case BUTTON_ENTER_CODE: // Ввод
        {
            _model->executeAction();
            break;
        }
        case BUTTON_ESCAPE_CODE: // Эскейп
        {
            _model->cancelAction();
            break;
        }
        case BUTTON_BACKSPACE_CODE: // Бэкспейс
        {
            break;
        }
        }
    }
};

#endif