#include "movesEvaluated.hpp"

/*
void printBoard(std::vector<std::vector<char> > board, int x, int y){
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


// starting x and starting y are so that print board prints uppercase version of piece's whose moves are being shown
// empty x and empty y are the coordinates of the square where eaten piece will be removed from
void remove_piece(std::vector<std::vector<char> > &board, int startingX, int startingY, int emptyX, int emptyY) {
  board[emptyY][emptyX] = '_';

  // these two lines are for visual purpose only
  //std::cout << "board after any removal of pieces\n" << std::endl;
  //printBoard(board, startingX, startingY);
}

std::pair<int, int> edible_piece(std::vector<std::vector<char> > board, int curX, int curY, int hopX, int hopY) {
  int x_avg = (curX + hopX) / 2;
  int y_avg = (curY + hopY) / 2;
  return std::make_pair(x_avg, y_avg);
}



std::vector<std::pair<std::pair<int,int>, int> > possible_moves_weights(std::vector<std::vector<char> > board, int x, int y, bool isWhite, bool isKing){
  //this algorithm is assuming that the white pieces are moving from
  //the top of the board down.
  std::vector<std::pair<std::pair<int, int>,int> > moves;
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
      if(board[newY1][newX1] == unoccupied){ // if next move is unoccupied
        std::pair<int, int> m1(newX1, newY1);
        std::pair<std::pair<int,int>, int> M1 = std::make_pair(m1,1);
        moves.push_back(M1);
      }
      else{ // if next move is occupied
        bool adjacent_enemy_piece = ((isWhite && board[newY1][newX1] == 'x') || (!isWhite && board[newY1][newX1] == 'o'));
        // if possible square to hop to has enemy on path and is in range of board
        if(adjacent_enemy_piece && hopX1 > -1 && hopX1 < 8 && hopY1 > -1 && hopY1 < 8) {
          bool empty_landing_space = (board[hopY1][hopX1] == unoccupied);
          // if sqaure to hop to is in range of board
          if(empty_landing_space) {
            std::pair<int, int> m1(hopX1, hopY1);
            std::pair< std::pair<int,int>, int> M1 = std::make_pair(m1, 2);
            moves.push_back(M1); // add hop move to vector
            std::pair<int, int> enemy = edible_piece(board, x, y, hopX1, hopY1);
            //std::cout << "This piece can move to (" << hopX1 << ", " << hopY1 << ") and would have to be hop over = ("
            //  << enemy.first << ", " << enemy.second << ")" << std::endl;
            remove_piece(board, x, y, newX1, newY1);
          }
        }
      }
    }

    if(newX2>-1 && newX2<8 && newY2>-1 && newY2<8){
      if(board[newY2][newX2] == unoccupied) {
        std::pair<int, int> m2(newX2, newY2);
        std::pair<std::pair<int,int>, int> M2 = std::make_pair(m2,1);
        moves.push_back(M2);
      }

      else if(board[newY2][newX2] != unoccupied){
        bool adjacent_enemy_piece = ((isWhite && board[newY2][newX2] == 'x') || (!isWhite && board[newY2][newX2] == 'o'));
        if(adjacent_enemy_piece && hopX2 > -1 && hopX2 < 8 && hopY2 > -1 && hopY2 < 8) {
          bool empty_landing_space = (board[hopY2][hopX2] == unoccupied);
          if(empty_landing_space) {
            std::pair<int, int> m2(hopX2, hopY2);
            std::pair< std::pair<int,int>, int> M2 = std::make_pair(m2, 2);
            moves.push_back(M2);
            std::pair<int, int> enemy = edible_piece(board, x, y, hopX2, hopY2);
            //std::cout << "This piece can move to (" << hopX2 << ", " << hopY2 << ") and would have to be hop over = ("
              //<< enemy.first << ", " << enemy.second << ")" << std::endl;
            remove_piece(board, x, y, newX2, newY2);
          }
        }
      }
    }

    if(newX3>-1 && newX3<8 && newY3>-1 && newY3<8) {
      if(board[newY3][newX3] == unoccupied) {
        std::pair<int, int> m3(newX3, newY3);
        std::pair<std::pair<int,int>, int> M3 = std::make_pair(m3,1);
        moves.push_back(M3);
      }
      else {
        bool adjacent_enemy_piece = ((isWhite && board[newY3][newX3] == 'x') || (!isWhite && board[newY3][newX3] == 'o'));
        if(adjacent_enemy_piece && hopX3 > -1 && hopX3 < 8 && hopY3 > -1 && hopY3 < 8) {
          bool empty_landing_space = (board[hopY3][hopX3] == unoccupied);
          if(empty_landing_space) {
            std::pair<int, int> m3(hopX3, hopY3);
            std::pair< std::pair<int,int>, int> M3 = std::make_pair(m3, 2);
            moves.push_back(M3);
            std::pair<int, int> enemy = edible_piece(board, x, y, hopX3, hopY3);
            //std::cout << "This piece can move to (" << hopX3 << ", " << hopY3 << ") and would have to be hop over = ("
              //<< enemy.first << ", " << enemy.second << ")" << std::endl;
            remove_piece(board, x, y, newX3, newY3);
          }
        }
      }
    }

    if(newX4>-1 && newX4<8 && newY4>-1 && newY4<8){
      if(board[newY4][newX4] == unoccupied) {
        std::pair<int, int> m4(newX4, newY4);
        std::pair<std::pair<int,int>,int > M4 = std::make_pair(m4, 1);
        moves.push_back(M4);
      }
      else {
        bool adjacent_enemy_piece = ((isWhite && board[newY4][newX4] == 'x') || (!isWhite && board[newY4][newX4] == 'o'));
        if(adjacent_enemy_piece && hopX4 > -1 && hopX4 < 8 && hopY4 > -1 && hopY4 < 8) {
          bool empty_landing_space = (board[hopY4][hopX4] == unoccupied);
          if(empty_landing_space) {
            std::pair<int, int> m4(hopX4, hopY4);
            std::pair< std::pair<int,int>, int> M4 = std::make_pair(m4, 2);
            moves.push_back(M4);
            std::pair<int, int> enemy = edible_piece(board, x, y, hopX4, hopY4);
            //std::cout << "This piece can move to (" << hopX4 << ", " << hopY4 << ") and would have to be hop over = ("
              //<< enemy.first << ", " << enemy.second << ")" << std::endl;
            remove_piece(board, x, y, newX4, newY4);
          }
        }
      }
    }

    return moves;
  }

  // it is a white piece(means it can only increase its y val)
  if(isWhite){
    if(newX1>-1 && newX1<8 && newY1>-1 && newY1<8){
      if(board[newY1][newX1]==unoccupied) {
        std::pair<int, int> m1(newX1, newY1);
        std::pair<std::pair<int,int>, int > M1 = std::make_pair(m1, 1);
        moves.push_back(M1);
      }
      else {
        bool adjacent_enemy_piece = ((isWhite && board[newY1][newX1] == 'x') || (!isWhite && board[newY1][newX1] == 'o'));
        if(adjacent_enemy_piece && hopX1 > -1 && hopX1 < 8 && hopY1 > -1 && hopY1 < 8) {
          bool empty_landing_space = (board[hopY1][hopX1] == unoccupied);
          if(empty_landing_space) {
            std::pair<int, int> m1(hopX1, hopY1);
            std::pair< std::pair<int,int>, int> M1 = std::make_pair(m1, 2);
            moves.push_back(M1);
            std::pair<int, int> enemy = edible_piece(board, x, y, hopX1, hopY1);
            //std::cout << "This piece can move to (" << hopX1 << ", " << hopY1 << ") and would have to be hop over = ("
              //<< enemy.first << ", " << enemy.second << ")" << std::endl;
            remove_piece(board, x, y, newX1, newY1);
          }
        }
      }
    }

    if(newX2>-1 && newX2<8 && newY2>-1 && newY2<8){
      if(board[newY2][newX2] == unoccupied) {
        std::pair<int, int> m2(newX2, newY2);
        std::pair<std::pair<int, int>, int > M2 = std::make_pair(m2, 1);
        moves.push_back(M2);
      }
      else {
        bool adjacent_enemy_piece = ((isWhite && board[newY2][newX2] == 'x') || (!isWhite && board[newY2][newX2] == 'o'));
        if(adjacent_enemy_piece && hopX2 > -1 && hopX2 < 8 && hopY2 > -1 && hopY2 < 8) {
          bool empty_landing_space = (board[hopY2][hopX2] == unoccupied);
          if(empty_landing_space) {
            std::pair<int, int> m2(hopX2, hopY2); 
            std::pair< std::pair<int,int>, int> M2 = std::make_pair(m2, 2);
            moves.push_back(M2);
            std::pair<int, int> enemy = edible_piece(board, x, y, hopX2, hopY2);
            //std::cout << "This piece can move to (" << hopX2 << ", " << hopY2 << ") and would have to be hop over = ("
              //<< enemy.first << ", " << enemy.second << ")" << std::endl;
            remove_piece(board, x, y, newX2, newY2);
          }
        }
      }
    }

    return moves;
  }
  else{
    //it is a black piece
    //means it can only decrease its y val
    if(newX3>-1 && newX3<8 && newY3>-1 && newY3<8){
      if(board[newY3][newX3] == unoccupied){
        std::pair<int, int> m3(newX3, newY3);
        std::pair<std::pair<int, int>, int > M3 = std::make_pair(m3,1);
        moves.push_back(M3);
      }
      else {
        bool adjacent_enemy_piece = ((isWhite && board[newY3][newX3] == 'x') || (!isWhite && board[newY3][newX3] == 'o'));
        if(adjacent_enemy_piece && hopX3 > -1 && hopX3 < 8 && hopY3 > -1 && hopY3 < 8) {
          bool empty_landing_space = (board[hopY3][hopX3] == unoccupied);
          if(empty_landing_space) {
            std::pair<int, int> m3(hopX3, hopY3);
            std::pair< std::pair<int,int>, int> M3 = std::make_pair(m3, 2);
            moves.push_back(M3);
            std::pair<int, int> enemy = edible_piece(board, x, y, hopX3, hopY3);
            //std::cout << "This piece can move to (" << hopX3 << ", " << hopY3 << ") and would have to be hop over = ("
            //  << enemy.first << ", " << enemy.second << ")" << std::endl;
            remove_piece(board, x, y, newX3, newY3);
          }
        }
      }
    }

    if(newX4>-1 && newX4<8 && newY4>-1 && newY4<8){
      if(board[newY4][newX4] == unoccupied) {
        std::pair<int, int> m4(newX4, newY4);
        std::pair<std::pair<int,int>, int > M4 = std::make_pair(m4, 1);
        moves.push_back(M4);
      }
      else {
        bool adjacent_enemy_piece = ((isWhite && board[newY4][newX4] == 'x') || (!isWhite && board[newY4][newX4] == 'o'));
        if(adjacent_enemy_piece && hopX4 > -1 && hopX4 < 8 && hopY4 > -1 && hopY4 < 8) {
          bool empty_landing_space = (board[hopY4][hopX4] == unoccupied);
          if(empty_landing_space) {
            std::pair<int, int> m4(hopX4, hopY4);
            std::pair< std::pair<int,int>, int> M4 = std::make_pair(m4, 2);
            moves.push_back(M4);
            std::pair<int, int> enemy = edible_piece(board, x, y, hopX4, hopY4);
            //std::cout << "This piece can move to (" << hopX4 << ", " << hopY4 << ") and would have to be hop over = ("
              //<< enemy.first << ", " << enemy.second << ")" << std::endl;
            remove_piece(board, x, y, newX4, newY4);
          }
        }
      }
    }
    return moves;
  }
}


/*
int main(){
  std::vector<std::pair<std::pair<int,int>,int> > moves;
  //make some test boards.   * means there is a piece in the position
  std::vector<std::vector<char>> board = {
    { {'o'},{'o'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'x'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'x'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} }, };

  std::vector<std::vector<char>> board2 = {
    { {'x'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'x'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'o'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'x'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} },
    { {'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'},{'_'} }, };

 */
/*
  //x effects the cols (left/right), y effects the rows (up/down)
 
  int x=0;
  int y=0; //(6th row from top)
  bool isWhite = true;
  bool isKing = false;
  printBoard(board, x, y);
  moves = whereCanPieceMove(board, x, y, isWhite, isKing);
  //print where the piece could move
  //printMoves(moves);

  int x2=1;
  int y2=0;
  isWhite = true;
  isKing = true;
  printBoard(board, x2, y2);
  moves = whereCanPieceMove(board, x2, y2, isWhite, isKing);
  //print where the piece could move
  //printMoves(moves);

  int x4=2;
  int y4=2;
  isWhite=true;
  isKing=true;
  printBoard(board2, x4, y4);
  moves = whereCanPieceMove(board, x4, y4, isWhite, isKing);
  //print where piece can move
  //printMoves(moves);
*/ 

   /*
  int x3=2;
  int y3=2;
  bool isWhite=true;
  bool isKing = true;
  printBoard(board2, x3, y3);
  moves = whereCanPieceMove(board2, x3, y3, isWhite, isKing);
  //print where the piece could move
 // printMoves(moves);


  return 0;
}

*/
