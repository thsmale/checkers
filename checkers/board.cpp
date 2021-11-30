//
//  board.cpp
//  cops_robbers
//
//  Created by Tommy Smale on 11/15/21.
//

#include "board.hpp"

Board::Board() {
    this->size = 5;
    this->board_size = (size*size) * 6 * 2;
    this->elements_size =  pow(size, 2) * 6; 
    this->colors_size = (size*size) * 6 * 3;
    this->board = new GLfloat[board_size];
    this->elements = new GLuint[elements_size];
    this->colors = new GLfloat[colors_size];
    
    //Initialize board
    for(int i = 0; i < board_size; ++i)
        board[i] = 0.0f;
    
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
    delete [] elements;
    delete [] colors;
}

//MARK: Coloring
//Scrooges are vertices that are unique to the triangle
//They are not shared by any other triangle
//They are colored in green cause they hog all the money and do not share!!
void Board::color_scrooges() {
    //Get list of elements
    int vertices = pow((size+1), 2); 
    map<GLuint, int> elements_count;
    for(int i = 0; i < vertices; ++i)
        elements_count[i] = 0;
    
    for(int i = 0; i < elements_size; ++i)
        elements_count[elements[i]] += 1;
    
    vector<GLuint> scrooges;
    for (std::map<GLuint,int>::iterator it=elements_count.begin(); it!=elements_count.end(); ++it) {
        if(it->second <= 1)
            scrooges.push_back(it->first);
    }
    
    for(int i = 0; i < scrooges.size(); ++i)
        colors[scrooges[i]*3+1] = 1.0f;
    
    print_colors();
}

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

void Board::color_squares() {
    int triangles = 0;
    int i = 0;
    int end = 0;
    GLfloat r = red;
    GLfloat g = green;
    GLfloat b = blue;
    for(int triangle = 0; triangle < num_triangles(); ++triangle) {
        end = i + 9;
        //Need to change every row other wise it will look like color columns 
        if(triangle % size != 0) {
            GLfloat temp = g;
            g = b;
            b = temp;
        }
        while(i < end) {
            triangles = 0;
            colors[i] = r;
            colors[i+1] = g;
            colors[i+2] = b;
            i+=3;
        }

    }
}

void Board::color_columns() {
    int i = 0;
    GLfloat r = red;
    GLfloat g = green;
    GLfloat b = blue;
    while(i < colors_size) {
        if( i % 9 == 0) {
            GLfloat temp = r;
            r = b;
            b = temp;
        }
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
        i += 3;
    }
}

//Should have
//Color even rows one way
//Color odd rows another way
void Board::color_rows() {
    int triangles = 0;
    int i = 0;
    GLfloat r = red;
    GLfloat g = green;
    GLfloat b = blue;
    while(i < colors_size) {
        if(triangles == size) {
            GLfloat temp = g;
            g = b;
            b = temp;
            triangles = 0;
        }
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
        i+=3;
        if(i % 9 == 0) triangles++;
    }
}

void Board::color_diagonals() {
    int i = 0;
    GLfloat r = red;
    GLfloat g = green;
    GLfloat b = blue;
    int triangles = 0;
    int row = 0;
    if(size % 2 == 0) {
        while(i < colors_size) {
            if(i % 9 == 0) {
                //Switch colors every time
                //Except if new row and row != size
                if(triangles == size) {
                    row++;
                    triangles = 0;
                    if(row == size) {
                        GLfloat temp = r;
                        r = g;
                        g = temp;
                    }
                }else {
                    GLfloat temp = r;
                    r = g;
                    g = temp;
                }
                triangles++;
            }
            colors[i] = r;
            colors[i+1] = g;
            colors[i+2] = b;
            i += 3;
        }
    }else {
        while(i < colors_size) {
            if(i % 9 == 0) {
                if(triangles % 2 == 0) {
                    cout << triangles << endl;
                    r = 0.0f;
                    g = 1.0f;
                }else {
                    r = 1.0f;
                    g = 0.0f;
                }
                triangles++;
            }
            colors[i] = r;
            colors[i+1] = g;
            colors[i+2] = b;
            i += 3;
        }
    }
}

