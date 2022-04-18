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
      if (colortry == Color::none && y1 == y0 - 1 && (x1 == x0 - 1 || x1 == x0 + 1)){
        Squares[x0][y0] = Color::none;
        Squares[x1][y1] = Color::white;
        return true;
      }
    } else if (colorstart == Color::black) { //Running if black
      if (colortry == Color::none && y1 == y0 + 1 && (x1 == x0 - 1 || x1 == x0 + 1)){
        Squares[x0][y0] = Color::none;
        Squares[x1][y1] = Color::black;
        return true;
      }
    } else {
      std::cout<<"Trying to move blank space\n";
      return false;
    }
  std::cout<<"Dude something has gone terribly wrong in TryMove"; 
  return true; 
}

CheckersGame::CheckersGame()
{    
}

void CheckersGame::Play()
{
  Color winningPlayer = Color::none;
  while (winningPlayer == Color::none)
  {
    // Get move input from player
    std::cout << "Move >\n";
    std::string playerInput;
    Board.Display();
    std::cin >> playerInput;
    std::string x0s, y0s, x1s, y1s;
    int x0, y0, x1, y1;
    //std::istream inputStream(playerInput);
    std::stringstream inputStream(playerInput);
    std::getline(inputStream, x0s, ' ');
    std::getline(inputStream, y0s, ' ');
    std::getline(inputStream, x1s, ' ');
    std::getline(inputStream, y1s, ' ');
    x0 = stoi(x0s); y0 = stoi(y0s); x1 = stoi(x1s); y1 = stoi(y1s);
    Board.TryMove(x0, y0, x1, y1);
  }
}
