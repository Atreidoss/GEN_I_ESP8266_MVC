#ifndef settings_h
#define settings_h

#define SOFTWARE_VERSION_NUMBER  "1.1"
#define SOFTWARE_VERSION_DATE    "06.06.2023"
#define SOFTWARE_OWNER           "Shuvalov Vladimir"

//---------------------------Настройки кнопок управления-----------------------------------------------------------------
#define SETTINGS_BUTTONS_POOL
#define EB_DEB 5                   // Задержка обработки дребезга, мс
#define EB_CLICK 150               // таймаут накликивания кнопки, мс
#define BUTTON_HOLD_TIMEOUT 500    // Время после которого зажатая начинает возвращать true, мс (32-8100)
#define BUTTON_STEP_TIMEOUT 50     // Период с которым зажатая кнопка возвращает true, мс (32-8100)
#define BUTTON_POLL_MEASURMENT_MS 2// Период опроса кнопок в прерывании, мс
#define PIN_BUTTON_ENTER 13        // Номер ножки контроллера для кнопки Ввод
#define PIN_BUTTON_UP 2            // Номер ножки контроллера для кнопки Вверх
#define PIN_BUTTON_DOWN 12         // Номер ножки контроллера для кнопки Вниз

//---------------------------Настройки генерации Напряжения и Тока-------------------------------------------------------
#define SETTINGS_AMPERE
#define PIN_PWM_AMPERE 14          // Номер ножки ШИМ генерации 4-20 мА
#define PIN_ITERNAL_POWER_SUPPLY 3 // Номер ножки подачи напряжения от внутреннего источника питания
#define PWM_RESOLUTION 10          // Разрешение ШИМ, бит
#define PWM_FREQUENCY 1000         // Частота ШИМ, Гц

//---------------------------Настройки кнопок управления-----------------------------------------------------------------
#define SETTINGS_BUTTON_CODE
#define BUTTON_UP_CODE 72         // Код кнопки Вверх
#define BUTTON_DOWN_CODE 80       // Код кнопки Вниз
#define BUTTON_ENTER_CODE 13      // Код кнопки Ввод
#define BUTTON_ESCAPE_CODE 27     // Код кнопки Выход
#define BUTTON_BACKSPACE_CODE 8   // Код кнопки Назад/Стереть
#define BUTTON_NON_JUST_UPDATE 99 // Код чисто для запуска обновления экрана

//------------------------Настройки WIFI ---------------------------------------------------------------------------------
#define SETTINGS_WIFI
#define STASSID "mark2"     // Имя сети WiFi
#define STAPSK "mark2mark2" // Пароль сети WiFi

//------------------------Настройки АЦП ADS1x15 --------------------------------------------------------------------------
#define SETTINGS_ADC
#define ADC_ADDR 0x48 // Адресс по шине i2c
// CH0 - I value, делитель канала 0 (в кОм), измерение тока
#define ADC_I 0
#define DIV_CH0_M 10
#define DIV_CH0_P 100
// CH1 - U value, делитель канала 1 (в кОм), измерение внешнего напряжения
#define ADC_U 1
#define DIV_CH1_M 10
#define DIV_CH1_P 10
// CH2 - Bat value, делитель канала 2 (в кОм), измерение напряжения аккумулятора
#define ADC_BAT 2
#define DIV_CH2_M 10
#define DIV_CH2_P 10
// CH3 - value, делитель канала 3 (в кОм), измерение напряжения 
#define ADC_CH3 3    // reserved
#define DIV_CH3_M 10 // reserved
#define DIV_CH3_P 10 // reserved

#define POOL_MEASURMENT_BAT_MS 500 // Период измерения напряжения батареи, мс
#define MEASURMENT_BAT_COUNT 15    // Количество измерений напряжения батареи, мс

#endif