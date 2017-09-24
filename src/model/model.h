#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
//Used for formatting outputs
#include <iomanip>
//Used to get random numbers
#include <random>

#pragma once

namespace draughts
{
    namespace model
    {
        class model
        {
            static std::unique_ptr<model> instance;
            std::map<int, std::string> playerList;

           	int currentPlayer;

            std::pair<int, char> player1;
            std::pair<int, char> player2;

            std::vector<std::vector<char>> board;

            const int height = 8;
            const int width = 8;

            model(void);
            bool player_exists(const std::string&);


            public:
            void start_game(int, int);
            char get_token(int,int);
            void make_move(int, int, int, int, int);

            bool possibleJumps(void);
            bool possibleMoves(void);

            void add_player(const std::string& );
            int get_player_score(int);
            int get_current_player(void);
            //Check which type of token the user was assigned
            char get_player_token(int);
            //To swap players when a turn is over
            void swap_players(void);
            std::string get_player_name(int);
            std::map<int, std::string> get_player_list(void) const;
            int get_winner();
            int get_width();
            int get_height();
            static model * get_instance(void);
            static void delete_instance(void);
            virtual ~model(void);
        };
    }
}
