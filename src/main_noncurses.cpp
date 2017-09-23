#include "ncview/ui.h"
#include "nc_controller/controller.h"
#include "model/model.h"

int main(void)
{
	//Program implemented using MVC design pattern
	//An instance of the ui is made and assigned a ui pointer called view
    draughts::ncview::ui * view = draughts::ncview::ui::get_instance();
    //After exiting the memory is freed by these functions to the system does not have to
    atexit(draughts::ncview::ui::delete_instance);
    atexit(draughts::nc_controller::controller::delete_instance);
    atexit(draughts::model::model::delete_instance);
    //Use the user interface and open the main menu
    view->main_menu();
}
