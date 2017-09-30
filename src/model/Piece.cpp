/*
 * File name: Piece.cpp
 * Created on: 27 Sep. 2017
 * Author: David Ping
 */

#include "Piece.h"

namespace draughts {
namespace model {

Piece::Piece(direction dir, PieceType pt, int x, int y):moveDirection(dir), pieceType(pt), xcoord(x), ycoord(y) {
	// TODO Auto-generated constructor stub
}

Piece::~Piece() {
	// TODO Auto-generated destructor stub
}

direction draughts::model::Piece::getDirection(){
	return moveDirection;
}

PieceType draughts::model::Piece::getPieceType(){
	return pieceType;
}

} /* namespace model */
} /* namespace draughts */
