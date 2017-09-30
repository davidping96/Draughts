/*
 * File name: Men.h
 * Created on: 28 Sep. 2017
 * Author: David Ping
 */

#include "Piece.h"
#include "Board.h"

#ifndef MODEL_MEN_H_
#define MODEL_MEN_H_

namespace draughts {
namespace model {

class Men:public Piece{
public:
	Men(direction, PieceType, int, int);
	virtual bool validMove(PieceType, int, int) override;
	virtual bool validJump(PieceType, int, int) override;
	virtual ~Men();
};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_MEN_H_ */
