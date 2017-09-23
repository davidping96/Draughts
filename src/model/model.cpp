#include "model.h"

std::unique_ptr<draughts::model::model> draughts::model::model::instance =
		nullptr;

draughts::model::model::model(void) {
}

draughts::model::model * draughts::model::model::get_instance(void) {
	if (instance == nullptr) {
		instance = std::unique_ptr<model>(new model);
	}
	return instance.get();
}

int draughts::model::model::get_player_score(int playernum) {
	return EOF;
}

void draughts::model::model::start_game(int plr1, int plr2) {
	//randomly assign a color to the two players
	//setup the board and assign pieces to them
	//the pieces should have a color
}

int draughts::model::model::get_winner() {
	return EOF;
}

std::string draughts::model::model::get_player_name(int id) {
	for(std::map<int, std::string>::iterator it = playerList.begin();it!=playerList.end();++it){
		if(it->first==id){
			return it->second;
		}
	}
	return "";
}

char draughts::model::model::get_token(int x, int y) {
	return '\0';
}

void draughts::model::model::make_move(int playernum, int startx, int starty,
		int endx, int endy) {
}

void draughts::model::model::add_player(const std::string& p) {
	int count = 1;
	while (1) {
		if (playerList[count] == "") {
			playerList[count] = p;
			break;
		}
		count++;
	}
	std::cout<<"ID "<<std::setw(20)<<"Name "<<std::endl;
	std::cout<<"----------------------------------------"<<std::endl;
	for(std::map<int, std::string>::iterator it = playerList.begin();it!=playerList.end();++it){
		std::cout<<it->first<<std::setw(20)<<it->second<<std::endl;
	}
	std::cout<<"----------------------------------------"<<std::endl;
}

bool draughts::model::model::player_exists(const std::string& pname) {
	for(std::map<int, std::string>::iterator it = playerList.begin();it!=playerList.end();++it){
		if(it->second==pname){
			return true;
		}
	}
	return false;
}

int draughts::model::model::get_current_player(void) {
	return EOF;
}

std::map<int, std::string> draughts::model::model::get_player_list(void) const {
	return playerList;
}

void draughts::model::model::delete_instance(void) {
	instance.reset(nullptr);
}

int draughts::model::model::get_width() {
	return EOF;
}

int draughts::model::model::get_height() {
	return EOF;
}

draughts::model::model::~model(void) {
}

