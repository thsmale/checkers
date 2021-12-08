//
//  player.cpp
//  checkers
//
//  Created by Tommy Smale on 11/30/21.
//

#include "player.hpp"

Player human(1);

Player::Player(int t) : Board() {
    this->type = t;
    if(type == COMPUTER) {
        //Computer
        x = (width+(width/2))-1;
        y = 1-(width/2);
        for(int i = 0; i < NUM_CHECKERS; ++i) {
            checkers[i].white = true;
        }
        this->turn = false; 
    }else if(type == HUMAN) {
        //Human
        x = width/2-1;
        y=0-(width+(width/2));
        for(int i = 0; i < NUM_CHECKERS; ++i) {
            checkers[i].white = false;
        }
        this->turn = true;
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

void Player::set_turn() {
    this->turn = true; 
}

//Assuming the movements are already updated
//Need to update
//  If king
//  If piece was eaten
void Player::update_checkers() {
    vector<vector<char> > board = get_board();
    int square = 0;
    int owner;
    //Check first and last row to update piece to king or queen
    for(int i = 0; i < board.size(); i+=(get_size()-1)) {
        for(int j = 0; j < board[i].size(); ++j) {
            square = get_square(make_pair(i, j));
            owner = player(square);
            if(square < get_size() && owner == HUMAN && !is_king(square)) {
                for(int i = 0; i < NUM_CHECKERS; ++i) {
                    if(checkers[i].square == square) {
                        checkers[i].king = true;
                        mark_king(get_coordinates(square));
                    }
                }
            }
            if(square >= (num_squares() - get_size()) && owner == COMPUTER && !is_king(square)) {
                for(int i = 0; i < NUM_CHECKERS; ++i) {
                    if(checkers[i].square == square) {
                        checkers[i].king = true;
                        mark_king(get_coordinates(square));
                    }
                }
            }
        }
    }
    //If any checkers square does not align with board eat it
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(checkers[i].square == -1) continue;;
        owner = player(checkers[i].square);
        if(owner != type) {
            /*
            if(type == HUMAN) {
                cout << "Human eating checker " << i << " at << " << checkers[i].square << endl;
            }else {
                cout << "Computer eating checker " << i << " at << " << checkers[i].square << endl;

            }
             */
            checkers[i].eat_checker();
        }
    }
}

//Both computer and human should use this to move a checker
void Player::move_checker(int old_square, int new_square) {
    if(old_square == -1 || new_square == -1) {
        cerr << "Passing invalid square to move_checker." << old_square << " to " << new_square << " not possible " << endl;
        return;
    }
    
    int checker = -1;
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(checkers[i].square == old_square) {
            checker = i;
            break;
        }
    }
    
    if(checker == -1) {
        cout << "Unable to find a valid checker to move" << endl;
        while(1); 
    }
    pair<GLfloat, GLfloat> new_center = get_center(new_square);
    checkers[checker].move_checker(make_pair(new_center.first, new_center.second), new_square);
    pair<int, int> old_coords = get_coordinates(old_square);
    pair<int, int> new_coords = get_coordinates(new_square);
    update_board(old_coords, new_coords);
    update_checkers();
}

//Select a checker piece
//Have selected a checker piece and are selecting a square to move too
//Highlight potential moves
bool Player::select_square(double xpos, double ypos) {
    //Calculate what square this is
    int square = get_square(xpos, ypos);
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
        vector<pair<int, int> > possible_moves = whereCanPieceMove(get_board(),
                                                          cur_coordinates.second,
                                                          cur_coordinates.first,
                                                          checkers[selected_checker].white,
                                                          checkers[selected_checker].king);
        pair<int, int> new_coordinates = get_coordinates(square);
        for(int i = 0; i < possible_moves.size(); ++i) {
            if(new_coordinates.first == possible_moves[i].second && new_coordinates.second == possible_moves[i].first) {
                move_checker(checkers[selected_checker].square, square);
                color_squares(); 
                selected_checker = -1;
                return false; 
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
    //Show possible moves
    if(checker != -1) {
        pair<int, int> coords = get_coordinates(checkers[checker].square);
        vector<pair<int, int> > possible_moves = whereCanPieceMove(get_board(),
                                                                   coords.second,
                                                                   coords.first,
                                                                   checkers[checker].white,
                                                                   checkers[checker].king);
        color_squares();
        if(possible_moves.size() > 0) {
            color_possible_moves(possible_moves);
        }
    }
    return true;
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
    if(selected_checker == -1) return -1;
    return checkers[selected_checker].square; 
}

bool Player::get_turn() {
    return turn; 
}

void Player::eat_all_checkers() {
    checkers[6].eat_checker();
    return; 
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        checkers[i].eat_checker(); 
    }
}

vector<Checker*> Player::get_checkers() {
    vector<Checker*> checker_ref;
    
    checker_ref.reserve(NUM_CHECKERS);

    for (int i = 0; i < NUM_CHECKERS; i++) {
        if (checkers[i].alive == true) {
            if(checkers[i].square == -1) {
                cerr << "GET CHECKERS IN VALID SQUARE" << endl; 
            }
            checker_ref.push_back(&checkers[i]);
        }
    }

    return checker_ref;

}

void Player::print_checker_squares() {
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        cout << checkers[i].square << " ";
    }cout << endl; 
}

void Player::print_checker_colors() {
    string player;
    if(type == HUMAN) {
        player = "human";
    }else {
        player = "computer";
    }
    cout << "Color sizes for " << player << endl; 
    //Checker 9 and 10 should be 0
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        cout << "CHECKER " << i << " " << checkers[i].colors.size() << endl;
        //for(int j = 0; j < checkers[i].colors.size()) {
            
        //}
    }
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
