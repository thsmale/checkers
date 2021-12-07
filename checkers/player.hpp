//
//  player.hpp
//  checkers
//
//  Created by Tommy Smale on 11/30/21.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>

#include "checker.hpp"
#include "board.hpp"
#include "additionalMoves.hpp"
#include "movesEvaluated.hpp"

#define NUM_CHECKERS 12
#define COMPUTER 0
//#define HUMAN_ID 1

class Player: public Board {
public:
    Player(int);
    void set_checkers();
    void set_turn(); 
    void update_checkers();
    void move_checker();
    void move_checker(int, int); 
    void select_square(double, double);
    void print_checker_squares(); 
    vector<GLfloat> get_checker_vertices();
    vector<GLfloat> get_checker_colors();
    int get_selected_checker_square();
    bool get_turn(); 
    void print_checker_vertices();
    vector<Checker*> get_checkers();
private:
    Checker checkers[NUM_CHECKERS];
    int type;
    bool turn; 
    int selected_checker; 
    GLfloat x;
    GLfloat y;
};

extern Player human;

#endif /* player_hpp */