//More than one way to draw a rhombus
void Board::color_rhombus() {
    int x = 0;
    color_triangle(x);
    cout << x << endl;
    x += num_triangles()/2+1;
    color_triangle(x);
    cout << x << endl;
    x = size+1;
    color_triangle(x);
    cout << x << endl;
    x = num_triangles()-4;
    color_triangle(x);
    cout << x << endl;
    x = num_triangles()/2-1;
    color_triangle(x);
    cout << x << endl;
}

//Threshold is column number of the main diagonal
//Each square matrix has a main diagonal
//Use its values to draw a line dividing the square into 2 main traingles
void Board::draw_two_triangles() {
    int triangle = 0;
    int threshold = 0;
    int row = 0;
    int i = 0;
    GLfloat triangle1_color = .25f;
    GLfloat triangle2_color = .75f;
    GLfloat r = .0f;
    GLfloat g = .0f;
    GLfloat b = 0.0f;
    while(i < colors_size) {
        if(i % 9 == 0) {
            if(triangle >= threshold) {
                r = triangle1_color;
                g = triangle1_color;
                b = triangle2_color;
            }else {
                r = triangle2_color;
                g = triangle2_color;
                b = triangle1_color;
            }
            
            triangle++;
            if(triangle >= size) {
                row++;
                if(row == size) threshold = 0;
                threshold++;
                triangle = 0;
            }
        }
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
        i+=3;
    }
}

//Stairway to heaven!
void Board::draw_staircase() {
    if(size <= 1) {
        cerr << "Staircase only works for size greater than 1" << endl;
    }
    int triangle = 0;
    int threshold = 0;
    int row = 0;
    int i = 0;
    GLfloat triangle1_color = .25f;
    GLfloat triangle2_color = .75f;
    GLfloat r = .0f;
    GLfloat g = .0f;
    GLfloat b = 0.0f;
    while(i < colors_size) {
        if(i % 9 == 0) {

            if(triangle >= threshold) {
                //Sky
                r = 1.0f;
                g = 1.0f;
                b = .941f;
            }else {
                //Staircase
                r = .855f;
                g = .647f;
                b = .125f;
            }
            triangle++;
            if(triangle == size) {
                row++;
                threshold++;
                triangle = 0;
            }
            if(row == size) {
                threshold = 0;
            }
        }
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
        i+=3;
    }
}

void Board::random_color_triangles() {
    for(int i = 0; i < colors_size; i+=3) {
        set_color();
        colors[i] = red;
        colors[i+1] = green;
        colors[i+2] = blue;
    }
}

void Board::random_color_squares() {
    int i = 0;
    int triangle = 0;
    int total_triangles = num_triangles();
    GLfloat r = 0.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
    while(i < colors_size) {
        if(i % 9 == 0) {
            if(triangle < total_triangles/2) {
                set_color();
                r = red;
                g = green;
                b = blue;
            }else {
                int other_half = triangle - (size*size);
                other_half *= 9;
                r = colors[other_half];
                g = colors[other_half+1];
                b = colors[other_half+2]; 
            }
            triangle++;
        }
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
        i+=3;
    }
}

//Implemented this way cause I was having fun
//But you can implement this the same way as squares()
//using other half method
void Board::random_color_columns() {
    int i = 0;
    int triangle = 0;
    int total_triangles = num_triangles();
    GLfloat r = 0.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
    while(i < colors_size) {
        if(i % 9 == 0) {
            if(triangle < ((total_triangles/size)/2)) {
                set_color();
                r = red;
                g = green;
                b = blue;
            }else {
                int column = triangle % size;
                column *= 9;
                r = colors[column];
                g = colors[column+1];
                b = colors[column+2];
            }
            triangle++;
        }
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
        i += 3;
    }
}

