#include "ui.h"
#include "../nc_controller/controller.h"
#include "../model/model.h"
//Singleton instance initialized as nullptr
std::unique_ptr<draughts::ncview::ui> draughts::ncview::ui::instance = 
    nullptr;

draughts::ncview::ui::ui(void)
    : thecontroller(draughts::nc_controller::controller::get_instance()),
        themodel(draughts::model::model::get_instance())
{
}

void draughts::ncview::ui::main_menu(void)
{
	/*Declare main_menu object the constructor will call menu constructor which will
		assign the menu commands to the menu*/
    draughts::ncview::main_menu menu;
    //Open the main menu
    menu.activate();
}

void draughts::ncview::ui::add_player(void)
{
    draughts::ncview::add_player_window newwin;
    newwin.activate();
}

void draughts::ncview::ui::play_game(void)
{
    try
    {
    	std::cout<<themodel->get_instance()->get_player_list().size()<<std::endl;
        player_selection_window newwin(themodel->get_instance()->get_player_list());
        newwin.activate();
    }
    catch(std::exception& ex)
    {
        std::cerr << "Exception: " << std::endl;
    }
}

//Singleton design pattern, if it exists return it or else make a new instance
draughts::ncview::ui * draughts::ncview::ui::get_instance(void)
{
    if(instance == nullptr)
    {
        instance = std::unique_ptr<ui>(new ui());
    }
    return instance.get();
}

void draughts::ncview::ui::delete_instance(void)
{
    instance.reset(nullptr);
}


void draughts::ncview::ui::show_game_window(draughts::ncview::player_pair
    players)
{
    game_window newwin(players);
    newwin.activate();
}

draughts::ncview::ui::~ui(void)
{
}

