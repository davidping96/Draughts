/*
 * File name: Player.cpp
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include "Player.h"
#include "King.h"
#include "Men.h"
#include <iostream>
namespace draughts {
namespace model {

Player::Player(int pnum, std::string pname, PieceType ptype) :
		playernum(pnum), name(pname), pieceType(ptype), score(0) {
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

int draughts::model::Player::getPlayerNum() {
	return playernum;
}

std::string draughts::model::Player::getPlayerName() {
	return name;
}

PieceType draughts::model::Player::getPieceType() {
	return pieceType;
}

int draughts::model::Player::getPlayerScore() {
	return score;
}

bool draughts::model::Player::possibleJumps() {
	std::unique_ptr<Board> board;
	//For every cell on the board
	for (int i = 0; i < board->getInstance()->getBoardLength(); i++) {
		for (int j = 0; j < board->getInstance()->getBoardLength(); j++) {
			//If it is not empty and it is the current players piece
			//Check if any direction is a valid jump
			if (board->getInstance()->getCells().at(i).at(j) != nullptr) {
				if (board->getInstance()->getCells().at(i).at(j)->validJump(
						pieceType, i + 2, j + 2)) {
					return true;
				}
				if (board->getInstance()->getCells().at(i).at(j)->validJump(
						pieceType, i + 2, j - 2)) {
					return true;
				}
				if (board->getInstance()->getCells().at(i).at(j)->validJump(
						pieceType, i - 2, j + 2)) {
					return true;
				}
				if (board->getInstance()->getCells().at(i).at(j)->validJump(
						pieceType, i - 2, j - 2)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool draughts::model::Player::possibleMoves() {
	std::unique_ptr<Board> board;
	for (int i = 0; i < board->getInstance()->getBoardLength(); i++) {
		for (int j = 0; j < board->getInstance()->getBoardLength(); j++) {
			if (board->getInstance()->getCells().at(i).at(j) != nullptr) {
				if (board->getInstance()->getCells().at(i).at(j)->validMove(
						pieceType, i + 1, j + 1)) {
					return true;
				}
				if (board->getInstance()->getCells().at(i).at(j)->validMove(
						pieceType, i + 1, j - 1)) {
					return true;
				}
				if (board->getInstance()->getCells().at(i).at(j)->validMove(
						pieceType, i - 1, j + 1)) {
					return true;
				}
				if (board->getInstance()->getCells().at(i).at(j)->validMove(
						pieceType, i - 1, j - 1)) {
					return true;
				}
			}
		}
	}
	return false;
}

void draughts::model::Player::makeMove(int startx, int starty, int endx,
		int endy) {
	std::unique_ptr<Board> board;
	direction d;
	//If the players piece is CROSS d = down else d = up
	if (pieceType == PieceType::CROSS) {
		d = direction::DOWN;
	} else {
		d = direction::UP;
	}
	std::unique_ptr<Piece> men = std::make_unique<Men>(d, pieceType, endx,
			endy);
	std::unique_ptr<Piece> king = std::make_unique<King>(pieceType, endx, endy);
	//If it is a jump
	if (board->getInstance()->getCells().at(startx).at(starty) != nullptr
			&& board->getInstance()->getCells().at(startx).at(starty)->validJump(
					pieceType, endx, endy)) {
		//If a king is jumping make the end position a king
		if (board->getInstance()->getCells().at(startx).at(starty)->getDirection()
				== direction::BOTH) {
			board->getInstance()->setPiece(endx, endy, std::move(king));
		} else {
			//Place players piece on the end position
			board->getInstance()->setPiece(endx, endy, std::move(men));
		}
		//Empty the start position
		board->getInstance()->setPiece(startx, starty, nullptr);
		//Take the enemy piece
		board->getInstance()->setPiece((startx + endx) / 2, (starty + endy) / 2,
				nullptr);
		++score;
	}
	//Check if it is a move
	if (board->getInstance()->getCells().at(startx).at(starty) != nullptr
			&& board->getInstance()->getCells().at(startx).at(starty)->validMove(
					pieceType, endx, endy)) {
		//If a king is moving make the end position a king
		if (board->getInstance()->getCells().at(startx).at(starty)->getDirection()
				== direction::BOTH) {
			board->getInstance()->setPiece(endx, endy, std::move(king));
		} else {
			//Place players piece on the end position
			board->getInstance()->setPiece(endx, endy, std::move(men));
		}
		//Empty the start position
		board->getInstance()->setPiece(startx, starty, nullptr);
	}
	//If the piece ends up in the kingsrow promote it to a king
	if (board->getInstance()->getCells().at(endx).at(endy)->getDirection()
			!= direction::BOTH) {
		if (pieceType == PieceType::CROSS) {
			if (endx == board->getInstance()->getBoardLength() - 1) {
				board->getInstance()->setPiece(endx, endy, std::move(king));
			}
		} else if (pieceType == PieceType::CIRCLE) {
			if (endx == 0) {
				board->getInstance()->setPiece(endx, endy, std::move(king));
			}
		}
	}
}

bool draughts::model::Player::moreJumps(int startx, int starty) {
	std::unique_ptr<Board> board;
	//If king piece check up and down
	if (board->getInstance()->getCells().at(startx).at(starty) == nullptr) {
		return false;
	}

	if (board->getInstance()->getCells().at(startx).at(starty)->getDirection()
			== direction::BOTH) {
		//Check all directions for possible jump
		if (board->getInstance()->getCells().at(startx).at(starty)->validJump(
				pieceType, startx - 2, starty + 2)) {
			return true;
		}
		if (board->getInstance()->getCells().at(startx).at(starty)->validJump(
				pieceType, startx - 2, starty - 2)) {
			return true;
		}
		if (board->getInstance()->getCells().at(startx).at(starty)->validJump(
				pieceType, startx + 2, starty + 2)) {
			return true;
		}
		if (board->getInstance()->getCells().at(startx).at(starty)->validJump(
				pieceType, startx + 2, starty - 2)) {
			return true;
		}
	}
	//If player1 check going down
	if (pieceType == PieceType::CROSS) {
		if (board->getInstance()->getCells().at(startx).at(starty)->validJump(
				pieceType, startx + 2, starty + 2)) {
			return true;
		}
		if (board->getInstance()->getCells().at(startx).at(starty)->validJump(
				pieceType, startx + 2, starty - 2)) {
			return true;
		}
	}
	//If player2 check going up
	if (pieceType == PieceType::CIRCLE) {
		if (board->getInstance()->getCells().at(startx).at(starty)->validJump(
				pieceType, startx - 2, starty + 2)) {
			return true;
		}
		if (board->getInstance()->getCells().at(startx).at(starty)->validJump(
				pieceType, startx - 2, starty - 2)) {
			return true;
		}
	}
	return false;
}
} /* namespace model */
} /* namespace draughts */
