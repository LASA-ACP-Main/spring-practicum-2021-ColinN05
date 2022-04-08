#include "game.h"
#include <iostream>

CheckersBoard::CheckersBoard()
{
    // set entire board to be empty
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Squares[i][j] = 0;
        }
    }
}

void CheckersBoard::Display()
{
    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            // just print square number for now, might change to special character
            std::cout << Squares[i][j] << " ";
        }
        std::cout << '\n';
    }
}

bool CheckersBoard::TryMove(int x0, int y0, int x1, int y1)
{
    // most of the game logic is here
    //...
    return true; // just return true for now
}

CheckersGame::CheckersGame()
{
    // put pieces in starting position
}

void CheckersGame::Play()
{
}