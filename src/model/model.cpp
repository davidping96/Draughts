#include "model.h"

std::unique_ptr<draughts::model::model> draughts::model::model::instance =
		nullptr;

draughts::model::model::model(void) {
}

draughts::model::model * draughts::model::model::get_instance(void) {
	if (instance == nullptr) {
		instance = std::unique_ptr<model>(new model);
	}
	return instance.get();
}

void draughts::model::model::start_game(int pnum1, std::string pname1, int pnum2, std::string pname2) {
	std::unique_ptr<Game> game;
	game->getInstance()->initGame(pnum1, pname1, pnum2, pname2);
	std::cout << "Starting the game with the players" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << std::setw(0) << "Player 1" << std::setw(10) << " ID: " << pnum1
			<< std::setw(10) << "Name: " << pname1 << std::setw(5) << std::endl;
	std::cout << std::setw(0) << "Player 2" << std::setw(10) << " ID: " << pnum2
			<< std::setw(10) << "Name: " << pname2 << std::setw(5) << std::endl;
			std::cout << "----------------------------------------" << std::endl;
}

void draughts::model::model::add_player(const std::string& p) {
	if (!player_exists(p)) {
		int count = 1;
		while (1) {
			if (playerList[count] == "") {
				playerList[count] = p;
				break;
			}
			count++;
		}
		std::cout << "ID " << std::setw(20) << "Name " << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		for (std::map<int, std::string>::iterator it = playerList.begin();
				it != playerList.end(); ++it) {
			std::cout << it->first << std::setw(20) << it->second << std::endl;
		}
		std::cout << "----------------------------------------" << std::endl;
	} else {
		std::cerr << "Player name exists" << std::endl;
	}
}

bool draughts::model::model::player_exists(const std::string& pname) {
	for (std::map<int, std::string>::iterator it = playerList.begin();
			it != playerList.end(); ++it) {
		if (it->second == pname) {
			return true;
		}
	}
	return false;
}

std::map<int, std::string> draughts::model::model::get_player_list(void) const {
	return playerList;
}

void draughts::model::model::delete_instance(void) {
	instance.reset(nullptr);
}

draughts::model::model::~model(void) {
}

