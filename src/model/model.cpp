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

void draughts::model::model::start_game(int plr1, int plr2) {
	//Pick the player that will go first
	int firstPlayer, secondPlayer;

	auto duration = std::chrono::system_clock::now().time_since_epoch();
	//seed with number of milliseconds since the unix epoch began
	long millis = std::chrono::duration_cast<std::chrono::milliseconds>(
			duration).count();
	std::mt19937 gen(millis);
	//set the range for the generator - in this case between 0 and 5 inclusive
	std::uniform_int_distribution<unsigned> dist(0, 1);
	int rand = dist(gen);

	if (rand == 0) {
		firstPlayer = plr1;
		secondPlayer = plr2;
	} else {
		firstPlayer = plr2;
		secondPlayer = plr1;
	}
	gameInstance = std::make_unique<Game>(firstPlayer,
			getPlayerName(firstPlayer), secondPlayer,
			getPlayerName(secondPlayer));
	std::cout << "Starting the game with the players" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << std::setw(0) << "Player 1" << std::setw(10) << " ID: " << plr1
			<< std::setw(10) << "Name: " << getPlayerName(firstPlayer)
			<< std::setw(5) << std::endl;
	std::cout << std::setw(0) << "Player 2" << std::setw(10) << " ID: " << plr2
			<< std::setw(10) << "Name: " << getPlayerName(secondPlayer)
			<< std::setw(5) << std::endl;
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

std::string draughts::model::model::getPlayerName(int playernum) {
	for (std::map<int, std::string>::iterator it = playerList.begin();
			it != playerList.end(); ++it) {
		if (playernum == it->first) {
			return it->second;
		}
	}
	return "";
}

draughts::model::Game * draughts::model::model::getGameInstance() {
	return gameInstance.get();
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

