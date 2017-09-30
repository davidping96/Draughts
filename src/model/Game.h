/*
 * File name: Game.h
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include <memory>
#include <locale>
#include <random>
#include <chrono>
#include "Board.h"
#include "Player.h"
#include "../PieceType.h"

#ifndef MODEL_GAME_H_
#define MODEL_GAME_H_

namespace draughts {
namespace model {

class Game {
	Game();
	static std::unique_ptr<Game> instance;
	Player * currentPlayer;
	std::unique_ptr<Player> player1;
	std::unique_ptr<Player> player2;
	int winner;

public:
	virtual ~Game();

	Game * getInstance();
	void deleteInstance();

	void initGame(int, std::string, int, std::string);

	Player * getCurrentPlayer();
	void swapPlayers();
	int getWinner();
	void setWinner(int);
};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_GAME_H_ */
