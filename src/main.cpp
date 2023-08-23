#include "controller.h"
#include "MCU_hardware/web.h"

Model model;
OledView view(&model);
Controller controller(&model);

void setup(void)
{
    view.init();
    web();
}

void loop(void)
{
    controller.loop();
    wb_loop();
}
