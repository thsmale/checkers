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
        x = (width+(width/2))-1;
        y = 1-(width/2);
    }else if(type == 1) {
        x = width/2-1;
        y=0-(width+(width/2));
    }else {
        cerr << "Invalid player mode" << endl;
        exit(1);
    }
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

void Player::select_checker(double xpos, double ypos) {
    //Calculate what square this is
    int square = get_square(xpos, ypos);
    cout << "Square " << square << endl;
    //Check to make sure it is valid checker
    //  It is blue
    //  It is alive
    //Color it cyan
    int checker = -1;
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(checkers[i].square == square) {
            checker = i;
            checkers[i].color(0.0f, 1.0f, 1.0f); 
            cout << "Checker " << i << endl;
        }
    }
    if(checker == -1) return; 
    //Disselect previous checker if exists
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(i != checker) {
            checkers[i].color(0.0f, 0.0f, 1.0f);
        }
    }
    //Update shader
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

void Player::print_checker_squares() {
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        cout << checkers[i].square << " ";
    }cout << endl; 
}
