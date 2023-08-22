#ifndef settings_h
#define settings_h


#define EB_DEB 5                    // Задержка обработки дребезга, мс
#define EB_CLICK 150                // Период с которым зажатая кнопкуа возвращает true, мс

#define PIN_BUTTON_ENTER 13         // Номер ножки контроллера для кнопки Ввод
#define PIN_BUTTON_UP 2             // Номер ножки контроллера для кнопки Вверх
#define PIN_BUTTON_DOWN 12          // Номер ножки контроллера для кнопки Вниз

#define BUTTON_POLL_MEASURMENT_MS 2 // Период опроса кнопок в прерывании, мс

#define BUTTON_UP        72         // Код кнопки Вверх
#define BUTTON_DOWN      80         // Код кнопки Вниз
#define BUTTON_ENTER     13         // Код кнопки Ввод
#define BUTTON_ESCAPE    27         // Код кнопки Выход
#define BUTTON_BACKSPACE  8         // Код кнопки Назад/Стереть

#define STASSID "mark2"             // Имя сети WiFi
#define STAPSK  "mark2mark2"        // Пароль сети WiFi

#define TEST_DEF 777

#endif