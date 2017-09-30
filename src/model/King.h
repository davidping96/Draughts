/*
 * File name: King.h
 * Created on: 28 Sep. 2017
 * Author: David Ping
 */

#include "Piece.h"

#ifndef MODEL_KING_H_
#define MODEL_KING_H_

namespace draughts {
namespace model {

class King : public Piece{
public:
	King(PieceType, int, int);
	virtual bool validMove(PieceType, int, int) override;
	virtual bool validJump(PieceType, int, int) override;
	virtual ~King();
};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_KING_H_ */
