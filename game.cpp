#include "game.h"
#include <iostream>
#include <math.h>
#include <sstream>
#include "stack.h"
#include <string.h>

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

CheckersBoard::CheckersBoard()
{
  // set entire board to be empty
  for (int i = 0; i < 8; i++)
  {
      for (int j = 0; j < 8; j++)
      {
          Squares[i][j] = Color::none;
          States[i][j] = PieceState::none;
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
        States[i % 8][ypos] = PieceState::def;
      }
      else if (ypos > 4)
      {
        Squares[i % 8][ypos] = Color::white;
        States[i % 8][ypos] = PieceState::def;
      }
    }
  }
}

	void CheckersBoard::Display()
{
  std::string board_text = "";
  for (int j = 0; j < 8; j++)
  {
    board_text += std::to_string(j);
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
        case Color::gray:
        {
          board_text += "🟠";
        }
      }
    }
    board_text += '\n';
  }
  board_text += "  0 1 2 3 4 5 6 7\n";
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
  
    if (colorstart == Color::white) //Running if white
    { 
      if (dy > 0 && States[x0][y0] != PieceState::king) return false; // if not king and moving down board
      if (abs(dy) == 1 && abs(dx) == 1)
      {
        PieceState saveState = States[x0][y0];
        States[x0][y0] = PieceState::none;
        States[x1][y1] = saveState;
        Squares[x0][y0] = Color::none;
        Squares[x1][y1] = Color::white;
        if (y1 == 0) States[x1][y1] = PieceState::king;
        return true;
      } 
      else if (abs(dy) == 2 && Squares[x0 + dx/2][y0 + dy/2] == Color::black)// capture check
      {
        PieceState saveState = States[x0][y0];
        States[x0][y0] = PieceState::none;
        States[x1][y1] = saveState;
        Squares[x1][y1] = Color::white;
        Squares[x0][y0] = Color::none;
        Squares[x0 + dx/2][y0 + dy/2] = Color::none; 
        if (y1 == 0) States[x1][y1] = PieceState::king;
        return true;// capture the piece jumped over
      }
    } 
    else if (colorstart == Color::black) 
    { //Running if black
      if (dy < 0 && States[x0][y0] != PieceState::king) return false; // if not king and moving up board
      if (abs(dy) == 1 && abs(dx) == 1)
      {
        PieceState saveState = States[x0][y0];
        States[x0][y0] = PieceState::none;
        States[x1][y1] = saveState;
        Squares[x0][y0] = Color::none;
        Squares[x1][y1] = Color::black;
        if (y1 == 7) States[x1][y1] = PieceState::king;
        return true;
      }  
      else if (abs(dy) == 2 && Squares[x0 + dx/2][y1 + dy/2] == Color::white)// capture check
      {
        PieceState saveState = States[x0][y0];
        States[x0][y0] = PieceState::none;
        States[x1][y1] = saveState;
        Squares[x1][y1] = Color::black;
        Squares[x0][y0] = Color::none;
        Squares[x0 + dx/2][y0 + dy/2] = Color::none; // capture the piece jumped over
        if (y1 == 7) States[x1][y1] = PieceState::king;
        return true;
      }
    } 
    else 
    {
      if (colorstart != moverc && colorstart == Color::none)
      {
        //std::cout<<"Trying to move wrong team\n";
      } else if (colorstart == Color::none)
      {
        //std::cout<<"Trying to move blank space\n";
      }
      return false;
    }
  return false; 
}

CheckersGame::CheckersGame()
{
  CheckersBoard* currBoard = new CheckersBoard();
  *currBoard = Board;
  boardstack.push(currBoard);
//boardstack.ShowBoards();
}

void CheckersGame::Play()
{
  Color winningPlayer = Color::none;
  CheckersBoard* currBoard;
  while (winningPlayer == Color::none)
  { 
    system("clear");
    std::cout << boardstack.length << '\n';
    Board.Display();
    GameNode n(&Board);
    std::cout << "Current Score: "<< n.EvaluateScore() << '\n';
    
    int playerMove = PlayerMakeMove(); // this will ask player to make move until they have made valid move
    if (playerMove != 1)
    {
      Board.BotMove();
      CheckersBoard* currBoard = new CheckersBoard();
      *currBoard = Board;
      boardstack.push(currBoard);
    }
  }
}

void CheckersGame::UndoMove(){
  if (boardstack.pTop){
    boardstack.pop();
    if (boardstack.pTop)
    {
      Board = *(boardstack.pTop->data);
    }
  }
}

int CheckersGame::PlayerMakeMove()
{
/*
   bool hasMadeValidMove = false;
    while (!hasMadeValidMove)
    {
      // read player input
      std::cout << "Move >";
      std::string playerInput;
      std::getline(std::cin, playerInput);

      if (playerInput == "u")
      {
        UndoMove();
        hasMadeValidMove = true;
        return 1;
      }
      else
      {
      
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
        if (hasMadeValidMove)
        {
          return 0;
        }
        else
        {
          std::cout << "Invalid move!\n";
          //std::cin.get(); // press enter to continue
        }
      }
    }
  return -1;
*/

  
  // FOR TESTING: Make white player make random moves
  bool hasMadeValidMove = false;
  while (!hasMadeValidMove)
  {
    // Generate random TryMove coords
    int tx0 = rand() % 8;
    int ty0 = rand() % 8;
    int tx1 = rand() % 8;
    int ty1 = rand() % 8;
    hasMadeValidMove = Board.TryMove(tx0, ty0, tx1, ty1, Color::white);
  }
  return 0;
  
}
