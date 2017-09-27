/*
 * File name: Player.cpp
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include "Player.h"

namespace draughts {
namespace model {

Player::Player(int playernum, std::string pname, char c):id(playernum), name(pname), score(0), tokenType(c)  {
	// TODO Auto-generated constructor stub

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void makeMove(int, int, int, int, int){

}
	std::string draughts::model::Player::getPlayerName(){
		return name;
	}
	int draughts::model::Player::getPlayerNum(){
		return id;
	}
	int draughts::model::Player::getPlayerScore(){
		return score;
	}
	char draughts::model::Player::getTokenType(){
		return tokenType;
	}

} /* namespace model */
} /* namespace draughts */
