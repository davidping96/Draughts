/*
 * File name: Player.h
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include <string>
#include <memory>
#include "Board.h"
#include "../PieceType.h"

#ifndef MODEL_PLAYER_H_
#define MODEL_PLAYER_H_

namespace draughts {
namespace model {

class Player {
	int playernum;
	std::string name;
	PieceType pieceType;
	int score;
public:
	Player(int, std::string, PieceType);
	virtual ~Player();

	int getPlayerNum();
	std::string getPlayerName();
	PieceType getPieceType();
	int getPlayerScore();

	void makeMove(int, int, int, int);
	bool possibleMoves();
	bool possibleJumps();
	bool moreJumps(int, int);
};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_PLAYER_H_ */
