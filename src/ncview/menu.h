#include "window.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

#pragma once

namespace draughts
{
    namespace ncview
    {
    	//menu class (child) derived from window class (parent)
        class menu : public window
        {
        	//Title of menu
            std::string title;
            //The commands available in text
            std::vector<std::string> menu_text;
            //Vector of menu commands
            command_vector menu_commands;
            public:
            	//menu constructor passes string references for memory efficiency
                menu(const std::string&, const std::vector<std::string>&, 
                    command_vector);
                menu(void);
                void set_title(const std::string&);
                void set_text(const std::vector<std::string>&);
                void set_actions(command_vector&);
                virtual void activate(void) override;
                virtual ~menu(void){}
        };
    }
}
