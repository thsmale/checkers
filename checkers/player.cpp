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
    //Check first and last row to update king or queen
    for(int i = 0; i < board.size(); i+=(get_size()-1)) {
        for(int j = 0; j < board[i].size(); ++j) {
            square = get_square(make_pair(i, j));
            owner = player(square);
            for(int i = 0; i < NUM_CHECKERS; ++i) {
                pair<int, int> coords = get_coordinates(square);
                if(coords.first == (get_size()-1) && owner == COMPUTER) {
                    mark_king(coords, type);
                    checkers[i].king = true;
                    cout << "KING" << endl;
                }
                if(coords.first == 0 && owner == HUMAN) {
                    mark_king(coords, type);
                    checkers[i].king = true;
                    cout << "KING" << endl;
                }
            }
        }
    }
    //If any checkers square does not align with board eat it
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(checkers[i].square == -1) continue;
        owner = player(checkers[i].square);
        if(owner != type) {
            cout << "Eating checker " << i << " type " << type << endl;
            checkers[i].eat_checker();
        }
    }
}

//Both computer and human should use this to move a checker
void Player::move_checker(int old_square, int new_square) {
    int checker = 0;
    for(int i = 0; i < NUM_CHECKERS; ++i) {
        if(checkers[i].square == old_square) {
            checker = i;
            break;
        }
    }
    if(type == COMPUTER) {
        cout << "Moving COMPUTER checker " << checker << " to " << new_square << " from " << old_square << endl;
    }else {
        cout << "Moving HUMAN checker " << checker << " to " << new_square << " from " << old_square << endl;
    }
    pair<GLfloat, GLfloat> new_center = get_center(new_square);
    checkers[checker].move_checker(make_pair(new_center.first, new_center.second), new_square);
    pair<int, int> old_coords = get_coordinates(old_square);
    pair<int, int> new_coords = get_coordinates(new_square);
    update_board(old_coords, new_coords, type);
    update_checkers();
    print_board();
}

//Select a checker piece
//Have selected a checker piece and are selecting a square to move too 
void Player::select_square(double xpos, double ypos) {
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
                turn = false;
                selected_checker = -1;
                break;
                //If want to add mandatory moves add here. Or in move_checker()
                //Must update board too
                //vector<pair<int, int> > more_moves = additional_moves(get_board(), new_coordinates.second, new_coordinates.first, checkers[selected_checker].white, checkers[selected_checker].king);
                /*
                if(more_moves.size() > 0) {
                    turn = true;
                }else {
                    turn = false;
                }
                 */
                /*
                while(more_moves.size() > 0) {
                    square = get_square(more_moves[i]);
                    cout << " Must move to square " << square << endl;
                    new_center = get_center(square);
                    checkers[selected_checker].move_checker(new_center, square);
                    cur_coordinates = new_coordinates;
                    new_coordinates = get_coordinates(square);
                    update_board(cur_coordinates, new_coordinates, checkers[selected_checker].white);
                    //Must update board too
                    more_moves = additional_moves(get_board(), new_coordinates.second, new_coordinates.first, checkers[selected_checker].white, checkers[selected_checker].king);
                }
                 */
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
    if(selected_checker == -1) return -1;
    return checkers[selected_checker].square; 
}

bool Player::get_turn() {
    return turn; 
}

vector<Checker*> Player::get_checkers() {
    vector<Checker*> checker_ref;
    
    checker_ref.reserve(NUM_CHECKERS);

    for (int i = 0; i < NUM_CHECKERS; i++) {
        checker_ref.push_back(&checkers[i]);
    }

    return checker_ref;

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
