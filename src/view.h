#ifndef view_h
#define view_h

#include <Arduino.h>
#include <Wire.h>
#include <u8g2lib.h>
#include "observer.h"
#include "model.h"

#define DISP_HEIGHT 64
#define DISP_WIDTH 128

#define VISIBLE_AREA_SIZE 3

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
        drawMenu();
        _display.sendBuffer();
    }
    void drawMainMenu(void)
    {
    }
    void drawTop(void)
    {
        int pos_y = DISP_HEIGHT / 4 - 1;
        _display.setCursor(5, pos_y - 2);
        _display.print(_model->getNameParent());
        _display.drawHLine(0, pos_y, 1);
    }
    void drawMenuItem(int pos, int posLocal, bool frame)
    {
        int pos_y = DISP_HEIGHT / 4;
        _display.setCursor(5, (pos_y * (posLocal + 2)) - 2);
        _display.print(_model->getName(pos));
    }
    void drawMenu(void)
    {
        int pos = _model->getPos();
        int localPos = _model->getLocalPos();
        _display.setFont(u8g2_font_helvR10_te);
        drawTop();
        for (int i = 0; i < VISIBLE_AREA_SIZE; i++)
        {
            if (i == localPos)
            {
                drawMenuItem(pos, i, false);
            }
        }
    }
    void drawParam(void)
    {
    }
    void displayInit(void)
    {
        Wire.begin();
        _display.begin();
        _display.enableUTF8Print();
        _model->initLocalSize(VISIBLE_AREA_SIZE);
    }
    void drawText(void)
    {
    }
};

#endif