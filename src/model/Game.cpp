/*
 * File name: Game.cpp
 * Created on: 26 Sep. 2017
 * Author: David Ping
 */

#include "Game.h"

namespace draughts {
namespace model {

std::unique_ptr<draughts::model::Game> draughts::model::Game::instance = nullptr;

Game::Game():currentPlayer(nullptr), player1(nullptr), player2(nullptr), winner(-1){

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

Game * draughts::model::Game::getInstance() {
	if (instance == nullptr) {
		instance = std::unique_ptr<Game>(new Game);
	}
	return instance.get();
}

void draughts::model::Game::deleteInstance() {
	instance.reset(nullptr);
}

void draughts::model::Game::initGame(int pnum1, std::string pname1, int pnum2, std::string pname2){
	getInstance();
	//Create player 1 and player 2
	player1 = std::make_unique<Player>(pnum1, pname1, PieceType::CROSS);
	player2 = std::make_unique<Player>(pnum2, pname2, PieceType::CIRCLE);
	//Pick the player that will go first
	auto duration = std::chrono::system_clock::now().time_since_epoch();
		//seed with number of milliseconds since the unix epoch began
		long millis = std::chrono::duration_cast<std::chrono::milliseconds>(
				duration).count();
		std::mt19937 gen(millis);
		//set the range for the generator - in this case between 0 and 1 inclusive
		std::uniform_int_distribution<unsigned> dist(0, 1);
		int rand = dist(gen);

		//set the player to make the first move using the random generator
		if (rand == 0) {
			currentPlayer = player1.get();
		} else {
			currentPlayer = player2.get();
		}
}

Player * draughts::model::Game::getCurrentPlayer(){
	return currentPlayer;
}

void draughts::model::Game::swapPlayers(){
	if(currentPlayer->getPlayerNum()==player1->getPlayerNum()){
		currentPlayer=player2.get();
	}else{
		currentPlayer=player1.get();
	}
}

int draughts::model::Game::getWinner(){
	return winner;
}

void draughts::model::Game::setWinner(int playernum){
	winner = playernum;
}

} /* namespace model */
} /* namespace draughts */
