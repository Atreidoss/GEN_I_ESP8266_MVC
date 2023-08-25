#ifndef menu_h
#define menu_h

#include "menuItem.h"

#define NEXT_LEVEL(x) (x + 1)
#define PREV_LEVEL(x) (x - 1)
#define ADDR_CHILD(x, y) (x + 1 - y)
#define MENU_SIZE 20

class ExecuteMenu
{
public:
    ExecuteMenu() {}

    MenuItem menuArray[MENU_SIZE];

    int menuNowPos = 1;
    bool menuEdit = false;

    // Собственно записывает данные в массив, по умолчанию класс инициализируетрся со значениями
    // соответствующими корневому пункту
    void Menu(MenuItem mi)
    {
        if (mi.indexGlobal > 0)
        {
            for (int i = mi.indexGlobal - 1; i >= 0; i--)
            {
                if (menuArray[i].levelDeep < mi.levelDeep)
                {
                    menuArray[i].lenght++;
                    break;
                }
            }
        }
        menuArray[mi.indexGlobal] = mi;
    }

    // Дает понять что вставляем подменю, наглядно выглядит строение меню при заполнении
    // С помощью этой функции у каждого элемента меню определяется параметр levelDeep
    MenuItem SubMenu(MenuItem mi)
    {
        mi.levelDeep++;
        return mi;
    }

    // Прошерстить весь массив классов, образующих меню, с целью нахождения
    // максимального значения параметра класса MenuItem.levelDeep
    int getMaxLevel(int menuSize)
    {
        int maxLevel = 0;
        for (int i = 0; i < MENU_SIZE; i++)
        {
            if (maxLevel < menuArray[i].levelDeep)
            {
                maxLevel = menuArray[i].levelDeep;
            }
        }
        return maxLevel;
    }

    // Небольшая функция для свапа двух ячеек массива
    void swapArrayElements(int addr1, int addr2)
    {
        MenuItem tempMenu;
        tempMenu = menuArray[addr1];
        menuArray[addr1] = menuArray[addr2];
        menuArray[addr2] = tempMenu;
    }

    // Пошагово проходим по всем пунктам массива. начиная с определенного адреса и до конца массива
    // пока не найдем первое совпадение у с элементом класса MenuItem.levelDeep и перетаскиваем этот элемент
    // на тот адрес с которого начинали, поочередно меняя его местами с предыдущим.
    // Используется для выстроения элементов меню в порядке возрастания уровня глубины 0-1-1-1-2-2-2-2-3-3-3-3-3-3-3
    bool moveMenu(int indexStart, int level, int menuSize)
    {
        bool isLevelMatch = false;
        for (int i = indexStart; i < menuSize; i++)
        {
            if (menuArray[i].levelDeep == level)
            {
                isLevelMatch = true;
                for (int indexEnd = i; indexStart < indexEnd; indexEnd--)
                {
                    swapArrayElements(indexEnd, indexEnd - 1);
                }
                break;
            }
        }
        return isLevelMatch;
    }

    // Устанавливает для всех ячеек массива параметры indexParent и indexChild
    void setDepend(int menuSize)
    {
        for (int i = menuSize - 1; i > 0; i--)
        {
            for (int j = i; j >= 0; j--)
            {
                int len = menuArray[j].lenght;
                if (len)
                {
                    if (menuArray[j].indexChild == 0)
                    {
                        for (int k = 0; k < len; k++)
                        {
                            menuArray[i - k].indexParent = j;
                            menuArray[j].indexChild = i - k;
                        }
                        i = i - len;
                    }
                }
            }
        }
    }

    // Функция для заполнения массива класса MenuItem, образующих меню.
    // После выполнения у всех элементов массива присваиваются значения для indexGlobal, levelDeep, lenght + имена
    // и другие необходимые параметры в будущем
    // Возвращает реальное количество пунктов меню
    int menuBuild(void)
    {
        int num = 0;
        Menu(MenuItem(num++, "Осн. меню"));
        Menu(SubMenu(MenuItem(num++, "Ток U внутр.", 1)));
        Menu(SubMenu(MenuItem(num++, "Ток U внеш.", 1)));
        Menu(SubMenu(MenuItem(num++, "Измер. U", 1)));
        Menu(SubMenu(MenuItem(num++, "Калибровка")));
        Menu(SubMenu(SubMenu(MenuItem(num++, "Кал. 4 мА", 1))));
        Menu(SubMenu(SubMenu(MenuItem(num++, "Кал. 20 мА", 1))));
        Menu(SubMenu(SubMenu(MenuItem(num++, "Кал. U пит.", 1))));
        Menu(SubMenu(SubMenu(MenuItem(num++, "Кал. U бат.", 1))));
        Menu(SubMenu(MenuItem(num++, "Настройки", 1)));
        Menu(SubMenu(MenuItem(num++, "Версия ПО", 1)));
        return num;
    }

    // Расставляет элементы меню в порядке возрастания уровня глубины 0-1-1-1-2-2-2-2-3-3-3-3-3-3-3
    // Устанавливает для всех ячеек массива параметры indexParent и indexChild
    void menuRebuild(void)
    {
        int realSize = menuBuild();
        int maxLevel = getMaxLevel(realSize);
        int level = 0;
        for (int i = 0; i < realSize; i++)
        {
            for (int j = level; j < maxLevel; j++)
            {
                if (moveMenu(i, j, realSize) == false)
                {
                    level++;
                }
                else
                {
                    break;
                }
            }
        }
        setDepend(realSize);
    }
};

#endif