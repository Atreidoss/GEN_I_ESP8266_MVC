#ifndef langs_h
#define langs_h

#include <Arduino.h>

enum langType : int
{
    MENU_LANG_VERSION,
    MENU_LANG_DATE,
    MENU_LANG_OWNER,
    MENU_LANG_URL,
    MENU_LANG_CONNECT,
    MENU_LANG_NAME,
    MENU_LANG_PASS,
    MENU_LANG_ERROR,
    MENU_LANG_LANG
};

const String namesLang[][2] =
{
{"Version: ", "Версия: "},
{"Date: " , "Дата: "},
{"by Shuvalov Vladimir", "Шувалов Владимир"},
{"Open URL: ", "Ссылка: "},
{"Connect to WIFI", "Подкл. к WIFI"},
{"Name: ", "Имя: "},
{"Pass: ", "Пар: "},
{"ERROR", "ОШИБКА"},
{"English", "Русский"}
};

#endif