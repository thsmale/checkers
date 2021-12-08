//
//  board_vertices.cpp
//  cops_robbers
//
//  Created by Tommy Smale on 11/15/21.
//

#include "board.hpp"

vector<vector<char> > Board::board;
GLfloat *Board::colors;

Board::Board() : size(8) {
    this->board_vertices_size = (size*size) * 6 * 2;
    this->colors_size = (size*size) * 6 * 3;
    this->board_vertices = new GLfloat[board_vertices_size];
    this->width = 1.0 / (size / 2.0);
    GLfloat width = 1.0 / (size / 2.0);
    red = 1.0f;
    green = 1.0f;
    blue = 1.0f;
}

//Do I need to delete every element in the array?
Board::~Board() {
    delete [] board_vertices;
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
    red = 1.0f;
    green = 1.0f;
    blue = 1.0f; 
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

//Moves uses col, row.
//I am using row, col so need to convert this
void Board::color_possible_moves(vector<pair<int, int> > possible_moves) {
    if(possible_moves[0].first == -1 && possible_moves[1].second == -1)
        return;
    set_color(0.f, 1.f, 0.f); 
    int square = 0;
    for(int i = 0; i < possible_moves.size(); ++i) {
        square = get_square(make_pair(possible_moves[i].second, possible_moves[i].first));
        color_square(square);
    }
}

//MARK: Setters
//Even rows odd numbers are checkers
//Odd rows odd numbers are blanks
//rows 0-3 are computer, rows (size-3..size) are player
void Board::set_board() {
    board.clear();
    board.resize(size);
    char piece;
    //Set computer positions
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(i < 3 || i >= (size-3)) {
                if (i < 3)
                    piece = board_properties::computer;
                else
                    piece = board_properties::human_player;
                if(i % 2 == 0) {
                    //Even row
                    if(j % 2 == 0) {
                        board[i].push_back(board_properties::blank);
                    }else {
                        board[i].push_back(piece);
                    }
                }else {
                    //Odd row
                    if(j % 2 == 0) {
                        board[i].push_back(piece);
                    }else {
                        board[i].push_back(board_properties::blank);
                    }
                }
            }else {
                board[i].push_back(board_properties::blank);
            }
        }
    }
    //Set player positions
}

void Board::set_colors() {
    this->colors = new GLfloat[colors_size];
    for(int i = 0; i < colors_size; ++i) {
        colors[i] = 1.f; 
    }
}

//Set all pieces in path to blank
//Would need to rely on update_checkers to set to king
void Board::update_board(pair<int, int> cur_coords, pair<int, int> new_coords) {
    //Set old and new square
    char old_piece = board[cur_coords.first][cur_coords.second];
    board[cur_coords.first][cur_coords.second] = board_properties::blank;
    board[new_coords.first][new_coords.second] = old_piece;
    //Set everything in between to blank
    if(get_path_length(get_square(cur_coords), get_square(new_coords)) > 1) {
        vector<int> path = get_path(get_square(cur_coords), get_square(new_coords));
        pair<int, int> coords;
        for(int i = 0; i < path.size()-1; ++i) {
            coords = get_coordinates(path[i]);
            board[coords.first][coords.second] = board_properties::blank;
        }
    }
}

