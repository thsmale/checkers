#include "additionalMoves.hpp"

/*
void printBoard(std::vector<std::vector<char>> board, int x, int y){
  //--------NOT NECCESSARY FOR THE ALGORITHM JUST FOR UNDERSTANDING PURPOSES----------------
  //print out a visual board to show what piece is being selected 
  //the space that the piece is on will be marked with a #
  std::cout<<"(x, y) = ("<<x<<", "<<y<<")"<<std::endl;
  std::cout<<std::endl;
  for(int i=0; i<board.size(); i++){
    for(int j=0; j<board.size(); j++){
      if(j == x && i == y){
        std::cout << (char)toupper(board[i][j]) << " ";
      }
      else
        std::cout<<board[i][j]<<" ";
    }
    std::cout<<std::endl;
  }
}

void printMoves(std::vector<std::pair<int, int> > moves){
  std::cout<<"this piece can move to: ";
  for(int i=0; i<moves.size(); i++){
    std::cout<<"("<<moves[i].first<<", "<<moves[i].second<<") ";
  }
  std::cout<<std::endl;
  std::cout<<std::endl;
}
 */


std::vector<std::pair<int,int> > additional_moves(std::vector<std::vector<char> > board, int x, int y, bool isWhite, bool isKing){
  //this algorithm is assuming that the white pieces are moving from
  //the top of the board down.
  std::vector<std::pair<int, int> > moves;
  //possible moves. will only return the moves that pass certain criteria
  int newX1 = x+1; 
  int newY1 = y+1;
  int newX2 = x-1;
  int newY2 = y+1;
  int newX3 = x+1;
  int newY3 = y-1;
  int newX4 = x-1;
  int newY4 = y-1;
  int hopX1 = x+2; 
  int hopY1 = y+2;
  int hopX2 = x-2;
  int hopY2 = y+2;
  int hopX3 = x+2;
  int hopY3 = y-2;
  int hopX4 = x-2;
  int hopY4 = y-2;
  char unoccupied = '_';

  if(isKing){ //doesnt matter which direction it can go
    //it can move to any space adjacent and diagonal to it
    //if the space is in bounds
    if(newX1>-1 && newX1<8 && newY1>-1 && newY1<8){
      if(board[newY1][newX1]!=unoccupied){ // if next move is occupied
        bool adjacent_enemy_piece = ((isWhite && board[newY1][newX1] == 'x') || (!isWhite && board[newY1][newX1] == 'o'));
        if(adjacent_enemy_piece) { // if adjacent square is an oppsotion
          if(hopX1 > -1 && hopX1 < 8 && hopY1 > -1 && hopY1 < 8) { // if landing hop location is legal
            std::pair<int, int> m1(hopX1, hopY1);
            moves.push_back(m1); // add hop move to vector
          }
        }
      }
    }

    if(newX2>-1 && newX2<8 && newY2>-1 && newY2<8){
      if(board[newY2][newX2] != unoccupied){
        bool adjacent_enemy_piece = ((isWhite && board[newY2][newX2] == 'x') || (!isWhite && board[newY2][newX2] == 'o'));
        if(adjacent_enemy_piece && hopX2 > -1 && hopX2 < 8 && hopY2 > -1 && hopY2 < 8) {
          std::pair<int, int> m2(hopX2, hopY2);
          moves.push_back(m2);
        }
      }
    }

    if(newX3>-1 && newX3<8 && newY3>-1 && newY3<8) {
      if(board[newY3][newX3] != unoccupied) {
        bool adjacent_enemy_piece = ((isWhite && board[newY3][newX3] == 'x') || (!isWhite && board[newY3][newX3] == 'o'));
        if(adjacent_enemy_piece && hopX3 > -1 && hopX3 < 8 && hopY3 > -1 && hopY3 < 8) {
            std::pair<int, int> m3(hopX3, hopY3);
            moves.push_back(m3);
        }
      }
    }

    if(newX4>-1 && newX4<8 && newY4>-1 && newY4<8){
      if(board[newY4][newX4]!=unoccupied){
        bool adjacent_enemy_piece = ((isWhite && board[newY4][newX4] == 'x') || (!isWhite && board[newY4][newX4] == 'o'));
        if(adjacent_enemy_piece && hopX4 > -1 && hopX4 < 8 && hopY4 > -1 && hopY4 < 8) {
            std::pair<int, int> m4(hopX4, hopY4);
            moves.push_back(m4);
        }
      }
    }

    return moves;
  }

  // it is a white piece(means it can only increase its y val)
  if(isWhite){
    
    if(newX1>-1 && newX1<8 && newY1>-1 && newY1<8){
      if(board[newY1][newX1]!=unoccupied) {
        bool adjacent_enemy_piece = ((isWhite && board[newY1][newX1] == 'x') || (!isWhite && board[newY1][newX1] == 'o'));
        if(adjacent_enemy_piece && hopX1 > -1 && hopX1 < 8 && hopY1 > -1 && hopY1 < 8) {
          std::pair<int, int> m1(hopX1, hopY1);
          moves.push_back(m1);
        }
      }
    }

    if(newX2>-1 && newX2<8 && newY2>-1 && newY2<8){
      if(board[newY2][newX2] != unoccupied) {
        bool adjacent_enemy_piece = ((isWhite && board[newY2][newX2] == 'x') || (!isWhite && board[newY2][newX2] == 'o'));
        if(adjacent_enemy_piece && hopX2 > -1 && hopX2 < 8 && hopY2 > -1 && hopY2 < 8) {
          std::pair<int, int> m2(hopX2, hopY2);
          moves.push_back(m2);
        }
      }
    }

    return moves;
  }
  else{
    //it is a black piece
    //means it can only decrease its y val
    if(newX3>-1 && newX3<8 && newY3>-1 && newY3<8){
      if(board[newY3][newX3]!=unoccupied){
        bool adjacent_enemy_piece = ((isWhite && board[newY3][newX3] == 'x') || (!isWhite && board[newY3][newX3] == 'o'));
        if(adjacent_enemy_piece && hopX3 > -1 && hopX3 < 8 && hopY3 > -1 && hopY3 < 8) {
          std::pair<int, int> m3(hopX3, hopY3);
          moves.push_back(m3);
        }
      }
    }

    if(newX4>-1 && newX4<8 && newY4>-1 && newY4<8){
      if(board[newY4][newX4] != unoccupied) {
        bool adjacent_enemy_piece = ((isWhite && board[newY4][newX4] == 'x') || (!isWhite && board[newY4][newX4] == 'o'));
        if(adjacent_enemy_piece && hopX4 > -1 && hopX4 < 8 && hopY4 > -1 && hopY4 < 8) {
          std::pair<int, int> m4(hopX4, hopY4);
          moves.push_back(m4);
        }
      }

    }
    return moves;
  }
}

