#include "game.h"
#include <iostream>

CheckersBoard::CheckersBoard()
{
  // set entire board to be empty
  for (int i = 0; i < 8; i++)
  {
      for (int j = 0; j < 8; j++)
      {
          Squares[i][j] = Color::none;
      }
  }
  //Then make the rows contain their proper starting pieces
  
}

void CheckersBoard::Display()
{
  std::string board_text = "";
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      // just print square number for now, might change to special character
      switch (Squares[i][j])
      {
        case Color::none:
        {
          board_text += "  ";
          break;
        }
        case Color::black:
        {
          board_text += "⚫ ";
          break;
        }
        case Color::white:
        {
          board_text += "⚪ ";
          break;
        }
    }
    board_text += '\n';
  }
  std::cout << board_text;
}

bool CheckersBoard::TryMove(int x0, int y0, int x1, int y1)
{
    Color colorstart = Squares[x0][y0];
    Color colortry = Squares[x1][y1];
    if (Squares[x0][y0]){
      
    }
    return true; // just return true for now
}

CheckersGame::CheckersGame()
{    
}

void CheckersGame::Play()
{
  int winningPlayer = 0;
  while (winningPlayer == 0)
  {
    // Get move input from player
    std::cout << "Move >";
    std::string playerInput;
    std::cin >> playerInput;
    
  }
}
