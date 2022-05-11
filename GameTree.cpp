#include "GameTree.h"
#include <math.h>

GameNode::GameNode(CheckersBoard* board)
  : Board(board)
{
}

GameTree::GameTree()
{
  //ptop = game
}

void GameNode::FillTree(CheckersBoard* startBoard, Color startColor, int depth)
{
  int x0, y0, x1, y1;
  CheckersBoard* addBoard = startBoard;
  if (depth > GameTree::maxdepth) return;
  for (int i = 0; i < 64; i++)
  {
    for (int j = 0; j < 64; j++)
    {
      x0 = i % 8;
      y0 = (int)floor(i / 8);
      x1 = j % 8;
      y1 = (int)floor(j / 8);
      if (startBoard->TryMove(x0, y0, x1, y1, startColor))
      {
        
      }
    }
  }
}
//MAKE SCORE EVALUATION EQUAL BLACKPIECES-WHITEPIECES

int GameTree::MiniMax(CheckersBoard board, int depth, bool isMaxPlayer){
  if(isTerminal(board)){
    return 
  }
}

int pieces (CheckersBoard board, Color color){
  int black;
  int white;
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      if (board.Squares[i][j] == Color::white){
        white++;
      } else if (board.Squares[i][j] == Color::black){
        black++;
      }
    }
  }
  if (color == Color::white){
    return white;
  } else if (color == Color::black){
    return black;
  } else {
    return -1;
  }
}

bool GameTree::isTerminal(CheckersBoard board){
  if (pieces(board, Color::white) == 0 || pieces(board, Color::black) == 0){
    return true;
  }
  return false;
}
