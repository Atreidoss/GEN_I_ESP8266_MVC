#ifndef menuItem_h
#define menuItem_h

#include <Arduino.h>

// Список типов меню
enum menuType : int
{
    MENU_TYPE_MENU,                 // 0 - меню/подменю, не редактируемый параметр
    MENU_TYPE_NUMBER,               // 1 - целое число, редактируемый
    MENU_TYPE_CURRENT_INTERNAL,     // 2 - задание тока встроенный источник, редактируемый
    MENU_TYPE_CURRENT_EXTERNAL,     // 3 - задание тока внешний источник, редактируемый
    MENU_TYPE_WIFI,                 // 4 - обновление по вайфай, редактируемый
    MENU_TYPE_SOFT_VERSION,         // 5 - версия ПО
};
// класс пункта меню
class MenuItem
{
public:
    MenuItem() {}
    MenuItem(int indG, String text, int mType = MENU_TYPE_MENU) : indexGlobal(indG), name(text), type(mType) {}

    int indexGlobal = 0; // на начальном этапе инициализации соотвествует номеру элемента массива классов
    int indexParent = 0; // номер родителя
    int indexChild = 0;  // номер первого дочернего пункта
    int levelDeep = 0;   // уровень глубины пункта, 0 - корень, 1 и больше уже подменю
    int lenght = 0;      // количество дочерних элементов
    int value = 0;       // значение, если пункт меню редактируемый
    int type = 0;        // тип меню : ...
    bool eeprom = false; // сохранять ли пункт в энергонезависимую память
    String name = "";    // имя пункта, один из параметров
};

#endif






