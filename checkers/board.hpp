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
#include "moves.hpp"
//#include "checker.hpp"
#include <utility>
#include <memory> 

using namespace std; 

//Could not for the life of me include Board because of glew.h header file 
#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

enum board_properties : char {
    blank = '_',
    player = 'x',
    computer = 'o',
    player_capital = 'X',
    computer_captial = 'O'
};

class Board {
public:
    Board();
    ~Board();
    void color_triangles();
    void color_squares();
    bool color_triangle(int);
    bool color_square(int);
    void color_possible_moves(vector<pair<int, int> >);
    //Setters
    void set_board();
    void update_board(pair<int, int>, pair<int, int>, bool player); 
    void set_board_vertices();
    void set_elements();
    void set_color();
    void set_color(GLfloat, GLfloat, GLfloat);
    //Getters
    int get_size();
    vector<vector<char> > get_board(); 
    GLfloat* get_board_vertices();
    GLfloat* get_colors();
    int get_board_vertices_size();
    int get_colors_size();
    int num_vertices();
    int num_triangles();
    int num_squares();
    int num_diagonals();
    int get_square(GLfloat, GLfloat);
    int get_square(double, double);
    int get_square(std::pair<int, int>);
    std::pair<int, int> get_coordinates(int);
    std::pair<GLfloat, GLfloat> get_center(int); 
    bool valid_move(int, bool, bool);
    bool player(int);
    //Print functions
    void print_board(); 
    void print_board_vertices();
    void print_triangles();
    void print_board_vertices_x_y();
    void print_colors();
protected:
    GLfloat width;
private:
    const int size;
    int board_vertices_size;
    int colors_size;
    static std::vector<std::vector<char> > board;
    GLfloat *board_vertices;
    GLfloat *colors;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};

#endif /* board_hpp */
