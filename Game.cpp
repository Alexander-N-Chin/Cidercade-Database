/****************************************************************************************************************

Alexander N. Chin | NetID: ANC200008
CS 2337.002 Jason Smith
Project 3 ""Cidercade database" Final Submission
11/6/2021

*****************************************************************************************************************/

#include "Game.h"
//default constructor
Game::Game (std::string _name, std::string _high_score, std::string _initials, int _plays) {
    name = _name;
    high_score = _high_score;
    initials = _initials;
    plays = _plays;
}

//display formatted based on project directions
std::ostream& operator<< (std::ostream& out, const Game& _game) {
  out << std::fixed << std::setprecision(2);
  int highscore = stoi(_game.high_score);
  out << _game.name << ", " << highscore << ", " << _game.initials << ", " << _game.plays << ", $" << _game.plays * COST_PER_PLAY;
  return out;
}

//overloaded relational operators
bool Game::operator< (Game& _game) {
  return (this->name < _game.name)?true:false;
}
bool Game::operator> (Game& _game) {
  return (this->name > _game.name)?true:false;
}
bool Game::operator== (Game& _game) {
  return (_game.name.find(name) != std::string::npos)?true:false;
}
