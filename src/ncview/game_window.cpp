#include "game_window.h"
#include "../model/model.h"
#include "../model/Game.h"
#include "../model/Board.h"

draughts::ncview::game_window::game_window(const player_pair & theplayers) :
		players(theplayers), quit(false) {
}

void draughts::ncview::game_window::activate(void) {
	std::unique_ptr<draughts::model::Board> board;
	std::unique_ptr<draughts::model::Game> game;
	std::unique_ptr<draughts::model::Board> boardInstance(board->getInstance());
	std::unique_ptr<draughts::model::Game> gameInstance(game->getInstance());
	boardInstance->initBoard();
	while (!quit) {
		bool valid_move = false;
		bool valid_jump = false;
		bool kinged = false;
		std::pair<std::pair<int, int>, std::pair<int, int>> move_coords;

		try {
			display_board();
			std::cout << gameInstance->getCurrentPlayer()->getPlayerName()
					<< "'s turn " << std::endl;
			char c =
					PieceType::CROSS
							== gameInstance->getCurrentPlayer()->getPieceType() ?
							'x' : 'o';
			std::cout << "Token: (" << c << ")" << std::endl;
			std::cout << "Score: "
					<< gameInstance->getCurrentPlayer()->getPlayerScore()
					<< std::endl;
		} catch (std::exception & ex) {
			std::cerr << ex.what() << std::endl;
		}
		try {
			/* If there are not more posssible moves or jumps for this player then end the game*/
			if (!gameInstance->getCurrentPlayer()->possibleJumps()
					&& !gameInstance->getCurrentPlayer()->possibleMoves()) {
				//Cannot make a move or a jump, have either lost or it might be a draw
				//Swap players to check, in either case make quit = true to break out
				gameInstance->swapPlayers();
				quit = true;
				if (gameInstance->getCurrentPlayer()->possibleMoves()
						|| gameInstance->getCurrentPlayer()->possibleJumps()) {
					gameInstance->setWinner(
							gameInstance->getCurrentPlayer()->getPlayerNum());
					std::cout << "Winner: "
							<< gameInstance->getCurrentPlayer()->getPlayerName()
							<< std::endl;
					break;
				} else {
					std::cout << "The game ends in a draw" << std::endl;
					break;
				}
			}

			do {
				//Get user input for next move
				move_coords = get_move_input();
				//Check if jumps are possible
				if (gameInstance->getCurrentPlayer()->possibleJumps()) {
					//If true then ensure move input is a valid jump
					if (boardInstance->getInstance()->getCells().at(
							move_coords.first.first).at(
							move_coords.first.second) != nullptr
							&& boardInstance->getInstance()->getCells().at(
									move_coords.first.first).at(
									move_coords.first.second)->validJump(
									gameInstance->getCurrentPlayer()->getPieceType(),
									move_coords.second.first,
									move_coords.second.second)) {
						//valid_input is true if it is
						valid_jump = true;
						//If a piece will be kinged upon jumping then do not try to make more jumps
						kinged = boardInstance->pieceKinged(
								move_coords.first.first,
								move_coords.first.second,
								move_coords.second.first);
					} else {
						std::cout << "Invalid input, must make a valid jump"
								<< std::endl;
					}
				} else {
					//Else if you cannot make a jump check if moves are possible
					if (gameInstance->getCurrentPlayer()->possibleMoves()) {
						//If true then ensure move input is a valid move
						if (boardInstance->getInstance()->getCells().at(
								move_coords.first.first).at(
								move_coords.first.second) != nullptr
								&& boardInstance->getInstance()->getCells().at(
										move_coords.first.first).at(
										move_coords.first.second)->validMove(
										gameInstance->getCurrentPlayer()->getPieceType(),
										move_coords.second.first,
										move_coords.second.second)) {
							//valid_input is true if it is
							valid_move = true;
						} else {
							std::cout << "Invalid input, must make a valid move"
									<< std::endl;
						}
					}
				}
			} while (!valid_move && !valid_jump);
			gameInstance->getCurrentPlayer()->makeMove(move_coords.first.first,
					move_coords.first.second, move_coords.second.first,
					move_coords.second.second);

			//If a valid jump was made
			if (valid_jump && !kinged) {
				int startx = move_coords.second.first;
				int starty = move_coords.second.second;
				//Make more jumps as long as it can
				while (gameInstance->getCurrentPlayer()->moreJumps(startx,
						starty) && !kinged) {
					std::cout << "Make another jump from " << startx + 1 << ","
							<< starty + 1 << std::endl;
					display_board();
					std::pair<int, int> jump_coords;
					//Get more user input
					jump_coords = get_more_jumps();
					//If it is valid input
					if (boardInstance->getInstance()->getCells().at(startx).at(
							starty) != nullptr
							&& boardInstance->getInstance()->getCells().at(
									startx).at(starty)->validJump(
									gameInstance->getCurrentPlayer()->getPieceType(),
									jump_coords.first, jump_coords.second)) {
						//If the end is a kingsrow for the piece then king then break the loop
						kinged = boardInstance->pieceKinged(startx, starty,
								jump_coords.first);
						//Make the jump
						gameInstance->getCurrentPlayer()->makeMove(startx,
								starty, jump_coords.first, jump_coords.second);

						startx = jump_coords.first;
						starty = jump_coords.second;
					} else {
						std::cout << "Invalid input, must make a valid jump"
								<< std::endl;
					}
				}
			}
			//Swap current player
			gameInstance->swapPlayers();
		} catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
	board->deleteInstance();
	game->deleteInstance();
}

std::pair<std::pair<int, int>, std::pair<int, int>> draughts::ncview::game_window::get_move_input(
		void) {
	std::string input;
	std::pair<std::pair<int, int>, std::pair<int, int>> move;
	std::pair<int, int> start;
	std::pair<int, int> end;
	std::cout << "Please enter your next move (x1,y1 - x2,y2): " << std::endl;

	/*Use regex to ensure user enters a valid input, repeat until valid*/
	std::regex reg("^[1-8],[\\s]?[1-8][\\s]?-[\\s]?[1-8],[\\s]?[1-8]$");
	do {
		std::getline(std::cin, input);
		if (!regex_match(input, reg)) {
			std::cerr << "Invalid input, please try again: " << std::endl;
		}
	} while (std::regex_match(input, reg) != 1);

	std::vector<std::string> moves;
	std::vector<std::string> coords;
	//Use lambda expression to split up the input
	boost::split(moves, input, [](char ch) {return ch == '-';});
	start = strtocoord(moves[0]);
	--start.first;
	--start.second;
	end = strtocoord(moves[1]);
	--end.first;
	--end.second;
	move = std::make_pair(start, end);
	return move;
}

std::pair<int, int> draughts::ncview::game_window::get_more_jumps(void) {
	std::string input;
	std::pair<int, int> move;
	std::cout << "Please enter another jump (x,y): " << std::endl;
	std::regex reg("^[1-8],[\\s]?[1-8]$");
	do {
		std::getline(std::cin, input);
		if (!regex_match(input, reg)) {
			std::cerr << "Invalid input, please try again: " << std::endl;
		}
	} while (std::regex_match(input, reg) != 1);
	int x, y;
	std::vector<std::string> parts;
	boost::split(parts, input, [](char ch) {return ch == ',';});
	x = stoi(parts[0]);
	--x;
	y = stoi(parts[1]);
	--y;
	move = std::make_pair(x, y);
	return move;
}

void draughts::ncview::game_window::print_top_row(void) {
	std::unique_ptr<draughts::model::Board> board;

	int xcount;
	std::cout << "   |";
	for (xcount = 0; xcount < board->getInstance()->getBoardLength();
			++xcount) {
		std::cout << " " << xcount + 1 << " |";
	}
	std::cout << std::endl;
}

std::pair<int, int> draughts::ncview::game_window::strtocoord(
		const std::string& input) {
	int x, y;
	std::vector<std::string> parts;
	boost::split(parts, input, [](char ch) {return ch == ',';});
	x = stoi(parts[0]);
	y = stoi(parts[1]);
	return std::make_pair(x, y);
}

void draughts::ncview::game_window::print_row(int rownum) {
	std::unique_ptr<draughts::model::Board> board;
	char c;
	int xcount;
	std::cout << " " << rownum + 1 << " |";
	for (xcount = 0; xcount < board->getInstance()->getBoardLength();
			++xcount) {
		c = ' ';
		if (board->getInstance()->getCells().at(rownum).at(xcount) != nullptr) {
			if (board->getInstance()->getPiece(rownum + 1, xcount + 1)->getPieceType()
					== PieceType::CROSS) {
				c = 'x';
			}
			if (board->getInstance()->getPiece(rownum + 1, xcount + 1)->getPieceType()
					== PieceType::CIRCLE) {
				c = 'o';
			}
			if (board->getInstance()->getPiece(rownum + 1, xcount + 1)->getDirection()
					== direction::BOTH) {
				c = std::toupper(c);
			}
		}

		std::cout << " " << c << " |";
	}
	std::cout << std::endl;
}

void draughts::ncview::game_window::print_line(int numdashes) {
	int count;
	for (count = 0; count < numdashes; ++count) {
		std::cout << '-';
	}
}

void draughts::ncview::game_window::display_board(void) {
	std::unique_ptr<draughts::model::Board> board;
	int ycount;

	std::cout << std::endl;
	print_top_row();
	print_line(board->getInstance()->getBoardLength() * 4 + 4);
	std::cout << std::endl;

	for (ycount = 0; ycount < board->getInstance()->getBoardLength();
			ycount++) {
		print_row(ycount);
		print_line(board->getInstance()->getBoardLength() * 4 + 4);
		std::cout << std::endl;
	}
}

