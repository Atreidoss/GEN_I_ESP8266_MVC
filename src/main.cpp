#include "controller.h"
#include "view.h"

Model model;
OledView view(&model);
Controller controller(&model);

void setup(void)
{
}

void loop(void)
{
    controller.loop();
}
