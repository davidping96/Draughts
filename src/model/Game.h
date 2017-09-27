/*
 * File name: Game.h
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include <memory>
#include <locale>
#include "Board.h"
#include "Player.h"

#ifndef MODEL_GAME_H_
#define MODEL_GAME_H_

namespace draughts {
namespace model {

class Game {

	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	std::unique_ptr<Board> board;
	int currentPlayer;
	int winner;
public:
	Game(int, std::string, int, std::string);
	virtual ~Game();

	int getCurrentPlayer();
	void swapPlayers();
	int getWinner();
	bool possibleJumps();
	bool validJump(int playernum, int startx, int starty, int endx, int endy);
	bool possibleMoves();
	bool validMove(int playernum, int startx, int starty, int endx, int endy);
	void make_move(int playernum, int startx, int starty, int endx, int endy);
	bool moreJumps(int playernum, int startx, int starty);
	char getPlayerToken(int);
	std::string getPlayerName(int);
	int getPlayerScore(int);
	Board * getBoard();
};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_GAME_H_ */
