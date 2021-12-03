//
//  checker.cpp
//  checkers
//
//  Created by Tommy Smale on 11/30/21.
//

#include "checker.hpp"

Checker::Checker() {
    radius = width/2;
}

void Checker::set_checker(GLfloat x, GLfloat y) {
    GLfloat radians = 0.f;
    GLfloat prev = 2*pi;
    for(int i = 1; i <= 12; ++i) {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(radius*cos(prev)+x);
        vertices.push_back(radius*sin(prev)+y);
        radians = (i * pi) / 6;
        vertices.push_back(radius*cos(radians)+x);
        vertices.push_back(radius*sin(radians)+y);
        prev = radians;
    }
}

void Checker::move_piece(int square, int piece) {
    //radius*=square
    for(int i = 0; i < vertices.size(); i++) {
        if(i % 2 == 0)
            vertices[i] += radius;
    }
}
    
    
