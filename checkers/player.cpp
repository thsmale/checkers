//
//  player.cpp
//  checkers
//
//  Created by Tommy Smale on 11/30/21.
//

#include "player.hpp"

//0 is human 1 is computer
Player::Player(int t) {
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
        checkers[i].set_checker(x, y);
        x += width*2;
    }
    /*
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < get_size()/2; ++j) {
            checkers[i].set_checker(center_x, center_y);
            center_x += width*2;
        }
        center_x = -.75f;
        center_y -= width; 
    }
     */
}

vector<GLfloat> Player::get_checkers() {
    vector<GLfloat> vertices;
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        for(int j = 0; j < checkers[i].vertices.size(); ++j)
            vertices.push_back(checkers[i].vertices[j]);
    }
    return vertices; 
}

