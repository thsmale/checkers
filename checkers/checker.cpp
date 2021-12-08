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
    alive = true; 
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

//Move the selected checker to the desired square
//Next need to check if it takes out any pieces along the way
void Checker::move_checker(pair<GLfloat, GLfloat> center, int square) {
    if (square < 0 || square > (num_squares()-1)) {
        cerr << "Cannot move checker to that square " << endl;
        exit(1);
    }
    GLfloat x = center.first;
    GLfloat y = center.second;
    vertices.clear();
    colors.clear(); 
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

void Checker::color(GLfloat r, GLfloat g, GLfloat b) {
    if(colors[0] == r && colors[1] == g && colors[2] == b)
        return;
    for(int i = 0; i < colors.size(); i+=3) {
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
    }
}
    
void Checker::eat_checker() {
    vertices.clear();
    colors.clear();
    alive = false;
    square = -1;
    king = false; 
}
    
