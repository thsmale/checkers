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


class Board {
public:
    Board();
    ~Board();
    //I would like API so I can pass in a pattern, specifies how shapes are drawn 
    //Binary classification
    //  This will color using opposite color
    //  Can function overload to choose opposite color
    //  Uniform color 
    void color_scrooges();
    void color_triangles();
    void color_squares();
    void color_columns();
    void color_rows();
    void color_diagonals();
    void color_rhombus(); //TODO: implement rhombus
    void draw_two_triangles();
    void draw_staircase();
    //Every shape gets uniform own color
    //  Randomly chosen
    //  Note not checked to see if every color generated is unique 
    void random_color_triangles();
    void random_color_squares();
    void random_color_columns();
    void random_color_rows();
    void random_color_diagonals(); 
    //2/3 color rule
    //Allow pattern
    //Downshift diagonal
    //Specify row or column to color
    bool color_triangle(int);
    bool color_square(int);
    bool color_column(int);
    bool color_row(int); 
    bool what_is_this(int);
    bool color_diagonal(int); 
    
    //Setters
    void set_board();
    void set_elements();
    //Set a color theme? Neon, Pink etc
    void set_color();
    void set_color(string); 
    void set_color(GLfloat, GLfloat, GLfloat);
    //Getters
    GLfloat* get_board();
    GLuint* get_elements();
    GLfloat* get_colors();
    int get_board_size();
    int get_elements_size();
    int get_colors_size();
    int num_vertices();
    int num_elements();
    int num_triangles();
    int num_diagonals();
    bool is_boundary(int); 
    //Print functions
    void print_board();
    void print_triangles();
    void print_vertice_with_attributes(); 
    void print_board_x_y();
    void print_elements(); 
    void print_colors();

private:
    unsigned int size;
    unsigned int board_size;
    unsigned int elements_size;
    unsigned int colors_size;
    GLfloat *board;
    GLuint *elements; 
    GLfloat *colors;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};


#endif /* board_hpp */
