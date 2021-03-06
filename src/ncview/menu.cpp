#include "menu.h"
#include "../nc_controller/command.h"

//Menu constructor
draughts::ncview::menu::menu(const std::string & thetitle,
		const std::vector<std::string>& text,
		draughts::ncview::command_vector commands) :
		title(thetitle), menu_text(text), menu_commands(std::move(commands)) {
}

//Opens the menu and requests user input
void draughts::ncview::menu::activate(void) {
	std::cout << title << std::endl;
	std::string underline(title.size(), '-');
	std::cout << underline << std::endl;
	int count;
	std::size_t end;
	int choice;

	std::string line;
	bool success = false;
	for (count = 0; count < static_cast<int>(menu_text.size()); ++count) {
		std::cout << count + 1 << ") " << menu_text[count] << std::endl;
	}
	while (!success) {
		try {
			std::cout << "Please enter your choice: " << std::endl;
			std::getline(std::cin, line);
			choice = std::stoi(line, &end);
			if (end != line.size() || choice <= 0
					|| choice > static_cast<int>(menu_text.size())) {
				std::cerr << "error: invalid input. Please try again."
						<< std::endl;
			} else {
				success = true;
			}
		} catch (std::exception& ex) {
			std::cout << "Exception: " << ex.what() << std::endl;
			std::cerr << "error: invalid input. Please try again." << std::endl;
			/* if the user pressed ctrl-d, we have to remove the
			 * buffer input
			 */
			if (std::cin.eof()) {
				std::cin.clear();
			}
		}
	}
	/*This is the same as below
	 command & comm = *menu_command[choice-1]
	 comm();*/

	//Command pattern
	//each window has a vector of commands/observers
	//menu_commands is a pointer to the vector of commands so first dereference it
	(*(menu_commands[choice - 1]))();
}

draughts::ncview::menu::menu(void) {
}

void draughts::ncview::menu::set_title(const std::string& newtitle) {
	title = newtitle;
}

void draughts::ncview::menu::set_text(const std::vector<std::string>& newtext) {
	menu_text = newtext;
}

void draughts::ncview::menu::set_actions(command_vector& vec) {
	menu_commands = std::move(vec);
}

