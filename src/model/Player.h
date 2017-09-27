/*
 * File name: Player.h
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include <string>

#ifndef MODEL_PLAYER_H_
#define MODEL_PLAYER_H_

namespace draughts {
namespace model {

class Player {
	int id;
	std::string name;
	int score;
	char tokenType;
public:
	Player(int, std::string, char);
	virtual ~Player();
	void makeMove(int, int, int, int, int);
	std::string getPlayerName();
	int getPlayerNum();
	int getPlayerScore();
	char getTokenType();
};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_PLAYER_H_ */
