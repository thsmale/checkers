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

#define NUM_CHECKERS 12

//0 is human 1 is opponent (computer) 
class Player: public Board {
public:
    Player(int);
    void set_checkers();
    void select_square(double, double);
    void print_checker_squares(); 
    vector<GLfloat> get_checker_vertices();
    vector<GLfloat> get_checker_colors();
    int get_selected_checker_square();
private:
    Checker checkers[NUM_CHECKERS];
    int type;
    int selected_checker; 
    GLfloat x;
    GLfloat y;
};

extern Player human; 
#endif /* player_hpp */
