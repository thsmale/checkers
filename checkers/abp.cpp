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
