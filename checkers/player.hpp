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
    void move_checker(int checker, int square);
    void set_checkers();
    vector<GLfloat> get_checkers();
private:
    Checker checkers[NUM_CHECKERS];
    int type;
    GLfloat x;
    GLfloat y;
};

#endif /* player_hpp */
