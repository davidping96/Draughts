#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
#include <regex>
#include <boost/algorithm/string.hpp>
//Used for formatting outputs
#include <iomanip>
//Used to get random numbers
#include <random>
#include <map>
#include "Game.h"
#include "Player.h"

#pragma once

namespace draughts
{
    namespace model
    {
        class model
        {
            static std::unique_ptr<model> instance;
            std::unique_ptr<Game> gameInstance = nullptr;
            std::map<int, std::string> playerList;

            model(void);
            bool player_exists(const std::string&);

            public:
            void start_game(int, int);
            void add_player(const std::string& );
            std::string getPlayerName(int playernum);
            Game * getGameInstance();
            std::map<int, std::string> get_player_list(void) const;


            static model * get_instance(void);
            static void delete_instance(void);
            virtual ~model(void);
        };
    }
}
