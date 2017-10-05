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
			display_current_player();
			do {
				//Get user input for next move
				move_coords = get_move_input();

				//Check if jumps are possible
				if (gameInstance->getCurrentPlayer()->possibleJumps()) {
					//If true then ensure move input is a valid jump
					if (boardInstance->getInstance()->getCells().at(
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

			//If a valid jump was made and the piece moved was not kinged
			if (valid_jump && !kinged) {
				try_more_jumps(move_coords.second.first,
						move_coords.second.second);
			}
			//Swap current player
			gameInstance->swapPlayers();
			if (gameInstance->checkGameOver()) {
				quit = true;
			}
		} catch (std::invalid_argument &e) {
			std::cerr << e.what() << std::endl;
		} catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
	display_winner(gameInstance->getWinner());
}

std::pair<std::pair<int, int>, std::pair<int, int>> draughts::ncview::game_window::get_move_input(
		void) {
	std::string input;
	std::pair<std::pair<int, int>, std::pair<int, int>> move;
	std::vector<std::string> moves;
	std::pair<int, int> start;
	std::pair<int, int> end;
	//bool validInput = false;

	//do {
	try {
		std::cout << "Please enter your next move (x1,y1 - x2,y2): "
				<< std::endl;
		std::getline(std::cin, input);
		boost::split(moves, input, [](char ch) {return ch == '-';});
		if(moves.size()!=2){
			throw std::invalid_argument("Invalid input format");
		}
		start = strtocoord(moves[0]);
		end = strtocoord(moves[1]);
		//validInput = true;
	} catch (std::invalid_argument &e) {
		throw e;
	} catch (std::exception &ex) {
		throw ex;
	}
	//} while (validInput == false);

	move = std::make_pair(start, end);
	return move;
}

std::pair<int, int> draughts::ncview::game_window::get_more_jumps(void) {
	std::string input;
	std::pair<int, int> move;
	int x, y;
	std::vector<std::string> parts;
	//bool validInput = false;

	//do {
	try {
		std::cout << "Please enter another jump (x,y): " << std::endl;
		std::getline(std::cin, input);
		boost::split(parts, input, [](char ch) {return ch == ',';});
		if (parts.size() != 2) {
			throw std::invalid_argument("Invalid coordinates format");
		}
		x = stoi(parts[0]);
		y = stoi(parts[1]);
		//validInput = true;
	} catch (std::invalid_argument &e) {
		throw e;
	} catch (std::exception &ex) {
		throw ex;
	}
	//} while (validInput == false);

	--x;
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
	try {
		boost::split(parts, input, [](char ch) {return ch == ',';});

		if (parts.size() != 2) {
			throw std::invalid_argument("Invalid coordinates");
		}
		x = stoi(parts[0]);
		y = stoi(parts[1]);
	} catch (std::invalid_argument &e) {
		throw e;
	} catch (std::exception &ex) {
		throw ex;
	}
	--x;
	--y;
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

void draughts::ncview::game_window::display_current_player(void) {
	std::unique_ptr<draughts::model::Game> game;

	std::cout << game->getInstance()->getCurrentPlayer()->getPlayerName()
			<< "'s turn " << std::endl;
	char c =
			PieceType::CROSS
					== game->getInstance()->getCurrentPlayer()->getPieceType() ?
					'x' : 'o';
	std::cout << "Token: (" << c << ")" << std::endl;
	std::cout << "Score: "
			<< game->getInstance()->getCurrentPlayer()->getPlayerScore()
			<< std::endl;
}

void draughts::ncview::game_window::display_winner(int playernum) {
	std::unique_ptr<draughts::model::Game> game;
	if (playernum != game->getInstance()->getCurrentPlayer()->getPlayerNum()) {
		game->getInstance()->swapPlayers();
	}
	if(playernum != -1){
	std::cout << "Winner: "
			<< game->getInstance()->getCurrentPlayer()->getPlayerName()
			<< std::endl;
	std::cout << "Score: "
			<< game->getInstance()->getCurrentPlayer()->getPlayerScore()
			<< std::endl;
	}else{
		std::cout<<"Game ends in a draw"<<std::endl;
	}
}

void draughts::ncview::game_window::try_more_jumps(int endx, int endy) {
	std::unique_ptr<draughts::model::Board> board;
	std::unique_ptr<draughts::model::Game> game;
	int startx = endx;
	int starty = endy;
	bool kinged = false;

	//While the current player can make more jumps and the piece has not been kinged jump again
	while (game->getInstance()->getCurrentPlayer()->moreJumps(startx, starty)
			&& !kinged) {
		try {
			std::cout << "Make another jump from " << startx + 1 << ","
					<< starty + 1 << std::endl;
			display_board();
			std::pair<int, int> jump_coords;
			//Get more user input
			jump_coords = get_more_jumps();
			//If it is valid input
			if (board->getInstance()->getInstance()->getCells().at(startx).at(
					starty)->validJump(
					game->getInstance()->getCurrentPlayer()->getPieceType(),
					jump_coords.first, jump_coords.second)) {
				//If the end is a kingsrow for the piece then king then break the loop
				kinged = board->getInstance()->pieceKinged(startx, starty,
						jump_coords.first);
				//Make the jump
				game->getInstance()->getCurrentPlayer()->makeMove(startx,
						starty, jump_coords.first, jump_coords.second);

				startx = jump_coords.first;
				starty = jump_coords.second;
			} else {
				std::cout << "Invalid input, must make a valid jump"
						<< std::endl;
			}
		} catch (std::invalid_argument &e) {
			std::cerr << e.what() << std::endl;
		} catch (std::exception &ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
}
