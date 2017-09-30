/*
 * File name: Men.cpp
 * Created on: 28 Sep. 2017
 * Author: David Ping
 */

#include "Men.h"
#include <iostream>

namespace draughts {
namespace model {

Men::Men(direction dir, PieceType pieceType, int x, int y) :
		Piece(dir, pieceType, x, y) {
	// TODO Auto-generated constructor stub
}

Men::~Men() {
	// TODO Auto-generated destructor stub
}

bool draughts::model::Men::validMove(PieceType playerPieceType, int endx,
		int endy) {
	std::unique_ptr<Board> board;
	//Ensure the start and end positions are within the boundaries of the board
	if (0 > endx || 0 > endy
			|| board->getInstance()->getBoardLength() - 1 < endx
			|| board->getInstance()->getBoardLength() - 1 < endy) {
		return false;
	}

	//Ensure it is the current players piece
	if (pieceType != playerPieceType) {
		return false;
	}

	//Ensure there is an empty space at the end position
	if (board->getInstance()->getCells().at(endx).at(endy) != nullptr) {
		return false;
	}
	//If player1 and going down check direction is valid
	if ((pieceType == PieceType::CROSS && xcoord == endx - 1)
			&& (ycoord == endy + 1 || ycoord == endy - 1)) {
		return true;
	}
	//If player2 then going up check direction is valid
	if ((pieceType == PieceType::CIRCLE && xcoord == endx + 1)
			&& (ycoord == endy + 1 || ycoord == endy - 1)) {
		return true;
	}
	return false;
}

bool draughts::model::Men::validJump(PieceType playerPieceType, int endx,
		int endy) {
	std::unique_ptr<Board> board;
	//Ensure the start and end positions are within the boundaries of the board
	if (0 > endx || 0 > endy
			|| board->getInstance()->getBoardLength() - 1 < endx
			|| board->getInstance()->getBoardLength() - 1 < endy) {
		return false;
	}

	//Ensure it is the current players piece
	if (pieceType != playerPieceType) {
		return false;
	}

	//Ensure there is an empty space at the end position
	//Ensure the space in between is not an empty space in between
	if ((board->getInstance()->getCells().at(endx).at(endy) != nullptr)
			|| (board->getInstance()->getCells().at((xcoord + endx) / 2).at(
					(ycoord + endy) / 2) == nullptr)) {
		return false;
	}

	//Ensure the space between the start and end is an enemy piece
	//i.e. Not your piece
	if (board->getInstance()->getCells().at((xcoord + endx) / 2).at(
			(ycoord + endy) / 2)->getPieceType() == pieceType) {
		return false;
	}

	//If player1 and going down check direction is valid
	if ((PieceType::CROSS == pieceType && xcoord == endx - 2)
			&& (ycoord == endy + 2 || ycoord == endy - 2)) {
		return true;
	}
	//If player2 then going up check direction is valid
	if ((PieceType::CIRCLE == pieceType && xcoord == endx + 2)
			&& (ycoord == endy + 2 || ycoord == endy - 2)) {
		return true;
	}

	return false;
}

} /* namespace model */
} /* namespace draughts */