/*
int main(){
  std::vector<std::pair<int,int>> moves;
  //make some test boards.   * means there is a piece in the position
  const std::vector<std::vector<char>> board = { 
    { {'o'},{'o'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'x'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'o'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'x'},{'_'},{'x'},{'_'},{'x'},{'_'},{'x'},{'_'} },
    { {'_'},{'x'},{'_'},{'x'},{'_'},{'x'},{'_'},{'x'} },
    { {'x'},{'_'},{'x'},{'_'},{'x'},{'_'},{'x'},{'_'} }, };

  const std::vector<std::vector<char>> board2 = { 
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'x'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'o'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'x'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} }, };


  //x effects the cols (left/right), y effects the rows (up/down)
  int x=0; 
  int y=0; //(6th row from top)
  bool isWhite = true;
  bool isKing = false;
  printBoard(board, x, y);
  moves = whereCanPieceMove(board, x, y, isWhite, isKing);
  //print where the piece could move
  printMoves(moves);

  int x2=1;
  int y2=0;
  isWhite = true;
  isKing = true;
  printBoard(board, x2, y2);
  moves = whereCanPieceMove(board, x2, y2, isWhite, isKing);
  //print where the piece could move
  printMoves(moves);

  int x3=2;
  int y3=2;
  isWhite=true;
  isKing = true;
  printBoard(board2, x3, y3);
  moves = whereCanPieceMove(board2, x3, y3, isWhite, isKing); 
  //print where the piece could move
  printMoves(moves);

  int x4=2;
  int y4=5;
  isWhite=false;
  isKing=false;
  printBoard(board, x4, y4);
  moves = whereCanPieceMove(board, x4, y4, isWhite, isKing);
  //print where piece can move
  printMoves(moves);

  return 0;
}
*/
