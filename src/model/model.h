#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <iomanip>
#include <map>
#include <string>

#include "Game.h"
#include "Player.h"

#pragma once

namespace draughts
{
    namespace model
    {
        class model
        {
        	model(void);
            static std::unique_ptr<model> instance;
            std::map<int, std::string> playerList;
            bool player_exists(const std::string&);

            public:
            void start_game(int, std::string, int, std::string);
            void add_player(const std::string& );
            std::map<int, std::string> get_player_list(void) const;
            static model * get_instance(void);
            static void delete_instance(void);
            virtual ~model(void);
        };
    }
}
