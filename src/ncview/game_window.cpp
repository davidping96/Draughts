#include "game_window.h"
#include "../model/model.h"

draughts::ncview::game_window::game_window(const player_pair & theplayers) :
		players(theplayers), quit(false) {
}

void draughts::ncview::game_window::activate(void) {
	std::unique_ptr<draughts::model::Game> game_instance(themodel->get_instance()->getGameInstance());
	while (!quit) {
		int playernum = EOF;
		try {
			display_board();
			playernum = game_instance->getCurrentPlayer();
			std::cout << game_instance->getPlayerName(playernum)<< "'s turn " <<std::endl;
			std::cout<<"Token: (" << game_instance->getPlayerToken(playernum) << ")"<< std::endl;
			std::cout << "Score: "<< game_instance->getPlayerScore(playernum) << std::endl;
		} catch (std::exception & ex) {
			std::cerr << ex.what() << std::endl;
			return;
		}
		try {
			std::pair<std::pair<int, int>, std::pair<int, int>> move_coords;
			bool valid_move = false;
			bool valid_jump = false;
			bool kinged = false;

			do {
				//Get user input for next move
				move_coords = get_move_input();

				//Check if jumps are possible
				if (game_instance->possibleJumps()) {
					//If true then ensure move input is a valid jump
					if (game_instance->validJump(playernum,
							move_coords.first.first - 1,
							move_coords.first.second - 1,
							move_coords.second.first - 1,
							move_coords.second.second - 1)) {
						//valid_input is true if it is
						valid_jump = true;
						//If a piece will be kinged upon jumping then do not try to make more jumps
						//If the start position is a normal piece
						//and the end position is the kingsrow
						if(game_instance->getBoard()->getToken(move_coords.first.first, move_coords.first.second)==game_instance->getPlayerToken(playernum)){
							if(game_instance->getBoard()->getToken(move_coords.first.first, move_coords.first.second)=='x' &&
									move_coords.first.first==0){
								kinged = true;
							}else if(game_instance->getBoard()->getToken(move_coords.first.first, move_coords.first.second)=='o' &&
									move_coords.first.first==game_instance->getBoard()->getHeight()-1){
								kinged = true;
							}
						}
					} else {
						std::cout << "Invalid input, must make a valid jump"
								<< std::endl;
					}
				} else {
					//Else if you cannot make a jump check if moves are possible
					if (game_instance->possibleMoves()) {
						//If true then ensure move input is a valid move
						if (game_instance->validMove(playernum,
								move_coords.first.first - 1,
								move_coords.first.second - 1,
								move_coords.second.first - 1,
								move_coords.second.second - 1)) {
							//valid_input is true if it is
							valid_move = true;
						} else {
							std::cout << "Invalid input, must make a valid move"
									<< std::endl;
						}
					} else {
						//Cannot make a move, have either lost or it might be a draw
						//Swap players to check, in either case make quit = true to break out
						//Assign the winner
					}
				}
			} while (!valid_move && !valid_jump);

			game_instance->make_move(playernum, move_coords.first.first - 1,
					move_coords.first.second - 1, move_coords.second.first - 1,
					move_coords.second.second - 1);

			//If a valid jump was made
			if (valid_jump && !kinged) {
				std::cout<<"Jump made"<<std::endl;
				int endx = move_coords.second.first-1;
				int endy = move_coords.second.second-1;
				//Make more jumps as long as it can
				while (game_instance->moreJumps(playernum, endx, endy)) {
					std::cout<<"More jumps must be made"<<std::endl;
					display_board();
					std::pair<int, int> jump_coords;
					//Get more user input
					jump_coords = get_more_jumps();
					//If it is valid input
					if (game_instance->validJump(playernum, endx, endy,
							jump_coords.first-1, jump_coords.second-1)) {
						//Make the jump
						game_instance->make_move(playernum, endx, endy,
								jump_coords.first-1, jump_coords.second-1);
						endx = jump_coords.first-1;
						endy = jump_coords.second-1;
					} else {
						std::cout << "Invalid input, must make a valid jump"
								<< std::endl;
					}
				}
			}
			game_instance->swapPlayers();

		} catch (std::exception& ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
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
	end = strtocoord(moves[1]);
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
	y = stoi(parts[1]);
	move = std::make_pair(x, y);
	return move;
}

void draughts::ncview::game_window::print_top_row(void) {
	int xcount;
	std::cout << "   |";
	for (xcount = 0; xcount < themodel->get_instance()->getGameInstance()->getBoard()->getWidth(); ++xcount) {
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
	int xcount;
	std::cout << " " << rownum + 1 << " |";
	for (xcount = 0; xcount < themodel->get_instance()->getGameInstance()->getBoard()->getWidth(); ++xcount) {
		std::cout << " "
				<< themodel->get_instance()->getGameInstance()->getBoard()->getToken(rownum + 1, xcount + 1)
				<< " |";
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
	int ycount;

	std::cout << std::endl;
	print_top_row();
	print_line(themodel->get_instance()->getGameInstance()->getBoard()->getWidth() * 4 + 4);
	std::cout << std::endl;

	for (ycount = 0; ycount < themodel->get_instance()->getGameInstance()->getBoard()->getHeight();
			ycount++) {
		print_row(ycount);
		print_line(themodel->get_instance()->getGameInstance()->getBoard()->getWidth() * 4 + 4);
		std::cout << std::endl;
	}
}

