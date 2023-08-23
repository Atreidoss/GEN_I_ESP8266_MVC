#ifndef view_h
#define view_h

#include <Arduino.h>
#include <Wire.h>
#include <u8g2lib.h>
#include "observer.h"
#include "model.h"

#define DISP_HEIGHT 64
#define DISP_WIDTH 128

class OledView : public Observer
{
public:
    OledView(Model *model) : _display(U8G2_R0, /* reset=*/U8X8_PIN_NONE)
    {
        _model = model;
        _model->addObserver(this);
        displayInit();
    }

    void init(void)
    {
        _display.clearBuffer();
        _display.setFont(u8g2_font_10x20_t_cyrillic);
        _display.setCursor(0, 32);
        _display.print("start programm");
        _display.sendBuffer();
    }

    // Если режим редактирования значения - тогда выводим навание пункта текущего
    // меню и значение, обновляется при каждом нажатии кнопок вверх/вних
    // иначе выводит список всех пунктов текущего меню/подменю и курсор на против текущего пункта
    virtual void update()
    {
        draw();
    }

private:
    U8G2_SH1106_128X64_NONAME_F_HW_I2C _display;
    Model *_model;
    void draw(void)
    {
        _display.clearBuffer();
        _display.setFont(u8g2_font_10x20_t_cyrillic);
        _display.setCursor(0, 32);
        // _display.print(_model->getName().c_str());
        _display.print(_model->getPos());
        _display.sendBuffer();
    }
    void drawMainMenu(void)
    {
    }
    void drawMenu(void)
    {
        _display.setFont(u8g2_font_10x20_t_cyrillic);
        _display.setCursor(10, 63);
        _display.drawHLine(0, 22, DISP_WIDTH);
    }
    void drawParam(void)
    {
    }
    void displayInit(void)
    {
        Wire.begin();
        _display.begin();
        _display.enableUTF8Print();
    }
    void drawText(void)
    {
    }
};

#endif