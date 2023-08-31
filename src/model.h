#ifndef model_h
#define model_h

#include <Arduino.h>
#include "observable.h"
#include "menu.h"

class Model : public Observable, private ExecuteMenu
{
public:
    Model()
    {
        menuRebuild();
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
        notifyUpdate();
    }

    void setBatValue(float batValue)
    {
        _batValue = batValue;
        _batPercent = ((_batValue - 3.00) / 1.20) * 100;
        _batPercent = constrain(_batPercent, 0.00, 100.00);
        notifyUpdate();
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

    // Действия при нажатии кнопки "Эскейп"
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

    void initLocalSize(int size)
    {
        _localPos = 0;
        _localFirstIndex = 0;
        _localPosMax = size;
    }

private:
    int _menuNowPos = 1;
    bool _menuEdit = false;
    int _localPos = 0;
    int _localPosMax = 0;
    int _localFirstIndex = 0;
    float _batValue = 0;
    float _batPercent = 0;
};

#endif