#include "window.h"
#include <map>
#include <string>
#include <utility>
#include <locale>
#include <boost/algorithm/string.hpp>
#include <regex>

namespace draughts
{
    namespace ncview
    {
        using view_player = std::pair<int, std::string>;
        using player_pair = std::pair<view_player, view_player>;
        class game_window : public window
        {
            player_pair players;
            bool quit;

            void print_top_row(void);
            void print_line(int);
            void print_row(int);
            std::pair<std::pair<int,int>, std::pair<int,int>> get_move_input(void);
            std::pair<int, int> get_more_jumps(void);
            std::pair<int, int> strtocoord(const std::string&);
            void try_more_jumps();
            
            public:
                game_window(const player_pair&);
                virtual void activate(void) override;
                void display_board(void);
                void display_current_player(void);
                void display_winner(int);
                void try_more_jumps(int, int);
                virtual ~game_window(void){}
        };
    }
}
