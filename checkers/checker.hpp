//
//  checker.hpp
//  checkers
//
//  Created by Tommy Smale on 11/30/21.
//

#ifndef checker_hpp
#define checker_hpp

#include <stdio.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "board.hpp"
#include <math.h> 
using namespace std;

static const GLfloat pi = 3.14f; //Maybe make this a macro 

struct Checker: protected Board {
    Checker();
    void set_checker(GLfloat, GLfloat, int); 
    void move_piece(int, int);
    void color(GLfloat, GLfloat, GLfloat); 
    GLfloat radius; 
    vector<GLfloat> vertices;
    vector<GLfloat> colors; 
    int square;
    bool capture;
    bool king;
};
#endif /* checker_hpp */
