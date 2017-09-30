#include "controller.h"
#include "../ncview/ui.h"
#include "../model/model.h"

std::unique_ptr<draughts::nc_controller::controller> draughts::nc_controller::controller::instance =
		nullptr;

draughts::nc_controller::controller::controller(void) {

}

draughts::model::model * draughts::nc_controller::controller::get_model(void) {
	return model::model::get_instance();
}

draughts::ncview::ui * draughts::nc_controller::controller::get_view(void) {
	return ncview::ui::get_instance();
}

draughts::nc_controller::controller*
draughts::nc_controller::controller::get_instance(void) {
	if (instance == nullptr) {
		instance = std::unique_ptr<controller>(new controller);
	}
	return instance.get();
}

std::vector<std::unique_ptr<draughts::nc_controller::command>> draughts::nc_controller::controller::get_main_menu_commands(
		void) {
	std::vector<std::unique_ptr<command>> main_menu_commands;
	main_menu_commands.emplace_back(std::make_unique<addplayer_command>());
	main_menu_commands.emplace_back(std::make_unique<newgame_command>());
	main_menu_commands.emplace_back(std::make_unique<exit_command>());
	return std::move(main_menu_commands);
}

void draughts::nc_controller::controller::delete_instance(void) {
	instance.reset(nullptr);
}

void draughts::nc_controller::controller::start_game(
		std::map<int, std::string> players) {
	//Declare a int vector for ids
	std::vector<int> ids;
	//Make player equivalent to an int string pair
	using player = std::pair<int, std::string>;
	//Declare the 2 players
	player player1, player2;
	//Declare a pair for the 2 players
	std::pair<player, player> theplayers;
	int count = 0;
	for (auto & pair : players) {
		count++;
		ids.push_back(pair.first);
		if (count == 1) {
			player1 = pair;
		} else {
			player2 = pair;
		}
	}
	//Define theplayers as the pair of player1 and player2
	theplayers = std::make_pair(player1, player2);
	//With the two players defined start the game (sides, board setup)
	get_model()->get_instance()->start_game(ids[0], player1.second, ids[1], player2.second);
	get_view()->get_instance()->show_game_window(theplayers);
}

draughts::nc_controller::controller::~controller(void) {
}
