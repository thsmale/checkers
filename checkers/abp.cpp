#include "abp.hpp"

ABP::ABP() {

}

int ABP::minmax(Board& board, int square, int depth, int alpha, int beta, bool isMaxPlayer, bool isKing) {
    pair<int, int> coords = board.get_coordinates(square);
    std::vector<std::pair<std::pair<int, int>, int> > moves = possible_moves_weights(board.get_board(), coords.first, coords.second, true, isKing);
    int eval;

    if (depth == 0) {
        return this->getHighestScore(moves);
    }

    if (isMaxPlayer) {
        int maxEval = INT_MIN;

        for (std::pair<std::pair<int, int>, int> move : moves) {
            eval = minmax(board, board.get_square((double) move.first.second, (double) move.first.first), depth - 1, alpha, beta, false, isKing);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha)
                break;
        }

        return maxEval;
    } else {
        int minEval = INT_MAX;

        for (std::pair<std::pair<int, int>, int> move : moves) {
            eval = minmax(board, board.get_square((double) move.first.second, (double) move.first.first), depth - 1, alpha, beta, true, isKing);
            minEval = max(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha)
                break;
        }

        return minEval;
    }
}

int ABP::getHighestScore(std::vector<std::pair<std::pair<int, int>, int> > moves) {
    int highest = 0;

    for (std::pair<std::pair<int, int>, int> move : moves) { 
        if (move.second > highest) {
            highest = move.second;
        }
    }

    return highest;
}

//Returns old square, new square
//In case all moves are equal, choose highest checker number
std::pair<int, int> ABP::optimal_move(Board &board, vector<Checker*> checkers) {
    Checker *chosen_checker = nullptr;
    int maxEval = INT_MIN;
    vector<std::pair<std::pair<int, int>, int> > chosen_moves;
    for (int i = 0; i < checkers.size(); ++i) {
        if(checkers[i]->square < 0 || checkers[i]->square > (board.num_squares()-1)) {
            cerr << "Checker square is -1" << endl; 
        }
        pair<int, int> coords = board.get_coordinates(checkers[i]->square);
        vector<std::pair<std::pair<int, int>, int> > moves = possible_moves_weights(board.get_board(),
                                                                                    coords.second,
                                                                                    coords.first,
                                                                                    checkers[i]->white,
                                                                                    checkers[i]->king);
        if (moves.size() > 0) {
            int eval = minmax(board, checkers[i]->square, getHighestScore(moves), INT_MIN, INT_MAX, true, checkers[i]->king);
            if (eval >= maxEval) {
                maxEval = eval;
                chosen_checker = checkers[i];
                chosen_moves = moves;
            }
        }
    }
    
    //cout << "AI chooses to move checker from square " << chosen_checker->square << endl;
    std::pair<int, int> optimal_move;
    int highest = 0;

    cout << "Choose square " << chosen_checker->square << endl;
    cout << "Possible moves " << endl;
    for (std::pair<std::pair<int, int>, int> move : chosen_moves) {
        cout << "\t" << move.first.second << " " << move.first.first << endl;
        if (move.second > highest) {
            highest = move.second;
            optimal_move = move.first;
        }
    }
    return make_pair(chosen_checker->square, board.get_square(make_pair(optimal_move.second, optimal_move.first)));
    
}
