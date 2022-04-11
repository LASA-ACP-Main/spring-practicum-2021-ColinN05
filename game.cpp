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
  // put pieces in starting position
  for (int i = 0; i < 64; i++)
  {
    int ypos = (int)floor(i / 8);
    if (i % 2 == 0 == ypos % 2)
    {
      if (ypos < 3)
      {
        Squares[i % 8][ypos] = Color::black;
      }
      else if (ypos > 4)
      {
        Squares[i % 8][ypos] = Color::white;
      }
    }
  }
  
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
          board_text += "◯  ";
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
    }
    board_text += '\n';
  }
  std::cout << board_text;
}

bool CheckersBoard::TryMove(int x0, int y0, int x1, int y1)
{
    Color colorstart = Squares[x0][y0];
    Color colortry = Squares[x1][y1];
    if (colorstart == Color::white){ //Running if white
      
    } else if (colorstart == Color::black) { //Running if black
      
    } else {
      std::cout<<"Trying to move blank space\n";
      return false;
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
