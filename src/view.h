#ifndef view_h
#define view_h

#include <Arduino.h>
#include <Wire.h>
#include <u8g2lib.h>
#include "observer.h"
#include "model.h"

#define DISP_HEIGHT 64
#define DISP_WIDTH 128

#define VISIBLE_AREA_SIZE 3 - 1

class OledView : public Observer
{
public:
    OledView(Model *model) : _display(U8G2_R0, /* reset=*/U8X8_PIN_NONE)
    {
        _model = model;
        _model->addObserver(this);
        displayInit();
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
        bool edit = _model->getEdit();
        _display.clearBuffer();
        drawTop(edit);
        if (edit)
        {
            switch (_model->getType())
            {
            case 1:
                drawParam();
                break;
            case 2:
                drawAmper();
                break;
            case 3:
                drawAmper();
                break;
            case 4:
                drawWifi();
                break;
            case 5:
                drawSoftVer();
                break;
            default:
                drawError();
                break;
            }
        }
        else
        {
            drawMenu();
        }
        _display.sendBuffer();
    }
    void drawMainMenu(void)
    {
    }
    void drawTop(bool isEdit)
    {
        int pos_y = DISP_HEIGHT / 4;
        _display.setFont(u8g2_font_helvR10_te);
        _display.setCursor(5, pos_y - 4);
        if (isEdit)
        {
            _display.print(_model->getName());
        }
        else
        {
            _display.print(_model->getNameParent());
        }
        _display.drawHLine(0, pos_y - 2, DISP_WIDTH);
        drawBat();
    }
    void drawMenuItem(int posLocal, int pos)
    {
        int pos_y = (DISP_HEIGHT / 4) * (2 + posLocal) - 2;
        _display.setCursor(5, pos_y);
        _display.print(_model->getName(pos));
    }
    void drawMenu(void)
    {
        int firstPos = _model->getFirstLocalIndex();
        int currentPos = _model->getPos();
        _display.setFont(u8g2_font_helvR10_te);
        for (int i = 0; i < 3; i++)
        {
            drawMenuItem(i, firstPos + i);
            if ((firstPos + i) == currentPos)
            {
                drawCursor(i);
            }
        }
    }
    void drawCursor(int pos)
    {
        int height = DISP_HEIGHT / 4;
        int pos_y = height * (1 + pos);
        _display.drawRFrame(0, pos_y + 1, DISP_WIDTH, height - 1, 3);
    }
    void drawParam(void)
    {
        int pos_y = (DISP_HEIGHT / 4) * 3;
        int pos_x = (DISP_WIDTH / 2) - 5;
        _display.setFont(u8g2_font_helvR10_te);
        _display.setCursor(pos_x, pos_y);
        _display.print(_model->getValue());
    }
    void drawAmper(void)
    {
        int pos_y = (DISP_HEIGHT / 4) * 3;
        int pos_x = (DISP_WIDTH / 2) - 5;
        _display.setFont(u8g2_font_helvR10_te);
        _display.setCursor(pos_x, pos_y);
        _display.print(_model->getValue() / 10);
        _display.print(".");
        _display.print(_model->getValue() % 10);
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

    void drawBat(void)
    {
        int percent = _model->getBatPercent();
        _display.drawRFrame(DISP_WIDTH - 20, 2, 20, 10, 2);
        _display.setFont(u8g2_font_5x7_tn);
        _display.setCursor(DISP_WIDTH - 20, 10);
        if (percent / 100 == 0)
        {
            _display.print(" ");
        }
        if (percent / 10 == 0)
        {
            _display.print(" ");
        }
        _display.print(percent);
    }

    void drawSoftVer(void)
    {
        int pos_y = (DISP_HEIGHT / 4) * 2 - 2;
        int pos_x = 0;
        _display.setFont(u8g2_font_helvR10_te);
        _display.setCursor(pos_x, pos_y);
        _display.print("Version: ");
        _display.print(SOFTWARE_VERSION_NUMBER);
        pos_y += 16;
        _display.setCursor(pos_x, pos_y);
        _display.print("Date: ");
        _display.print(SOFTWARE_VERSION_DATE);
        pos_y += 16;
        _display.setCursor(pos_x, pos_y);
        _display.print("by ");
        _display.print(SOFTWARE_OWNER);
    }

    void drawWifi(void)
    {
        int pos_y = (DISP_HEIGHT / 4) * 2 - 2;
        int pos_x = 0;
        _display.setFont(u8g2_font_helvR10_te);
        _display.setCursor(pos_x, pos_y);
        _display.print("Connect to WIFI");
        pos_y += 16;
        _display.setCursor(pos_x, pos_y);
        _display.print("Name: ");
        _display.print(STASSID);
        pos_y += 16;
        _display.setCursor(pos_x, pos_y);
        _display.print("Pass: ");
        _display.print(STAPSK);
    }

    void drawError(void)
    {
        _display.setFont(u8g2_font_helvR10_te);
        _display.setCursor(DISP_WIDTH - 10, DISP_HEIGHT / 2);
        _display.print("ERROR");
    }
};

#endif