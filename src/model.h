#ifndef model_h
#define model_h

#include <Arduino.h>
#include "observable.h"
#include "Menu/menu.h"
#include "MCU_hardware/eeprom.h"

#define CONTROL_MEMORY_CODE 12345

class Model : public Observable, private ExecuteMenu
{
public:
    Model()
    {
        menuRebuild();
        // _mem.init(512);
        // // initData(menuRebuild());
        // _mem.writeInt(0, 77);
        // setValue(3,_mem.getInt(0));
    }

    // Возвращает имя пункта меню/подменю для указанного индекса
    String getName(int menuPos)
    {
        return menuArray[menuPos].name;
    }

    // Возвращает имя текущего пункта меню/подменю
    String getName(void)
    {
        return menuArray[_menuNowPos].name;
    }

    // Возвращает имя родительского меню для текущего пункта меню/подменю
    String getNameParent(void)
    {
        return getName(getParent());
    }

    // Устанавливает значение (value) для текущего меню и обновляет эран(view)
    void setValue(int value)
    {
        menuArray[_menuNowPos].value = value;
        notifyUpdate();
    }

    // Устанавливает значение (value) для указанного меню и обновляет эран(view)
    void setValue(int pos, int value)
    {
        menuArray[pos].value = value;
    }

    // Устанавливает индекс текущего меню и обновляет эран(view)
    void setMenuPos(int menuPos)
    {
        _menuNowPos = menuPos;
        setLocalPos();
        notifyUpdate();
    }

    void setLocalPos(void)
    {
        _localFirstIndex = _menuNowPos - _localPos;
    }

    // Устанавливает состояние меню: true - редактирование параметра, false - перемещение по меню
    void setEdit(bool edit)
    {
        _menuEdit = edit;
        // saveData();
        notifyUpdate();
    }

    void setBatValue(float batValue)
    {
        _batValue = batValue;
        _batPercent = ((_batValue - 3.00) / 1.20) * 100;
        _batPercent = constrain(_batPercent, 0.00, 100.00);
        notifyUpdate();
    }

    void setWifiState(bool state)
    {
        _wifiState = state;
        notifyUpdate();
    }

    void setIP(String ip)
    {
        _ip = ip;
    }

    float getBatValue(void)
    {
        return _batValue;
    }

    float getBatPercent(void)
    {
        return _batPercent;
    }
    // Возвращает состояние меню: true - редактирование параметра, false - перемещение по меню
    bool getEdit()
    {
        return _menuEdit;
    }

    // Возвращает текущий индекс выбранного пункта меню/подменю
    int getPos(void)
    {
        return _menuNowPos;
    }

    int getLocalPos(void)
    {
        return _localPos;
    }

    int getFirstLocalIndex(void)
    {
        return _localFirstIndex;
    }

    // Возвращает длинну (кол-во пунктов) для текущего меню/подменю
    int getLenght(void)
    {
        return menuArray[getParent()].lenght;
    }

    // Возвращает индекс последнего пункта для текущего меню/подменю
    int getLastIndex(void)
    {
        return getFirstIndex() + getLenght() - 1;
    }

    // Возвращает индекс первого пункта для текущего меню/подменю
    int getFirstIndex(void)
    {
        return menuArray[getParent()].indexChild;
    }
    // Возвращает индекс первого дочернего пункта для текущего меню/подменю
    int getChild(void)
    {
        return menuArray[_menuNowPos].indexChild;
    }

    int getParent(void)
    {
        return menuArray[_menuNowPos].indexParent;
    }

    // Возвращает тип меню для текущего пунка меню (_menuNowPos)
    int getType(void)
    {
        return menuArray[_menuNowPos].type;
    }

    // Возвращает значение Value для текущего пунка меню (_menuNowPos)
    int getValue(void)
    {
        return menuArray[_menuNowPos].value;
    }

    // Возвращает значение Value для указанного пунка меню (_menuNowPos)
    int getValue(int pos)
    {
        return menuArray[pos].value;
    }

    bool getWifiState(void)
    {
        return _wifiState;
    }

    // Возвращает IP адресс прибора
    String getIP(void)
    {
        return _ip;
    }

    bool execute(int input)
    {
        bool prevEdit = _menuEdit;
        switch (input)
        {
        case BUTTON_UP_CODE: // Стрелка вверх
            moveUp();
            break;
        case BUTTON_DOWN_CODE: // Стрелка вниз
            moveDown();
            break;
        case BUTTON_ENTER_CODE: // Ввод
            executeAction();
            break;
        case BUTTON_ESCAPE_CODE: // Эскейп
            cancelAction();
            break;
        case BUTTON_BACKSPACE_CODE: // Бэкспейс
            break;
        default:
            notifyUpdate();
            break;
        }
        if (prevEdit == _menuEdit)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void initLocalSize(int size)
    {
        _localPos = 0;
        _localFirstIndex = 0;
        _localPosMax = size;
    }

private:
    Eeprom _mem;
    int _menuNowPos = 1;
    bool _menuEdit = false;
    int _localPos = 0;
    int _localPosMax = 0;
    int _localFirstIndex = 0;
    float _batValue = 0;
    float _batPercent = 0;
    String _ip = "";
    bool _wifiState = false;
    int _tempValue = 0;

    void initData(int len)
    {
        int slotSize = sizeof(int);
        _mem.init(slotSize * (len + 1));
        if (_mem.getInt(slotSize * (len + 1)) != CONTROL_MEMORY_CODE)
        {
            _mem.writeInt(slotSize * (len + 1), CONTROL_MEMORY_CODE);
            for (int i = 0; i < len; i++)
            {
                _mem.writeInt(slotSize * i, getValue(i));
            }
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                setValue(i, _mem.getInt(slotSize * i));
            }
        }
    }

    void saveData(void)
    {
        int slotSize = sizeof(int);
        int val = getValue();
        if (_menuEdit)
        {
            _tempValue = val;
        }
        else
        {
            if (_tempValue != val)
            {
                _mem.writeInt(slotSize * _menuNowPos, val);
            }
        }
    }

    // Действия при нажатии кнопки "вверх"
    void moveUp(void)
    {
        if (_menuEdit == false)
        {
            if (_menuNowPos > getFirstIndex())
            {
                if (_localPos > 0)
                {
                    _localPos--;
                }
                setMenuPos(_menuNowPos - 1);
            }
        }
        else
        {
            int tempValue = getValue();
            setValue(++tempValue);
        }
    }

    // Действия при нажатии кнопки "вниз"
    void moveDown(void)
    {
        if (_menuEdit == false)
        {
            if (_menuNowPos < getLastIndex())
            {
                if (_localPos < _localPosMax)
                {
                    _localPos++;
                }
                setMenuPos(_menuNowPos + 1);
            }
        }
        else
        {
            int tempValue = getValue();
            setValue(--tempValue);
        }
    }

    // Действия при нажатии кнопки "Ввод"
    void executeAction(void)
    {
        if (_menuEdit == false)
        {
            if (getType() == 0)
            {
                int child = getChild();
                if (child != 0)
                {
                    _localPos = 0;
                    setMenuPos(child);
                }
                else
                {
                    setEdit(true);
                }
            }
            else
            {
                setEdit(true);
            }
        }
        else
        {
            setEdit(false);
        }
    }

    // Действия при нажатии кнопки "Эскейп" ( зажатие кнопки Ввод )
    void cancelAction(void)
    {
        if (_menuEdit == false)
        {
            _localPos = 0;
            int parent = getParent();
            if (parent > 0)
                setMenuPos(parent);
        }
        else
        {
            setEdit(false);
        }
    }
};

#endif