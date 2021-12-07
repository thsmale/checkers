#include <iostream>
#include <cmath>
#include <climits>

#include "board.hpp"
#include "checker.hpp"
#include "movesEvaluated.hpp" 

using std::cout;
using std::endl;

class ABP {
public:

    ABP();

    int minmax(Board& board, int square, int depth, int alpha, int beta, bool isMaxPlayer, bool isKing);

    int getHighestScore(std::vector<std::pair<std::pair<int, int>, int> > moves);

};
