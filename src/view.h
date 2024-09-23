#ifndef view_h
#define view_h

#include <Arduino.h>
#include <Wire.h>
#include <u8g2lib.h>
#include "observer.h"
#include "model.h"
#include "logo.cpp"
#include "Menu/langs.h"

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
    bool lang = 0; // 0 - английский, 1 - Русский

    void
    draw(void)
    {
        bool edit = _model->getEdit();
        _display.clearBuffer();
        lang = _model->intToBool(_model->getMenuTypeValue(MENU_TYPE_LANG));
        drawTop(edit);
        if (edit)
        {
            switch (_model->getType())
            {
            case MENU_TYPE_NUMBER:
                drawParam();
                break;
            case MENU_TYPE_CURRENT_INTERNAL:
                drawAmper();
                break;
            case MENU_TYPE_CURRENT_EXTERNAL:
                drawAmper();
                break;
            case MENU_TYPE_WIFI:
                drawWifi();
                break;
            case MENU_TYPE_SOFT_VERSION:
                drawSoftVer();
                break;
            case MENU_TYPE_CAL_4MA:
                drawParam();
                break;
            case MENU_TYPE_CAL_20MA:
                drawParam();
                break;
            case MENU_TYPE_LANG:
                drawLang();
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

    void drawTop(bool isEdit)
    {
        int pos_y = DISP_HEIGHT / 4;
        if (lang)
        {
            _display.setFont(u8g2_font_cu12_t_cyrillic); // u8g2_font_helvR10_te);
        }
        else
        {
            _display.setFont(u8g2_font_helvR10_te);
        }
        _display.setCursor(5, pos_y - 4);
        if (isEdit)
        {
            _display.print(_model->getName(lang));
        }
        else
        {
            _display.print(_model->getNameParent(lang));
        }
        _display.drawHLine(0, pos_y - 2, DISP_WIDTH);
        drawBat();
    }
    void drawMenuItem(int posLocal, int pos)
    {
        int pos_y = (DISP_HEIGHT / 4) * (2 + posLocal) - 2;
        _display.setCursor(5, pos_y);
        _display.print(_model->getName(pos, lang)); // pos));
    }
    void drawMenu(void)
    {
        int firstPos = _model->getFirstLocalIndex();
        int currentPos = _model->getPos();
        if (lang)
        {
            _display.setFont(u8g2_font_cu12_t_cyrillic); // u8g2_font_helvR10_te);
        }
        else
        {
            _display.setFont(u8g2_font_helvR10_te);
        }
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
    // todo добавить вывод 10Bit PWM
    void drawAmper(void)
    {
        int pos_y = (DISP_HEIGHT / 4) * 3;
        int pos_x = (DISP_WIDTH / 2) - 20;
        _display.setFont(u8g2_font_inb16_mn); // u8g2_font_helvR10_te);
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
        _display.clearBuffer();
        _display.drawXBMP(0, 0, logo_width, logo_height, logo);
        _display.sendBuffer();
        delay(1500);
    }

    void drawLang(void)
    {
        int pos_y = (DISP_HEIGHT / 4) * 3;
        int pos_x = (DISP_WIDTH / 3) - 5;
        _display.setCursor(pos_x, pos_y);
        if (lang)
        {
            _display.setFont(u8g2_font_cu12_t_cyrillic); // u8g2_font_helvR10_te);
        }
        else
        {
            _display.setFont(u8g2_font_helvR10_te);
        }
        _display.print(namesLang[MENU_LANG_LANG][lang]);
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
        if (lang)
        {
            _display.setFont(u8g2_font_cu12_t_cyrillic); // u8g2_font_helvR10_te);
        }
        else
        {
            _display.setFont(u8g2_font_helvR10_te);
        }
        _display.setCursor(pos_x, pos_y);
        _display.print(namesLang[MENU_LANG_VERSION][lang]); //("Version: ");
        _display.print(SOFTWARE_VERSION_NUMBER);
        pos_y += 16;
        _display.setCursor(pos_x, pos_y);
        _display.print(namesLang[MENU_LANG_DATE][lang]); //("Date: ");
        _display.print(SOFTWARE_VERSION_DATE);
        pos_y += 16;
        _display.setCursor(pos_x, pos_y);
        _display.print(namesLang[MENU_LANG_OWNER][lang]);
        // _display.print("by ");
        // _display.print(SOFTWARE_OWNER);
    }
    void drawWifi(void)
    {
        int pos_y = (DISP_HEIGHT / 4) * 2 - 2;
        int pos_x = 0;
        if (lang)
        {
            _display.setFont(u8g2_font_cu12_t_cyrillic); // u8g2_font_helvR10_te);
        }
        else
        {
            _display.setFont(u8g2_font_helvR10_te);
        }
        if (_model->getWifiState())
        {
            _display.setCursor(pos_x, pos_y);
            _display.print(namesLang[MENU_LANG_URL][lang]); //"Open URL: ");
            pos_y += 16;
            _display.setFont(u8g2_font_helvR08_tf);
            _display.setCursor(pos_x + 5, pos_y);
            _display.print(_model->getIP());
            _display.print("/update");
        }
        else
        {
            _display.setCursor(pos_x, pos_y);
            _display.print(namesLang[MENU_LANG_CONNECT][lang]); //"Connect to WIFI");
            pos_y += 16;
            _display.setCursor(pos_x, pos_y);
            _display.print(namesLang[MENU_LANG_NAME][lang]); //"Name: ");
            _display.print(STASSID);
            pos_y += 16;
            _display.setCursor(pos_x, pos_y);
            _display.print(namesLang[MENU_LANG_PASS][lang]); //"Pass: ");
            _display.print(STAPSK);
        }
    }
    void drawError(void)
    {
        if (lang)
        {
            _display.setFont(u8g2_font_cu12_t_cyrillic); // u8g2_font_helvR10_te);
        }
        else
        {
            _display.setFont(u8g2_font_helvR10_te);
        }
        _display.setCursor(DISP_WIDTH / 2 - 30, DISP_HEIGHT / 2 + 10);
        _display.print(namesLang[MENU_LANG_ERROR][lang]); //"ERROR");
    }
};

#endif