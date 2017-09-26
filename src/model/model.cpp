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
			<< get_player_name(player1.first) << std::setw(5) << player1.second
			<< std::endl;
	std::cout << std::setw(0) << "Player 2" << std::setw(10) << " ID: "
			<< player2.first << std::setw(20) << "Name: "
			<< get_player_name(player2.first) << std::setw(5) << player2.second
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

	//If it is a jump
	if (validJump(playernum, startx, starty, endx, endy)) {
		//If a king is jumping make the end position a king
		if (board.at(startx).at(starty)
				== std::toupper(get_player_token(playernum))) {
			board.at(endx).at(endy) = std::toupper(get_player_token(playernum));
		} else {
			//Place players piece on the end position
			board.at(endx).at(endy) = get_player_token(playernum);
		}
		//Empty the start position
		board.at(startx).at(starty) = ' ';
		//Take the enemy piece
		board.at((startx + endx) / 2).at((starty + endy) / 2) = ' ';
	}

	//Check if it is a move
	if (validMove(playernum, startx, starty, endx, endy)) {
		//If a king is moving make the end position a king
		if (board.at(startx).at(starty)
				== std::toupper(get_player_token(playernum))) {
			board.at(endx).at(endy) = std::toupper(get_player_token(playernum));
		} else {
			//Place players piece on the end position
			board.at(endx).at(endy) = get_player_token(playernum);
		}
		//Empty the start position
		board.at(startx).at(starty) = ' ';
	}

	//If the piece ends up in the kingsrow promote it to a king
	if (playernum == player1.first) {
		if (endx == 0) {
			board.at(endx).at(endy) = std::toupper(get_player_token(playernum));
		}
	} else if (playernum == player2.first) {
		if (endx == get_height() - 1) {
			board.at(endx).at(endy) = std::toupper(get_player_token(playernum));
		}
	}
}

bool draughts::model::model::possibleJumps() {
	int playernum = get_current_player();

	for (unsigned int i = 0; i < board.size(); i++) {
		for (unsigned int j = 0; j < board.at(i).size(); j++) {
			if (validJump(playernum, i, j, i + 2, j + 2)) {
				return true;
			}
			if (validJump(playernum, i, j, i + 2, j - 2)) {
				return true;
			}
			if (validJump(playernum, i, j, i - 2, j + 2)) {
				return true;
			}
			if (validJump(playernum, i, j, i - 2, j - 2)) {
				return true;
			}
		}
	}
	return false;
}

bool draughts::model::model::possibleMoves() {
	int playernum = get_current_player();
	for (unsigned int i = 0; i < board.size(); ++i) {
		for (unsigned int j = 0; j < board.at(i).size(); ++j) {
			if (board.at(i).at(j) == get_player_token(playernum)) {
				//If it is player 1 check Down
				if (playernum == player1.first) {
					if ((i < board.size() - 1 && j > 0)
							&& board.at(i + 1).at(j - 1) == ' ') {
						return true;
					}
					if ((i < board.size() - 1 && j < board.size() - 1)
							&& board.at(i + 1).at(j + 1) == ' ') {
						return true;
					}
				}
				//If it is player 2 check Up
				if (playernum == player2.first) {
					if ((i > 0 && j > 0) && board.at(i - 1).at(j - 1) == ' ') {
						return true;
					}
					if ((i > 0 && j < board.size() - 1)
							&& board.at(i - 1).at(j + 1) == ' ') {
						return true;
					}
				}
			}
			//For king pieces check both directions
			if (board.at(i).at(j)
					== std::toupper(get_player_token(playernum))) {
				if ((i > 0 && j > 0) && board.at(i - 1).at(j - 1) == ' ') {
					return true;
				}
				if ((i > 0 && j < board.size() - 1)
						&& board.at(i - 1).at(j + 1) == ' ') {
					return true;
				}
				if ((i < board.size() - 1 && j > 0)
						&& board.at(i + 1).at(j - 1) == ' ') {
					return true;
				}
				if ((i < board.size() - 1 && j < board.size() - 1)
						&& board.at(i + 1).at(j + 1) == ' ') {
					return true;
				}
			}
		}
	}
	return false;
}

