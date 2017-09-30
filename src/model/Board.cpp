/*
 * File name: Board.cpp
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include "Board.h"
#include "Men.h"

namespace draughts {
namespace model {

std::unique_ptr<draughts::model::Board> draughts::model::Board::instance =
		nullptr;

Board::Board() {

}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

Board * draughts::model::Board::getInstance() {
	if (instance == nullptr) {
		instance = std::unique_ptr<Board>(new Board);
	}
	return instance.get();
}

void draughts::model::Board::deleteInstance() {
	instance.reset(nullptr);
}

std::vector<std::vector<std::unique_ptr<Piece>>> & draughts::model::Board::getCells() {
	return cells;
}

Piece * draughts::model::Board::getPiece(int x, int y) {
	return cells.at(x - 1).at(y - 1).get();
}

int draughts::model::Board::getBoardLength() {
	return boardLength;
}

void draughts::model::Board::setPiece(int x, int y, std::unique_ptr<Piece> p) {
	cells.at(x).at(y) = std::move(p);
}

bool draughts::model::Board::pieceKinged(int startx, int starty, int endx) {
	//If the start position is a normal piece (not a king)
	//and the end position is the kingsrow
	if(cells.at(startx).at(starty)->getDirection()!=direction::BOTH){
		if(cells.at(startx).at(starty)->getDirection()==direction::UP && endx == 0){
			return true;
		}else if(cells.at(startx).at(starty)->getDirection()==direction::DOWN && endx == boardLength - 1){
			return true;
		}
	}
	return false;
}

void draughts::model::Board::initBoard() {
	//Set up the board 8x8
	//Add the pieces to a vector, x's on the top, o's on the bottom
	for (int i = 0; i < boardLength; ++i) {
		std::vector<std::unique_ptr<Piece>> v;
		for (int j = 0; j < boardLength; ++j) {
			std::unique_ptr<Piece> p;
			if (i < boardLength / 2 - 1) {
				p = std::make_unique<Men>(direction::DOWN, PieceType::CROSS, i, j);
			} else if (i > boardLength / 2) {
				p = std::make_unique<Men>(direction::UP, PieceType::CIRCLE, i, j);
			}
			if (i % 2 != j % 2) {
				v.push_back(std::move(p));
			} else {
				v.push_back(nullptr);
			}
		}
		cells.push_back(std::move(v));
	}
}

} /* namespace model */
} /* namespace draughts */
