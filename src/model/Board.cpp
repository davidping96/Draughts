/*
 * File name: Board.cpp
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include "Board.h"
#include <iostream>

namespace draughts {
namespace model {

Board::Board() {
	initBoard();
}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

int draughts::model::Board::getHeight() {
	return height;
}
int draughts::model::Board::getWidth() {
	return width;
}

char draughts::model::Board::getToken(int x, int y) {
	return cells.at(x - 1).at(y - 1);
}

void draughts::model::Board::setToken(int x, int y, char c){
	cells.at(x).at(y)=c;
}

std::vector<std::vector<char>> draughts::model::Board::getCells() {
	return cells;
}

void draughts::model::Board::initBoard() {
	std::vector<std::vector<char>> board;
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
	cells = board;
}

} /* namespace model */
} /* namespace draughts */
