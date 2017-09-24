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

int draughts::model::model::get_player_score(int playernum) {
	return EOF;
}

void draughts::model::model::start_game(int plr1, int plr2) {
	//Pick the player that will go first
	player1 = std::make_pair(plr1, 'x');
	player2 = std::make_pair(plr2, 'o');

	//Random number generator
	std::default_random_engine generator;
	//Random number 0 to 1 inclusive
	std::uniform_int_distribution<int> distribution(0, 1);
	//Acquire random number
	int rand = distribution(generator);

	if (rand == 0) {
		currentPlayer = player1.first;
	} else {
		currentPlayer = player2.first;
	}

	//Start the game, the selected_list contains the names of the two players
	std::cout << "Starting the game with the players" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	std::cout << std::setw(0) << "Player 1" << std::setw(10) << " ID: "
			<< player1.first << std::setw(20) << "Name: "
			<< get_player_name(player1.first) << std::setw(25) << player1.second
			<< std::endl;
	std::cout << std::setw(0) << "Player 2" << std::setw(10) << " ID: "
			<< player2.first << std::setw(20) << "Name: "
			<< get_player_name(player2.first) << std::setw(25) << player2.second
			<< std::endl;

	//Set up the board 8x8
	//Add the tokens to a vector, x's on the top, o's on the bottom
	for (int i = 0; i < height; ++i) {
		std::vector<char> v;
		char c = ' ';
		for (int j = 0; j < width; ++j) {
			if (i < height / 2 - 1) {
				c = 'x';
			} else if (i > height / 2) {
				c = 'o';
			}
			if (i % 2 == j % 2) {
				v.push_back(' ');
			} else {
				v.push_back(c);
			}
		}
		board.push_back(v);
	}
}

int draughts::model::model::get_winner() {
	return EOF;
}

std::string draughts::model::model::get_player_name(int id) {
	for (std::map<int, std::string>::iterator it = playerList.begin();
			it != playerList.end(); ++it) {
		if (it->first == id) {
			return it->second;
		}
	}
	return "";
}

char draughts::model::model::get_token(int x, int y) {
	return board.at(x - 1).at(y - 1);
}

void draughts::model::model::make_move(int playernum, int startx, int starty,
		int endx, int endy) {
	char currPlayerToken = get_player_token(playernum);

	//Check if a player has won or lost or draw
	//if player has no possible moves/jump
	//if opponent has  no possible moves/jump

	//Check if any jumps are possible
	//while a jump is possible
	//check if the move made is a valid jump
	//Check if a player has won or lost
	//Last piece taken

	//If no jumps are possible check if the move is a valid move

	//If the piece ends up in the kingsrow promote it to a king

}

bool draughts::model::model::possibleJumps() {
	int playernum = get_current_player();
	int enemynum;
	if (playernum == player1.first) {
		enemynum = player2.first;
	} else {
		enemynum = player1.first;
	}

	for (unsigned int i = 0; i < board.size(); i++) {
		for (unsigned int j = 0; j < board.at(i).size(); j++) {
			//For normal pieces
			if (board.at(i).at(j) == get_player_token(playernum)) {
				//If it is player 1 check Down
				if (playernum == player1.first) {
					//If it is within boundaries of the board and the enemies token is there
					if ((i > 0 && j > 0)
							&& board.at(i - 1).at(j - 1)
									== get_player_token(enemynum)) {
						//If the jump is within boundaries and the jump dest is empty
						if ((i > 1 && j > 1)
								&& board.at(i - 2).at(j - 2) == ' ') {
							return true;
						}
					}
					if ((i > 0 && j < board.size() - 1)
							&& board.at(i - 1).at(j + 1)
									== get_player_token(enemynum)) {
						if ((i > 1 && j < board.size() - 2)
								&& board.at(i - 2).at(j + 2) == ' ') {
							return true;
						}
					}
				}
				//If it is player 2 check Up
				if (playernum == player2.first) {
					//If it is within boundaries of the board and the enemies token is there
					if ((i < board.size() && j > 0)
							&& board.at(i + 1).at(j - 1)
									== get_player_token(enemynum)) {
						//If the jump is within boundaries and the jump dest is empty
						if ((i < board.size() - 1 && j > 1)
								&& board.at(i + 2).at(j - 2) == ' ') {
							return true;
						}
					}
					if ((i < board.size() && j < board.size() - 1)
							&& board.at(i - 1).at(j + 1)
									== get_player_token(enemynum)) {
						if ((i < board.size() - 1 && j < board.size() - 2)
								&& board.at(i + 2).at(j + 2) == ' ') {
							return true;
						}
					}
				}

			}

			//For king pieces check both directions

		}
	}
	return false;
}

bool draughts::model::model::possibleMoves() {
	return false;
}

void draughts::model::model::add_player(const std::string& p) {
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

int draughts::model::model::get_current_player(void) {
	return get_instance()->currentPlayer;
}

char draughts::model::model::get_player_token(int id) {
	if (id == player1.first) {
		return player1.second;
	} else {
		return player2.second;
	}
}

void draughts::model::model::swap_players(void) {
	if (currentPlayer == player1.first) {
		currentPlayer = player2.first;
	} else {
		currentPlayer = player1.first;
	}
}

std::map<int, std::string> draughts::model::model::get_player_list(void) const {
	return playerList;
}

void draughts::model::model::delete_instance(void) {
	instance.reset(nullptr);
}

int draughts::model::model::get_width() {
	return width;
}

int draughts::model::model::get_height() {
	return height;
}

draughts::model::model::~model(void) {
}

