/*
 * File name: Board.h
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include <vector>

#ifndef MODEL_BOARD_H_
#define MODEL_BOARD_H_

namespace draughts {
namespace model {

class Board {
	std::vector<std::vector<char>> cells;
	int width = 8;
	int height = 8;

public:
	Board();
	virtual ~Board();
	int getHeight();
	int getWidth();
	char getToken(int x, int y);
	void setToken(int x, int y, char c);
	std::vector<std::vector<char>> getCells();
	void initBoard();
};

} /* namespace model */
} /* namespace draughts */

#endif /* MODEL_BOARD_H_ */
