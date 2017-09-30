/*
 * File name: Piece.h
 * Created on: 27 Sep. 2017
 * Author: David Ping
 */

#include "../direction.h"
#include "../PieceType.h"

#ifndef MODEL_PIECE_H_
#define MODEL_PIECE_H_

namespace draughts {
namespace model {

class Piece {
protected:
	direction moveDirection;
	PieceType pieceType;
	int xcoord;
	int ycoord;
public:
	Piece(direction, PieceType, int, int);
	virtual ~Piece();
	direction getDirection();
	PieceType getPieceType();
	virtual bool validMove(PieceType, int, int)=0;
	virtual bool validJump(PieceType, int, int)=0;

};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_PIECE_H_ */
