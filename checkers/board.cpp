//
//  board.cpp
//  cops_robbers
//
//  Created by Tommy Smale on 11/15/21.
//

#include "board.hpp"

Board::Board() : size(8) {
    this->board_size = (size*size) * 6 * 2;
    this->colors_size = (size*size) * 6 * 3;
    this->board = new GLfloat[board_size];
    this->colors = new GLfloat[colors_size];
    this->width = 1.0 / (size / 2.0);
    GLfloat width = 1.0 / (size / 2.0);
    
    //Initialize board 
    GLfloat height = width;
    GLfloat x = -1.0f;
    GLfloat y = 1.0f;
    //Set top triangles
    int i = 0;
    for(int rows = 0; rows < size; rows++) {
        for(int cols = 0; cols < size; cols++) {
            board[i] = x;
            board[i+1] = y;
            x += width;
            board[i+2] = x;
            board[i+3] = y;
            board[i+4] = x;
            board[i+5] = y-width;
            i += 6;
        }
        x = -1.0f; //Reset x to far left
        y = y-height; //Shift y down
    }
     
    //Set bottom triangles
    x = -1.0f;
    y = 1.0f;
    for(int rows = 0; rows < size; rows++) {
        for(int cols = 0; cols < size; cols++) {
            //Top left
            board[i] = x;
            board[i+1] = y;
            //Bottom left
            board[i+2] = x;
            board[i+3] = y-width;
            //Bottom right
            x += width;
            board[i+4] = x;
            board[i+5] = y-width;
            i += 6;
        }
        x = -1.0f; //Reset x to far left
        y = y-height; //Shift y down
    }
    
    //Initialize colors
    for(int i = 0; i < colors_size; ++i)
        colors[i] = 0.0f;
    
    red = 1.0f;
    green = 1.0f;
    blue = 1.0f;
}

//Do I need to delete every element in the array?
Board::~Board() {
    delete [] board;
    delete [] colors;
}

//MARK: Coloring
void Board::color_triangles() {
    //Initialize elements
    int i = 0;
    GLfloat r = red;
    GLfloat g = green;
    GLfloat b = blue;
    while(i < colors_size) {
        if(i == colors_size/2) {
            GLfloat temp = r;
            r = g;
            g = temp;
        }
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
        i += 3;
    }
}


//Color squares 2 different colors
void Board::color_squares() {
    GLfloat temp = .0f;
    for(int square = 0; square < num_squares(); ++square) {
        if(square % size != 0) {
            temp = red;
            if(red == 0.0f) {
                temp = 1.0f;
            }else {
                temp = 0.0f;
            }
            red = temp;
            green = temp;
            blue = temp;
        }
        if(square % 2 == 0) {
            color_square(square);
        }else {
            color_square(square);
        }
    }
}

bool Board::color_triangle(int triangle) {
    if(triangle > num_triangles()) {
        cerr << "Triangle does not exist" << endl;
        return false;
    }
    int i = triangle*9;
    int end = i + 9; 
    while(i < end) {
        colors[i] = red;
        colors[i+1] = green;
        colors[i+2] = blue;
        i+=3;
    }
    return true;
}

bool Board::color_square(int square) {
    if(square > (size*size)) {
        cerr << "Square does not exist" << endl;
        return false;
    }
    color_triangle(square);
    color_triangle(square+(num_triangles()/2));
    return true; 
}


//MARK: Setters
//Space is -1, 1 with center being 0, 0
//Need each triangle to have unique points
//So it can have it's own attributes
//Width will be maximumn number of squares we can fit in the space given the size
void Board::set_board() {
    GLfloat width = 1.0 / (size / 2.0);
    GLfloat height = width;
    GLfloat x = -1.0f;
    GLfloat y = 1.0f;
    //Set top triangles
    int i = 0;
    for(int rows = 0; rows < size; rows++) {
        for(int cols = 0; cols < size; cols++) {
            board[i] = x;
            board[i+1] = y;
            x += width;
            board[i+2] = x;
            board[i+3] = y;
            board[i+4] = x;
            board[i+5] = y-width;
            i += 6;
        }
        x = -1.0f; //Reset x to far left
        y = y-height; //Shift y down
    }
    //Set bottom triangles
    x = -1.0f;
    y = 1.0f;
    for(int rows = 0; rows < size; rows++) {
        for(int cols = 0; cols < size; cols++) {
            //Top left
            board[i] = x;
            board[i+1] = y;
            //Bottom left
            board[i+2] = x;
            board[i+3] = y-width;
            //Bottom right
            x += width;
            board[i+4] = x;
            board[i+5] = y-width;
            i += 6;
        }
        x = -1.0f; //Reset x to far left
        y = y-height; //Shift y down
    }
}