bool draughts::model::model::validJump(int playernum, int startx, int starty,
		int endx, int endy) {

	int enemynum;
	if (playernum == player1.first) {
		enemynum = player2.first;
	} else if (playernum == player2.first) {
		enemynum = player1.first;
	}

//Ensure the start and end positions are within the boundaries of the board
	if (0 > startx || 0 > starty || 0 > endx || 0 > endy
			|| get_height() - 1 < startx || get_height() - 1 < starty
			|| get_height() - 1 < endx || get_height() - 1 < endy) {
		return false;
	}

//Ensure the start is a player piece
	if (board.at(startx).at(starty) != get_player_token(playernum)
			&& board.at(startx).at(starty)
					!= std::toupper(get_player_token(playernum))) {
		return false;
	}
//Ensure there is an empty space at the end position
	if (!(board.at(endx).at(endy) == ' ')) {
		return false;
	}
//Ensure the space between the start and end is an enemy piece
	if (!(board.at((startx + endx) / 2).at((starty + endy) / 2)
			== get_player_token(enemynum))
			&& !(board.at((startx + endx) / 2).at((starty + endy) / 2)
					== std::toupper(get_player_token(enemynum)))) {
		return false;
	}

//If player1 and going down check direction is valid
	if ((playernum == player1.first && startx == endx - 2)
			&& (starty == endy + 2 || starty == endy - 2)) {
		return true;
	}
//If player2 then going up check direction is valid
	if ((playernum == player2.first && startx == endx + 2)
			&& (starty == endy + 2 || starty == endy - 2)) {
		return true;
	}
//If king piece go up or down
	if (board.at(startx).at(starty) == std::toupper(get_player_token(playernum))
			&& (startx == endx + 2 || startx == endx - 2)
			&& (starty == endy + 2 || starty == endy - 2)) {
		return true;
	}

	return false;
}

bool draughts::model::model::moreJumps(int playernum, int startx, int starty) {

//If king piece check up and down
	if (board.at(startx).at(starty)
			== std::toupper(get_player_token(playernum))) {
		//Check all directions for possible jump
		if (validJump(playernum, startx, starty, startx - 2, starty + 2)) {
			return true;
		}
		if (validJump(playernum, startx, starty, startx - 2, starty - 2)) {
			return true;
		}
		if (validJump(playernum, startx, starty, startx + 2, starty + 2)) {
			return true;
		}
		if (validJump(playernum, startx, starty, startx + 2, starty - 2)) {
			return true;
		}
	}
//If player1 check going down
	if (playernum == player1.first) {
		if (validJump(playernum, startx, starty, startx + 2, starty + 2)) {
			return true;
		}
		if (validJump(playernum, startx, starty, startx + 2, starty - 2)) {
			return true;
		}
	}
//If player2 check going up
	if (playernum == player2.first) {
		if (validJump(playernum, startx, starty, startx - 2, starty + 2)) {
			return true;
		}
		if (validJump(playernum, startx, starty, startx - 2, starty - 2)) {
			return true;
		}
	}
	return false;
}

bool draughts::model::model::validMove(int playernum, int startx, int starty,
		int endx, int endy) {
//Ensure the start and end positions are within the boundaries of the board
	if (0 > startx || 0 > starty || 0 > endx || 0 > endy
			|| get_height() - 1 < startx || get_height() - 1 < starty
			|| get_height() - 1 < endx || get_height() - 1 < endy) {
		return false;
	}

//Ensure the start is a player piece
	if (board.at(startx).at(starty) != get_player_token(playernum)
			&& board.at(startx).at(starty)
					!= std::toupper(get_player_token(playernum))) {
		return false;
	}
//Ensure there is an empty space at the end position
	if (board.at(endx).at(endy) != ' ') {
		return false;
	}

//If player1 and going down check direction is valid
	if ((playernum == player1.first && startx == endx - 1)
			&& (starty == endy + 1 || starty == endy - 1)) {
		return true;
	}
//If player2 then going up check direction is valid
	if ((playernum == player2.first && startx == endx + 1)
			&& (starty == endy + 1 || starty == endy - 1)) {
		return true;
	}
//If king piece go up or down
	if (board.at(startx).at(starty) == std::toupper(get_player_token(playernum))
			&& (startx == endx + 1 || startx == endx - 1)
			&& (starty == endy + 1 || starty == endy - 1)) {
		return true;
	}

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
	return currentPlayer;
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

