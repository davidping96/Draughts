/*
 * File name: Board.h
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include <vector>
#include <memory>
#include "Piece.h"

#ifndef MODEL_BOARD_H_
#define MODEL_BOARD_H_

namespace draughts {
namespace model {

class Board {
	Board();
	static std::unique_ptr<Board> instance;
	std::vector<std::vector<std::unique_ptr<Piece>>> cells;
	const int boardLength = 8;

public:
	virtual ~Board();

	Board * getInstance();
	void deleteInstance();

	std::vector<std::vector<std::unique_ptr<Piece>>> & getCells();
	Piece * getPiece(int x, int y);
	int getBoardLength();
	void setPiece(int x, int y, std::unique_ptr<Piece>);
	bool pieceKinged(int, int, int);
	void initBoard();

};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_BOARD_H_ */
