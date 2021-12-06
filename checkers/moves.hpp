#ifndef moves_hpp
#define moves_hpp

#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<locale>

void printBoard(std::vector<std::vector<char> > board, int x, int y);

void printMoves(std::vector<std::pair<int, int> > moves);

std::pair<int, int> ediblePiece(std::vector<std::vector<char> > board, int curX, int curY, int hopX, int hopY);

void removePiece(std::vector<std::vector<char> > &board, int startingX, int startingY, int emptyX, int emptyY); 


std::vector<std::pair<int,int> > whereCanPieceMove(std::vector<std::vector<char> > board,
                                                   int x,
                                                   int y,
                                                   bool isWhite,
                                                   bool isKing);

#endif
