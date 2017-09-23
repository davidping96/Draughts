#include "menu.h"

#pragma once

namespace draughts
{
    namespace ncview
    {
    	//main_menu class (child) derived from menu class (parent)
        class main_menu : public menu
        {
        	//strings variable holds the menu text
            static const std::vector<std::string> strings;
            public:
            	//Declare the main_menu constructor
                main_menu(void);
                //Virtual destructor
                virtual ~main_menu(void);
        };
    }
}
