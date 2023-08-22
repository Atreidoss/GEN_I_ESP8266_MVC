#ifndef keyboard_h_
#define keyboard_h_

#include "Arduino.h"
#include <Ticker.h>
#include "MCU_hardware/button.h"
#include "settings.h"

class Keyboard
{

public:
    Keyboard() : enter(PIN_BUTTON_ENTER, INVERSE_INPUT),
                 up(PIN_BUTTON_UP, NO_INVERSE_INPUT),
                 down(PIN_BUTTON_DOWN, INVERSE_INPUT)
    {
        _buttonsTicker.attach_ms(BUTTON_POLL_MEASURMENT_MS,
                                 [this]()
                                 {
                                     tickerLoop();
                                 });
    };
    int getState(void){
        int state = 0;
        if (up.click() or up.step()){
            state  = BUTTON_UP;
        }
        if (down.click() or down.step()){
            state  = BUTTON_DOWN;
        }
        
        if (enter.click()){
            state  = BUTTON_ENTER;
        }
        if (enter.held()){
            state  = BUTTON_UP;
        }
        return state;
    };

private:
    Ticker _buttonsTicker;
    Button enter;
    Button up;
    Button down;

    void tickerLoop(void)
    {
        enter.tick();
        up.tick();
        down.tick();
    }
};
#endif