//Note this method works for square matrices
void Board::random_color_rows() {
    int i = 0;
    int triangle = 0;
    int total_triangles = num_triangles();
    int row = 0;
    GLfloat r = 0.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
    while(i < colors_size) {
        if(i % 9 == 0) {
            //1st triangle of that row will be in column 0
            if(triangle % size == 0 && row < size) {
                set_color();
                r = red;
                g = green;
                b = blue;
            }else {
                int first_triangle_in_row = (row) % size;
                first_triangle_in_row *= 9;
                first_triangle_in_row *= size;
                r = colors[first_triangle_in_row];
                g = colors[first_triangle_in_row+1];
                b = colors[first_triangle_in_row+2];
            }
            triangle++;
            if(triangle % size == 0) {
                row++;
            }
        }
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
        i += 3;
    }
}

//Any first triangle in a row or col is assigned head of that diagonal
//Meaning the rest of triangles in that digonal will copy its color
//You crammed everything else into as few lines possible
//Now lets take this piece by piece, you deserve it
void Board::random_color_diagonals() {
    int i = 0;
    int total_triangles = num_triangles();
    int row = 0;
    GLfloat r = 0.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
    //First set the heads
    //i .. size and (size+1)^2 .. num_triangles
    for(int head = 0; head < size; ++head) {
        set_color();
        i = head*9;
        while( i <(head*9+9)) {
            colors[i] = red;
            colors[i+1] = green;
            colors[i+2] = blue;
            i += 3;
        }
    }
    
    for(int head = pow(size, 2); head < total_triangles; head+=size) {
        set_color();
        i = head*9;
        while(i < (head*9+9)) {
            colors[i] = red;
            colors[i+1] = green;
            colors[i+2] = blue;
            i+=3;
        }
    }
    
    
    int head = 0;
    for(int triangle = size; triangle < num_triangles()/2; ++triangle) {
        if(triangle % size == 0) {
            head = triangle + (size*(size-1));
        }else {
            head = triangle - (size+1);
        }
        head *= 9;
        i = triangle*9;

        r = colors[head];
        g = colors[head+1];
        b = colors[head+2];
        while(i < triangle*9+9) {
            colors[i] = r;
            colors[i+1] = g;
            colors[i+2] = b;
            i += 3;
        }
    }
     
    
    int distance = num_triangles()/2+1;
    for(int triangle = distance; triangle < num_triangles(); triangle++) {
        if(triangle % size == 0) continue; 
        head = triangle-distance;
        head *= 9;
        i = triangle*9;
        r = colors[head];
        g = colors[head+1];
        b = colors[head+2];
        while(i < triangle*9+9) {
            colors[i] = r;
            colors[i+1] = g;
            colors[i+2] = b;
            i += 3;
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

bool Board::color_column(int column) {
    if(column > size) {
        cerr << "Column does not exist" << endl;
        return false;
    }
    for(int triangle = column; triangle < num_triangles(); triangle+=size) {
            color_triangle(triangle);
    }
    return true;
}

bool Board::color_row(int row) {
    if(row > size) {
        cerr << "Row does not exist" << endl;
        return false;
    }
    int triangle = row*size;
    int end = triangle+size;
    for(int i = 0; i < 2; ++i) {
        while(triangle < end) {
            color_triangle(triangle);
            triangle++;
        }
        triangle += num_triangles()/2 - size;
        end = triangle + size;
    }
    return true;
}

//Start from 0 each time there is a new diagonal add 1
//That will be the label for the diagonal
//top and bottom form rhumbus
//  top is less than half
//  bottom is second half
bool Board::color_diagonal(int diagonal) {
    if(diagonal > num_diagonals()) {
        cerr << "Not a diagonal" << endl;
        return false;
    }
    int triangle = 0;
    if(diagonal < size) {
        triangle = diagonal;
    }else {
        triangle = diagonal*size; 
    }
    int boundary = 0;
    if(diagonal == size-1 || diagonal == num_diagonals()) {
        color_triangle(triangle);
        return true; 
    }
    while(triangle < num_triangles() && boundary < 2) {
        //1 11 5 15 9
        if(is_boundary(triangle)) boundary++;
        color_triangle(triangle);
        //Next triangle will be top or bottom
        if(triangle < num_triangles()/2) {
            //Current is Top
            //Get matching bottom
            triangle += num_triangles()/2 + 1;
        }else {
            //Current is bottom
            //Get matching top
            triangle -= size*(size-1);
        }
    }
    return true;
 }

//Basically if the board is bigger it will look like it's coloring rhombuses
bool Board::what_is_this(int column) {
    if(column > size) {
        cerr << "Column does not exist" << endl;
        return false;
    }
    for(int triangle = 0; triangle < num_triangles(); triangle++) {
        if(triangle % column == 0)
            color_triangle(triangle);
    }
    return true;
    
    //Also this code will color a row of rhumbi
    int row = 6;
    int triangle = row*size;
    int end = triangle+size;
    for(int i = 0; i < 2; ++i) {
        while(triangle < end) {
            color_triangle(triangle);
            triangle++;
        }
        triangle += num_triangles()/2;
        end = triangle + size;
    }
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

void Board::set_elements() {
    //Initialize elements
    unsigned int top = 0;
    unsigned int bottom = size+1;
    int i = 0;
    for(int row = 0; row < size; ++row) {
        for(int col = 0; col < size; ++col) {
            //Initialize a square at a time.
            //  Square consists of 2 triangles
            elements[i] = top;
            elements[i+1] = top+1;
            elements[i+2] = bottom+1;
            elements[i+3] = bottom+1;
            elements[i+4] = bottom;
            elements[i+5] = top;
            i += 6;
            top++;
            bottom++;
        }
        top++;
        bottom++;
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

//Generate random color scheme based off theme
void Board::set_color(string theme) {
    
}

void Board::set_color(GLfloat r, GLfloat g, GLfloat b) {
    red = r;
    green = g;
    blue = b; 
}

//MARK: Getters
GLfloat* Board::get_board() {
    return board;
}

GLuint* Board::get_elements() {
    return elements;
}

GLfloat* Board::get_colors() {
    return colors;
}

int Board::get_board_size() {
    return board_size;
}

int Board::get_elements_size() {
    return elements_size;
}

int Board::get_colors_size() {
    return colors_size;
}

int Board::num_vertices() {
    return board_size/2;
}

int Board::num_elements() {
    return elements_size;
}

int Board::num_triangles() {
    return (size * size) * 2; 
}

int Board::num_diagonals() {
    return (size * 2 - 1);
}

//Checking if it shares an edge with the boundary
bool Board::is_boundary(int triangle) {
    //Find the triangle
    int start = triangle*6;
    int end = start+6;
    int x_axis = 0;
    int y_axis = 0;
    //Format is X Y X Y X Y
    //Wall is -1 or 1 for x and y axis
    //If 2 x or 2 y equal the wall then return true
    while(start < end) {
        if(start % 2 == 0) {
            if(board[start] == -1 || board[start] == 1) {
                x_axis++;
            }
        }else {
            if(board[start] == -1 || board[start] == 1) {
                y_axis++;
            }
        }
        start++;
    }
    if(x_axis >= 2 || y_axis >= 2) {
        return true;
    }
    return false;
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

void Board::print_vertice_with_attributes() {
    int row = 0;
    int index = 0;
    for(int i = 0; i < board_size; i+=2) {
        if( i % 6 == 0)
            cout << endl;
        index = row + i;
        cout << "(" << board[i] << ", " << board[i+1] << ") ";
        cout << "(" << colors[index] << ", " << colors[index+1] << ", " << colors[index+2] << ")" << endl;
    }
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

//6 elements per square
//2 triangles per square
//3 elements per triangle
//Indeed these triangles will have shared elements
void Board::print_elements() {
    int square = 0;
    cout << "Element size " << elements_size << endl;
    cout << "[ ";
    for(int i = 0; i < elements_size; ++i) {
        if(i % 6 == 0) {
            if (square == size) {
                square = 0;
                cout << "]\n[ ";
            }
            if(square > 0) {
                cout << "] [ ";
            }
            square++;

        }
        cout << elements[i] << " ";
    }
    cout << "]" << endl;
}

/*
void Board::print_colors() {
    int i = 0;
    int squares = 0;
    while( i < colors_size ) {
        if(squares % size == 0) {
            cout << endl;
            squares = 0;
        }
        cout << "[" << colors[i] << ", " << colors[i+1] << ", " << colors[i+2] << "] ";
        i += 3;
        squares++;
    }
    cout << endl;
}
 */

