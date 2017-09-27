/*
 * File name: Game.cpp
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include "Game.h"
#include <iostream>

namespace draughts {
namespace model {

Game::Game(int pnum1, std::string pname1, int pnum2, std::string pname2):
		player1(new Player(pnum1, pname1, 'x')),player2(new Player(pnum2, pname2, 'o')),
		board(new Board),winner(-1){
	currentPlayer = player1->getPlayerNum();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

int draughts::model::Game::getCurrentPlayer(){
	return currentPlayer;
}

void draughts::model::Game::swapPlayers(){
	if(currentPlayer==player1->getPlayerNum()){
		currentPlayer=player2->getPlayerNum();
	}else{
		currentPlayer=player1->getPlayerNum();
	}
}

int draughts::model::Game::getWinner() {
	return winner;
}

bool draughts::model::Game::possibleJumps() {
	int playernum = getCurrentPlayer();

	for (int i = 0; i < board->getHeight(); i++) {
		for (int j = 0; j < board->getWidth(); j++) {
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

bool draughts::model::Game::validJump(int playernum, int startx, int starty,
		int endx, int endy) {

	int enemynum;
	if (playernum == player1->getPlayerNum()) {
		enemynum = player2->getPlayerNum();
	} else if (playernum == player2->getPlayerNum()) {
		enemynum = player1->getPlayerNum();
	}

//Ensure the start and end positions are within the boundaries of the board
	if (0 > startx || 0 > starty || 0 > endx || 0 > endy
			|| board->getHeight() - 1 < startx || board->getWidth() - 1 < starty
			|| board->getHeight() - 1 < endx || board->getWidth() - 1 < endy) {
		return false;
	}

//Ensure the start is a player piece
	if (board->getCells().at(startx).at(starty) != getPlayerToken(playernum)
			&& board->getCells().at(startx).at(starty)
								!= std::toupper(getPlayerToken(playernum))) {
		return false;
	}
//Ensure there is an empty space at the end position
	if (!(board->getCells().at(endx).at(endy) == ' ')) {
		return false;
	}
//Ensure the space between the start and end is an enemy piece
	if (!(board->getCells().at((startx + endx) / 2).at((starty + endy) / 2)
			== getPlayerToken(enemynum))
			&& !(board->getCells().at((startx + endx) / 2).at((starty + endy) / 2)
					== std::toupper(getPlayerToken(enemynum)))) {
		return false;
	}

//If player1 and going down check direction is valid
	if ((playernum == player1->getPlayerNum() && startx == endx - 2)
			&& (starty == endy + 2 || starty == endy - 2)) {
		return true;
	}
//If player2 then going up check direction is valid
	if ((playernum == player2->getPlayerNum() && startx == endx + 2)
			&& (starty == endy + 2 || starty == endy - 2)) {
		return true;
	}
//If king piece go up or down
	if (board->getCells().at(startx).at(starty) == std::toupper(getPlayerToken(playernum))
			&& (startx == endx + 2 || startx == endx - 2)
			&& (starty == endy + 2 || starty == endy - 2)) {
		return true;
	}

	return false;
}

bool draughts::model::Game::possibleMoves() {
	int playernum = getCurrentPlayer();
	for (int i = 0; i < board->getHeight(); i++) {
			for (int j = 0; j < board->getWidth(); j++) {
				if (validMove(playernum, i, j, i + 1, j + 1)) {
					return true;
				}
				if (validMove(playernum, i, j, i + 1, j - 1)) {
					return true;
				}
				if (validMove(playernum, i, j, i - 1, j + 1)) {
					return true;
				}
				if (validMove(playernum, i, j, i - 1, j - 1)) {
					return true;
				}
			}
		}
	return false;
}

bool draughts::model::Game::validMove(int playernum, int startx, int starty,
		int endx, int endy) {
//Ensure the start and end positions are within the boundaries of the board
	if (0 > startx || 0 > starty || 0 > endx || 0 > endy
			|| board->getHeight() - 1 < startx || board->getWidth() - 1 < starty
			|| board->getHeight() - 1 < endx || board->getWidth() - 1 < endy) {
		return false;
	}

//Ensure the start is a player piece
	if (board->getCells().at(startx).at(starty) != getPlayerToken(playernum)
			&& board->getCells().at(startx).at(starty)
					!= std::toupper(getPlayerToken(playernum))) {
		return false;
	}
//Ensure there is an empty space at the end position
	if (board->getCells().at(endx).at(endy) != ' ') {
		return false;
	}

//If player1 and going down check direction is valid
	if ((playernum == player1->getPlayerNum() && startx == endx - 1)
			&& (starty == endy + 1 || starty == endy - 1)) {
		return true;
	}
//If player2 then going up check direction is valid
	if ((playernum == player2->getPlayerNum() && startx == endx + 1)
			&& (starty == endy + 1 || starty == endy - 1)) {
		return true;
	}
//If king piece go up or down
	if (board->getCells().at(startx).at(starty) == std::toupper(getPlayerToken(playernum))
			&& (startx == endx + 1 || startx == endx - 1)
			&& (starty == endy + 1 || starty == endy - 1)) {
		return true;
	}

	return false;
}

void draughts::model::Game::make_move(int playernum, int startx, int starty,
		int endx, int endy) {

	//If it is a jump
	if (validJump(playernum, startx, starty, endx, endy)) {
		//If a king is jumping make the end position a king
		if (board->getCells().at(startx).at(starty)
				== std::toupper(getPlayerToken(playernum))) {
			board->setToken(endx, endy, std::toupper(getPlayerToken(playernum)));
		} else {
			//Place players piece on the end position
			board->setToken(endx, endy, getPlayerToken(playernum));
		}
		//Empty the start position
		board->setToken(startx, starty, ' ');
		//Take the enemy piece
		board->setToken((startx + endx) / 2, (starty + endy) / 2, ' ');
	}

	//Check if it is a move
	if (validMove(playernum, startx, starty, endx, endy)) {
		//If a king is moving make the end position a king
		if (board->getCells().at(startx).at(starty)
				== std::toupper(getPlayerToken(playernum))) {
			board->setToken(endx, endy, std::toupper(getPlayerToken(playernum)));
		} else {
			//Place players piece on the end position
			board->setToken(endx, endy, getPlayerToken(playernum));
		}
		//Empty the start position
		board->setToken(startx, starty, ' ');
	}

	//If the piece ends up in the kingsrow promote it to a king
	if (playernum == player1->getPlayerNum()) {
		if (endx == board->getHeight() - 1) {
			board->setToken(endx, endy, std::toupper(getPlayerToken(playernum)));
		}
	} else if (playernum == player2->getPlayerNum()) {
		if (endx == 0) {
			board->setToken(endx, endy, std::toupper(getPlayerToken(playernum)));
		}
	}
}

bool draughts::model::Game::moreJumps(int playernum, int startx, int starty) {

//If king piece check up and down
	if (board->getCells().at(startx).at(starty)
			== std::toupper(getPlayerToken(playernum))) {
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
	if (playernum == player1->getPlayerNum()) {
		if (validJump(playernum, startx, starty, startx + 2, starty + 2)) {
			return true;
		}
		if (validJump(playernum, startx, starty, startx + 2, starty - 2)) {
			return true;
		}
	}
//If player2 check going up
	if (playernum == player2->getPlayerNum()) {
		if (validJump(playernum, startx, starty, startx - 2, starty + 2)) {
			return true;
		}
		if (validJump(playernum, startx, starty, startx - 2, starty - 2)) {
			return true;
		}
	}
	return false;
}

char draughts::model::Game::getPlayerToken(int playernum){
	if(playernum == player1->getPlayerNum()){
		return player1->getTokenType();
	}else{
		return player2->getTokenType();
	}
}

std::string draughts::model::Game::getPlayerName(int playernum){
	if(playernum == player1->getPlayerNum()){
		return player1->getPlayerName();
	}else{
		return player2->getPlayerName();
	}
}

int draughts::model::Game::getPlayerScore(int playernum){
	if(playernum == player1->getPlayerNum()){
		return player1->getPlayerScore();
	}else{
		return player2->getPlayerScore();
	}
}

draughts::model::Board * draughts::model::Game::getBoard(){
	return board.get();
}


} /* namespace model */
} /* namespace draughts */
