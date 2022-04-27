#include "game.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include "stack.h"

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

      
      switch (Squares[i][j])
      {
        case Color::none:
        {
          board_text += "⭕";
          break;
        }
        case Color::black:
        {
          board_text += "⚫";
          break;
        }
        case Color::white:
        {
          board_text += "⚪";
          break;
        }
      }
    }
    board_text += '\n';
  }
  std::cout << board_text;
}

bool CheckersBoard::TryMove(int x0, int y0, int x1, int y1, Color moverc)
{
    Color colorstart = Squares[x0][y0];
    Color colortry = Squares[x1][y1];
    if (colortry != Color::none){
      //std::cout<<"Trying to move to occupied space\n";
      return false;
    }
    if (colorstart != moverc) 
    {
      //std::cout<<"Trying to move wrong team\n";
      return false;
    }

    if (colorstart == Color::none){
        //std::cout<<"Trying to move blank space\n";
        return false;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    if (abs(dx) != abs(dy))
    {
      //std::cout << "Not moving along diagonal.\n";
      return false; 
    }
  
    if (colorstart == Color::white){ //Running if white
      if (y1 == y0 - 1 && (x1 == x0 - 1 || x1 == x0 + 1)){
        Squares[x0][y0] = Color::none;
        Squares[x1][y1] = Color::white;
        return true;
        } else if (y1 == y0 - 2 && Squares[x0 + dx/2][y1 + dy/2] == Color::black)// capture check
      {
        Squares[x1][y1] = Color::white;
        Squares[x0][y0] = Color::none;
        Squares[x0 + dx/2][y0 + dy/2] = Color::none; 
        return true;// capture the piece jumped over
      }
    } else if (colorstart == Color::black) { //Running if black
      if (y1 == y0 + 1 && (x1 == x0 - 1 || x1 == x0 + 1)){
        Squares[x0][y0] = Color::none;
        Squares[x1][y1] = Color::black;
        return true;
      }  else if (y1 == y0 + 2 && Squares[x0 - dx/2][y1 - dy/2] == Color::white)// capture check
      {
        Squares[x1][y1] = Color::black;
        Squares[x0][y0] = Color::none;
        Squares[x0 + dx/2][y0 + dy/2] = Color::none; // capture the piece jumped over
        return true;
      }
        
      //}
    } else {
      if (colorstart != moverc && colorstart == Color::none){
        std::cout<<"Trying to move wrong team\n";
      } else if (colorstart == Color::none){
        std::cout<<"Trying to move blank space\n";
      } else {
        std::cout<<"what\n";
      }
      return false;
    }
  std::cout<<"Dude something has gone terribly wrong in TryMove OR you're trying to do a very bad move\n"; 
  return false; 
}

void CheckersBoard::BotMove()
{
  int x0, y0, x1, y1;
  // find coords for best move
  // . . .

  bool hasMadeValidMove = false;
  while (!hasMadeValidMove)
  {
    // Generate random TryMove coords
    int tx0 = rand() % 8;
    int ty0 = rand() % 8;
    int tx1 = rand() % 8;
    int ty1 = rand() % 8;
    hasMadeValidMove = TryMove(tx0, ty0, tx1, ty1, Color::black);
  }
  
  //TryMove(x0, y0, x1, y1, Color::black);
}

CheckersGame::CheckersGame()
{    
}

void CheckersGame::Play()
{
  Color winningPlayer = Color::none;
  Stack boardstack = Stack();
  CheckersBoard* currBoard;
  while (winningPlayer == Color::none)
  { 
    Board.Display();
    
    PlayerMakeMove(); // this will ask player to make move until they have made valid move
    currBoard = new CheckersBoard();
    *currBoard = Board;
    boardstack.push(currBoard);
    //Board.Display();

    std::cin.get(); // press enter to continue
    
    Board.BotMove();
    currBoard = new CheckersBoard();
    *currBoard = Board;
    boardstack.push(currBoard);
  }
}

void CheckersGame::PlayerMakeMove()
{
   bool hasMadeValidMove = false;
    while (!hasMadeValidMove)
    {
      // read player input
      std::cout << "Move >";
      char playerInput[25];
      std::cin.get(playerInput, 25);
      
      // get coords from input string
      std::string x0s, y0s, x1s, y1s;
      int x0, y0, x1, y1;
      std::stringstream inputStream(playerInput);
      std::getline(inputStream, x0s, ' ');
      std::getline(inputStream, y0s, ' ');
      std::getline(inputStream, x1s, ' ');
      std::getline(inputStream, y1s, '\0');
      x0 = stoi(x0s); y0 = stoi(y0s); x1 = stoi(x1s); y1 = stoi(y1s);
      hasMadeValidMove = Board.TryMove(x0, y0, x1, y1, Color::white); // try move from input
      if (!hasMadeValidMove) 
      {
        std::cout << "Invalid move!\n";
        std::cin.get(); // press enter to continue
      }
    }

    //Board.Display();
}
