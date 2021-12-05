//
//  board.hpp
//  cops_robbers
//
//  Created by Tommy Smale on 11/15/21.
//

#ifndef board_hpp
#define board_hpp

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <map>
#include <vector>
#include <time.h>


using namespace std; 

//Could not for the life of me include Board because of glew.h header file 
#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

class Board {
public:
    Board();
    ~Board();
    void color_triangles();
    void color_squares();
    bool color_triangle(int);
    bool color_square(int);
    //Setters
    void set_board();
    void set_elements();
    void set_color();
    void set_color(GLfloat, GLfloat, GLfloat);
    //Getters
    int get_size(); 
    GLfloat* get_board();
    GLfloat* get_colors();
    int get_board_size();
    int get_colors_size();
    int num_vertices();
    int num_triangles();
    int num_squares();
    int num_diagonals();
    int get_square(GLfloat, GLfloat);
    int get_square(double, double); 
    //Print functions
    void print_board();
    void print_triangles();
    void print_board_x_y();
    void print_colors();
protected:
    GLfloat width;
private:
    const int size;
    int board_size;
    int colors_size;
    GLfloat *board;
    GLfloat *colors;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};


#endif /* board_hpp */
