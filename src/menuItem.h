#ifndef menuItem_h
#define menuItem_h

#include <iostream>
#include <string>
using namespace std;

// класс пункта меню
class MenuItem
{
public:
    MenuItem() {}
    MenuItem(int indG, string text, int mType = 0) : indexGlobal(indG), name(text), type(mType) {}

    int indexGlobal = 0; // на начальном этапе инициализации соотвествует номеру элемента массива классов
    int indexParent = 0; // номер родителя
    int indexChild = 0;  // номер первого дочернего пункта
    int levelDeep = 0;   // уровень глубины пункта, 0 - корень, 1 и больше уже подменю
    int lenght = 0;      // количество дочерних элементов
    int value = 0;       // значение, если пункт меню редактируемый
    int type = 0;        // тип меню : ... 
    string name = "";    // имя пункта, один из параметров
};

#endif