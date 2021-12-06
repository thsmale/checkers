//
//  player.cpp
//  checkers
//
//  Created by Tommy Smale on 11/30/21.
//

#include "player.hpp"

Player human(1);

//0 is human 1 is computer
Player::Player(int t) : Board() {
    this->type = t;
    if(type == 0) {
        //Computer
        x = (width+(width/2))-1;
        y = 1-(width/2);
        for(int i = 0; i < NUM_CHECKERS; ++i) {
            checkers[i].white = true;
        }
    }else if(type == 1) {
        //Human
        x = width/2-1;
        y=0-(width+(width/2));
        for(int i = 0; i < NUM_CHECKERS; ++i) {
            checkers[i].white = false;
        }
    }else {
        cerr << "Invalid player mode" << endl;
        exit(1);
    }
    this->selected_checker = -1;
}

void Player::set_checkers() {
    GLfloat temp = x;
    int square = 0;
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(i % (get_size()/2) == 0 && i != 0) {
            if(temp == ((width+(width/2))-1)) {
                x = width/2-1;
            }else {
                x = (width+(width/2))-1;
            }
            temp = x;
            y -= (width/2)*2;
        }
        square = get_square(x, y);
        checkers[i].set_checker(x, y, square);
        x += width*2;
    }
    cout << endl;
}

//Select a checker piece
//Have selected a checker piece and are selecting a square to move too 
void Player::select_square(double xpos, double ypos) {
    //Calculate what square this is
    int square = get_square(xpos, ypos);
    cout << "Clicked square " << square << endl; 
    //Color checker if it is in square selected
    //  It is blue
    //  It is alive
    //Color it cyan
    int checker = -1;
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(checkers[i].square == square) {
            checker = i;
            selected_checker = checker;
            checkers[i].color(0.0f, 1.0f, 1.0f);
        }
    }
    //Potentially move checker to new square
    if(checker == -1 && selected_checker != -1) {
        pair<int, int> cur_coordinates = get_coordinates(get_selected_checker_square());
        cout << checkers[selected_checker].white << " " << checkers[selected_checker].king << endl;
        vector<pair<int, int> > possible_moves = whereCanPieceMove(get_board(),
                                                          cur_coordinates.second,
                                                          cur_coordinates.first,
                                                          checkers[selected_checker].white,
                                                          checkers[selected_checker].king);
        pair<int, int> new_coordinates = get_coordinates(square);
        for(int i = 0; i < possible_moves.size(); ++i) {
            if(new_coordinates.first == possible_moves[i].second && new_coordinates.second == possible_moves[i].first) {
                pair<GLfloat, GLfloat> new_center = get_center(square);
                cout << "Move to center " << new_center.first << " " << new_center.second << endl; 
                checkers[selected_checker].move_checker(new_center, square);
                print_board();
                cout << endl; 
                update_board(cur_coordinates, new_coordinates, checkers[selected_checker].white);
                print_board();
                //Must update board too 
                //selected_checker = -1;
                break;
            }
        }
    }
    
    //Disselect previous checker if exists
    //Or if we moved the checker
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(i != selected_checker) {
            checkers[i].color(0.0f, 0.0f, 1.0f);
        }
    }
}

vector<GLfloat> Player::get_checker_vertices() {
    vector<GLfloat> vertices;
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        for(int j = 0; j < checkers[i].vertices.size(); ++j)
            vertices.push_back(checkers[i].vertices[j]);
    }
    return vertices; 
}

vector<GLfloat> Player::get_checker_colors() {
    vector<GLfloat> colors;
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        for(int j = 0; j < checkers[i].colors.size(); ++j)
            colors.push_back(checkers[i].colors[j]);
    }
    return colors;
}

int Player::get_selected_checker_square() {
    if(selected_checker == -1) return selected_checker;
    return checkers[selected_checker].square; 
}

void Player::print_checker_squares() {
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        cout << checkers[i].square << " ";
    }cout << endl; 
}

void Player::print_checker_vertices() {
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        for(int j = 0; j < checkers[i].vertices.size(); ++j) {
            if(j % 9 == 0) cout << endl;
            cout << checkers[i].vertices[j] << " ";
        }
        cout << endl;
    }
}
