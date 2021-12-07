#ifndef moves_evaluated_hpp
#define moves_evaluated_hpp

#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<locale>

std::vector<std::pair<std::pair<int,int>, int> > possible_moves_weights(std::vector<std::vector<char> > board, int x, int y, bool isWhite, bool isKing);

    
#endif 
