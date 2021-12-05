//
//  checker.cpp
//  checkers
//
//  Created by Tommy Smale on 11/30/21.
//

#include "checker.hpp"

Checker::Checker() {
    radius = width/2;
    square = 0; 
}

void Checker::set_checker(GLfloat x, GLfloat y, int square) {
    GLfloat radians = 0.f;
    GLfloat prev = 2*pi;
    int triangles = 0;
    //Vertices
    for(int degree = 15; degree <= 360; degree+=15) {
        triangles++;
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(radius*cos(prev)+x);
        vertices.push_back(radius*sin(prev)+y);
        radians = (degree * pi) / 180.0;
        vertices.push_back(radius*cos(radians)+x);
        vertices.push_back(radius*sin(radians)+y);
        prev = radians;
    }
    //Colors
    for(int i = 0; i < (triangles*9); i+=3) {
        colors.push_back(0.0f);
        colors.push_back(0.0f);
        colors.push_back(1.0f);
    }
    this->square = square; 
}

void Checker::move_piece(int square, int piece) {
    //radius*=square
    for(int i = 0; i < vertices.size(); i++) {
        if(i % 2 == 0)
            vertices[i] += radius;
    }
}

void Checker::color(GLfloat r, GLfloat g, GLfloat b) {
    if(colors[0] == r && colors[1] == g && colors[2] == b)
        return;
    for(int i = 0; i < colors.size(); i+=3) {
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
    }
}
    
    
