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
        return menuArray[menuNowPos].name;
    }

    // Устанавливает значение (value) для текущего меню и обновляет эран(view)
    void setValue(int value)
    {
        menuArray[menuNowPos].value = value;
        notifyUpdate();
    }

    // Устанавливает индекс текущего меню и обновляет эран(view)
    void setMenuPos(int menuPos)
    {
        menuNowPos = menuPos;
        notifyUpdate();
    }

    // Устанавливает состояние меню: true - редактирование параметра, false - перемещение по меню
    void setEdit(bool edit)
    {
        menuEdit = edit;
        notifyUpdate();
    }

    // Возвращает состояние меню: true - редактирование параметра, false - перемещение по меню
    bool getEdit()
    {
        return menuEdit;
    }

    // Возвращает текущий индекс выбранного пункта меню/подменю
    int getPos(void)
    {
        return menuNowPos;
    }

    // Возвращает длинну (кол-во пунктов) для текущего меню/подменю
    int getLenght(void)
    {
        return menuArray[menuArray[menuNowPos].indexParent].lenght;
    }

    // Возвращает индекс последнего пункта для текущего меню/подменю
    int getLastIndex(void)
    {
        return getFirstIndex() + getLenght() - 1;
    }

    // Возвращает индекс первого пункта для текущего меню/подменю
    int getFirstIndex(void)
    {
        return menuArray[menuArray[menuNowPos].indexParent].indexChild;
    }

    // Возвращает индекс первого дочернего пункта для текущего меню/подменю
    int getChild(void)
    {
        return menuArray[menuNowPos].indexChild;
    }

    // Возвращает тип меню для текущего пунка меню (MenuNowPos)
    int getType(void)
    {
        return menuArray[menuNowPos].type;
    }

    // Возвращает значение Value для текущего пунка меню (MenuNowPos)
    int getValue(void)
    {
        return menuArray[menuNowPos].value;
    }

    // Действия при нажатии кнопки "вверх"
    void moveUp(void)
    {
        if (menuEdit == false)
        {
            if (menuNowPos > getFirstIndex())
            {
                setMenuPos(menuNowPos - 1);
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
        if (menuEdit == false)
        {
            if (menuNowPos < getLastIndex())
            {
                setMenuPos(menuNowPos + 1);
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
        if (menuEdit == false)
        {
            if (getType() == 0)
            {
                int child = getChild();
                if (child != 0)
                {
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
        if (menuEdit == false)
        {
            setMenuPos(menuArray[menuNowPos].indexParent);
        }
        else
        {
            setEdit(false);
        }
    }

private:
};

#endif