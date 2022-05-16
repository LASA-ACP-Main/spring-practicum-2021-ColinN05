#pragma once
#include "stack.h"

enum class Color
{
  none = 0, black = 1, white = 2, gray = 3 // human player is always white
};

enum class PieceState
{
  none = 0, def = 1,king = 2
};

class CheckersBoard
{
public:
	CheckersBoard();

  void Display();

  // tries to move piece at (x0,y0) to (x1,y1) returns true if move could be made and false if not
  bool TryMove(int x0, int y0, int x1, int y1, Color moverc);
  void BotMove();
	Color Squares[8][8]; // 0 = empty square, 1 = black square, 2 = white square
};

class CheckersGame
{
public:
  CheckersGame();
  void UndoMove();
  void Play();
  int PlayerMakeMove();
private:
  CheckersBoard Board;

  Stack boardstack;
};