//I should be wary of this implementation
//Numbers may not be uniformally distributed
//And the whole /RAND_MAX ish
//I also thought I would have to seed this
void Board::set_color() {
    red = (GLfloat) rand()/RAND_MAX;
    green = (GLfloat) rand()/RAND_MAX;
    blue = (GLfloat) rand()/RAND_MAX;
}

void Board::set_color(GLfloat r, GLfloat g, GLfloat b) {
    red = r;
    green = g;
    blue = b; 
}

//MARK: Getters
int Board::get_size() {
    return size;
}

GLfloat* Board::get_board() {
    return board;
}

GLfloat* Board::get_colors() {
    return colors;
}

int Board::get_board_size() {
    return board_size;
}

int Board::get_colors_size() {
    return colors_size;
}

int Board::get_square(GLfloat x, GLfloat y) {
    GLfloat xstart = -1.f, xend = -1.f;
    GLfloat ycieling = 1.f, yfloor = 1.f;
    for(int i = 0; i < num_squares(); ++i) {
        if(i % size == 0) {
            ycieling = yfloor;
            yfloor -= width;
            xstart = -1.f;
            xend = xstart + width;
        }
        if(xstart <= x && x < xend &&  y <= ycieling && y > yfloor) {
            return i;
        }
        xstart = xend;
        xend += width;
    }
    cout << x << " " << y << endl;
    //cout << xstart << " " << xend << " " << x << " " << ystart << " " << yend << " " << y << endl;
    exit(1);
    return -1;
}

//Based on Mouse coordinates
//Uses win/width and win_height instead of square_len
int Board::get_square(double x, double y) {
    int xpos = int(x);
    int ypos = int(y);
    int x_len = WIN_WIDTH/size;
    int y_len = WIN_HEIGHT/size;
    int xstart = 0, xend = 0;
    int ystart = 0, yend = 0;
    for(int i = 0; i < num_squares(); ++i) {
        if(i % size == 0) {
            ystart = yend;
            yend += y_len;
            xstart = 0;
            xend = x_len;
        }
        if(xstart <= xpos && xpos < xend && ystart <= ypos && ypos < yend) {
            return i;
        }
        xstart = xend;
        xend += x_len;
    }
    return -1;
}

int Board::num_vertices() {
    return board_size/2;
}

int Board::num_triangles() {
    return (size * size) * 2; 
}

int Board::num_squares() {
    return (size * size);
}

int Board::num_diagonals() {
    return (size * 2 - 1);
}

//MARK: Print functions
void Board::print_board() {
    for(int i = 0; i < board_size; ++i) {
        if((i % size) == 0)
            cout << endl;
        printf("%.2f ", board[i]);
    }
}

void Board::print_triangles() {
    int i = 0;
    for(int i = 0; i < board_size; i+=2) {
        if(i % 6 == 0)
            cout << endl;
        cout << "(" << board[i] << ", " << board[i+1] <<") ";
    }
    cout << endl;
}
void Board::print_colors() {
    for(int i = 0; i < colors_size; ++i) {
        if(i % 3 == 0) cout << endl;
        if(i % 9 == 0) cout << endl;
        cout << colors[i] << " "; 
    }
    cout << endl; 
}

void Board::print_board_x_y() {
    int i = 0;
    while(i < board_size) {
        if(i % 18 == 0) cout << endl;
        if(i % 6 == 0) {
            cout << endl;
        }
        printf("(%.2f, %.2f) ", board[i], board[i+1]);
        i += 2;
    }
    cout << endl;
}
