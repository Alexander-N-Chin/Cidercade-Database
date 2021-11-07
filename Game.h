/****************************************************************************************************************

Alexander N. Chin | NetID: ANC200008
CS 2337.002 Jason Smith
Project 3 ""Cidercade database" Final Submission
11/6/2021

*****************************************************************************************************************/

#include <string>
#include <iostream>
#include <iomanip>

#ifndef GAME_H
#define GAME_H

//global constant variable to store the cost per play
const double COST_PER_PLAY = 0.25;

class Game {
private:
    std::string name;
    std::string high_score;
    std::string initials;
    int plays;
public:
    //constructors
    Game() {name = ""; high_score = ""; initials = ""; plays = 0;}
    Game (std::string _name, std::string _high_score, std::string _initials, int _plays);

    //relational overloaded operators
    friend std::ostream& operator<< (std::ostream& out, const Game& _game);
    bool operator< (Game& _game);
    bool operator> (Game& _game);
    bool operator== (Game& _game);

    //accessors and mutators
    std::string getName() const {return name;}
    std::string getHigh_score() const {return high_score;}
    std::string getInitials() const {return initials;}
    int getPlays() const {return plays;}

    void setName (std::string _name) {name = _name;}
    void setHigh_score (std::string _high_score) {high_score = _high_score;}
    void setInitials (std::string _initials) {initials = _initials;}
    void setPlays (int _plays) {plays = _plays;}
};
#endif
