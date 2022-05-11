#pragma once
#include "game.h"
#include <vector>

struct GameNode
{
public:
  GameNode(CheckersBoard* board);
  CheckersBoard* Board;
  std::vector<GameNode*> Branches;
  //int MinimaxScore(Color );
  void FillTree(CheckersBoard* startBoard, Color startColor,int depth = 0);
};

class GameTree
{
public:
  GameTree();
  static int maxdepth = 5;
  GameNode* ptop;
  int MiniMax(CheckersBoard board, int depth, bool isMaxPlayer);
  bool isTerminal(CheckersBoard board);
private:

};
