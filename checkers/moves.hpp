#ifndef moves_hpp
#define moves_hpp

#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<locale>

void printBoard(std::vector<std::vector<char> > board, int x, int y);

void printMoves(std::vector<std::pair<int, int> > moves); 

std::vector<std::pair<int,int> > whereCanPieceMove(const std::vector<std::vector<char> > board,
                                                   int x,
                                                   int y,
                                                   bool isWhite,
                                                   bool isKing);

#endif
