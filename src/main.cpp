#include "controller.h"
#include "view.h"
#include "MCU_hardware/web.h"

Model model;
OledView view(&model);
Controller controller(&model);

void setup(void)
{
    web();
}

void loop(void)
{
    controller.loop();
    wb_loop();
}
