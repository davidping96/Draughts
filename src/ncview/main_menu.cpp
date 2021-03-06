#include "main_menu.h"
#include "../nc_controller/command.h"
#include "../nc_controller/controller.h"

//Menu items in a string vector
const std::vector<std::string> draughts::ncview::main_menu::strings = {
    "Add Player to the system",  
    "Play Game", "Exit Game"
};

/*main_menu(title (inherited from menu class), menu_text string vector,
	controller instance->main_menu commands (command vector))*/
draughts::ncview::main_menu::main_menu(void)
    : menu("English Draughts", strings, 
        draughts::nc_controller::controller::controller::get_instance()
            ->get_main_menu_commands())
{
}

draughts::ncview::main_menu::~main_menu(void)
{
}