//Space is -1, 1 with center being 0, 0
//Need each triangle to have unique points
//So it can have it's own attributes
//Width will be maximumn number of squares we can fit in the space given the size
void Board::set_board_vertices() {
    GLfloat width = 1.0 / (size / 2.0);
    GLfloat height = width;
    GLfloat x = -1.0f;
    GLfloat y = 1.0f;
    //Set top triangles
    int i = 0;
    for(int rows = 0; rows < size; rows++) {
        for(int cols = 0; cols < size; cols++) {
            board_vertices[i] = x;
            board_vertices[i+1] = y;
            x += width;
            board_vertices[i+2] = x;
            board_vertices[i+3] = y;
            board_vertices[i+4] = x;
            board_vertices[i+5] = y-width;
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
            board_vertices[i] = x;
            board_vertices[i+1] = y;
            //Bottom left
            board_vertices[i+2] = x;
            board_vertices[i+3] = y-width;
            //Bottom right
            x += width;
            board_vertices[i+4] = x;
            board_vertices[i+5] = y-width;
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

vector<vector<char> > Board::get_board() {
    return board; 
}

GLfloat* Board::get_board_vertices() {
    return board_vertices;
}

GLfloat* Board::get_colors() {
    return colors;
}

int Board::get_board_vertices_size() {
    return board_vertices_size;
}

int Board::get_colors_size() {
    return colors_size;
}

//Given center coordinates of checker return what square it is 
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

//Only accepts row, col coordinates
int Board::get_square(std::pair<int, int> coordinates) {
    if(coordinates.first < 0 || coordinates.first >= size) {
        cerr << "Invalid coordinate passed to get_square" << endl;
        while(1);
    }
    if(coordinates.second < 0 || coordinates.second >= size) {
        cerr << "Invalid coordinate passed to get_square" << endl;
        while(1);
    }
    int row = coordinates.first * size;
    int col = coordinates.second;
    return (row+col); 
}

//Pass in a square number and this will return the coordinates
//This is for compatibility with moves.hpp file
std::pair<int, int> Board::get_coordinates(int square) {
    if(square < 0 || square > ((size*size)-1)) {
        return make_pair(-1, -1);
    }
    std::pair<int, int> coordinates;
    int row = int(square / size);
    int col = square % size;
    coordinates = make_pair(row, col); 
    return coordinates;
}

pair<GLfloat, GLfloat> Board::get_center(int square) {
    GLfloat center_x = -1.f+(width/2.f), center_y = 1.f-(width/2.f);
    for(int i = 0; i < num_squares(); ++i) {
        if(i % size == 0 && i != 0) {
            center_x =  -1.f+(width/2.f);
            center_y -= width;
        }
        if(i == square) {
            return make_pair(center_x, center_y);
        }
        center_x += width;
    }
    cerr << "Could not find center of square " << square << endl;
    exit(1); 
}

//Given old square and new square this will return the x and y
//direction at which it moves. All pieces move one at a time.
//Can move (x, y), (x, -y), (-x, y), (-x, -y)
//Uses row col indexing where row is y and col is x
pair<int, int> Board::get_direction(int old_square, int new_square) {
    //Get x direction
    int old_col = old_square % size;
    int new_col = new_square % size;
    int direction_x = 0;
    if(old_col < new_col)
        direction_x = 1;
    else
        direction_x = -1;
    //Get y direction
    int old_row = int(old_square / size);
    int new_row = int(new_square / size);
    int direction_y = 0;
    if(old_row > new_row) {
        direction_y = -1;
    }else {
        direction_y = 1;
    }
    return make_pair(direction_y, direction_x);
}

int Board::get_path_length(int old_square, int new_square) {
    int path_length = 0;
    pair<int, int> directions = get_direction(old_square, new_square);
    pair<int, int> coords = get_coordinates(old_square);
    while(old_square != new_square) {
        coords = get_coordinates(old_square);
        old_square = get_square(make_pair(coords.first+directions.first, coords.second+directions.second));
        path_length++;
    }
    return path_length;
}

//Return a path of all squares in path from old square to new_square
//It's purpose is to clear checkers in this path
//This only works for diagonal moves.
//Only call if checker is hoping a checker
vector<int> Board::get_path(int old_square, int new_square) {
    vector<int> path;
    pair<int, int> directions = get_direction(old_square, new_square);
    pair<int,int> coords;
    while(old_square != new_square) {
        coords = get_coordinates(old_square);
        old_square = get_square(make_pair(coords.first+directions.first, coords.second+directions.second));
        path.push_back(old_square);
    }
    return path;
}

bool Board::valid_move(int square, bool white, bool king) {
    pair<int, int> coords = get_coordinates(square);
    vector<pair<int, int> > possible_moves = whereCanPieceMove(board, coords.second, coords.first, white, king);
    int row = int(square/size);
    int col = square % size;
    bool player;
    if(board[row][col] == board_properties::human_player) {
        player = true;
    }else {
        player = false;
    }
    //White is false if player
    //Move to square if it is open or take out opponent
    if(board[row][col] == board_properties::blank || player != white) {
        cout << "Moving to square " << square << " is valid" << endl;
        return true;
    }
    return false;
}

//Given a square return which player controls that square
//0 is computer, 1 is human
//-1 is blank
int Board::player(int square) {
    pair<int, int> coords = get_coordinates(square);
    char piece = board[coords.first][coords.second];
    if(piece == board_properties::computer || piece == board_properties::computer_king) {
        return COMPUTER;
    }
    if(piece == board_properties::human_player || piece == board_properties::human_king) {
        return HUMAN;
    }
    return -1;
}

//Assumes we know the type of player
bool Board::is_king(int square) {
    pair<int, int> coords = get_coordinates(square);
    char piece = board[coords.first][coords.second];
    if(piece == board_properties::computer_king || piece == board_properties::human_king) {
        return true;
    }
    return false;
}

//Ensure this function only works for squares that are not kings already
void Board::mark_king(pair<int, int> coords) {
    char piece = board[coords.first][coords.second];
    if(piece == board_properties::computer) {
        piece = board_properties::computer_king;
    }else if(piece == board_properties::human_player) {
        piece = board_properties::human_king;
    }else {
        cerr << "Err you shouldn't be marking square " << get_square(coords) << " as king " << endl;
        return;
    }
    board[coords.first][coords.second] = piece;
}

int Board::num_vertices() {
    return board_vertices_size/2;
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
    for(int i = 0; i < board.size(); ++i) {
        for(int j = 0; j < board[i].size(); ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl; 
    }
}
void Board::print_board_vertices() {
    for(int i = 0; i < board_vertices_size; ++i) {
        if((i % size) == 0)
            cout << endl;
        printf("%.2f ", board_vertices[i]);
    }
}

void Board::print_triangles() {
    int i = 0;
    for(int i = 0; i < board_vertices_size; i+=2) {
        if(i % 6 == 0)
            cout << endl;
        cout << "(" << board_vertices[i] << ", " << board_vertices[i+1] <<") ";
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

void Board::print_board_vertices_x_y() {
    int i = 0;
    while(i < board_vertices_size) {
        if(i % 18 == 0) cout << endl;
        if(i % 6 == 0) {
            cout << endl;
        }
        printf("(%.2f, %.2f) ", board_vertices[i], board_vertices[i+1]);
        i += 2;
    }
    cout << endl;
}
