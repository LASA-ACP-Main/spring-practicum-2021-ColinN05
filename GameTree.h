#pragma once
#include "game.h"
#include <vector>

struct GameNode
{
public:
  GameNode(CheckersBoard* board);
  ~GameNode();
  void Free(int depth = 0);
  CheckersBoard* Board;
  std::vector<GameNode*> Branches;
  //int MinimaxScore(Color );
  void FillTree(CheckersBoard* startBoard, Color startColor,int depth = 0);
  float EvaluateScore();

  const static int maxdepth = 4;
  GameNode* ptop;
  float MiniMax(GameNode* node, int depth, Color player, float alpha = -999.0f, float beta = 999.0f);
  Color isTerminal(CheckersBoard* board); // returns winning player color

  GameNode* GetBestMove();
  GameNode* BestPotentialMove(GameNode* node, int depth, Color player);
  GameNode* BestAverageMove(GameNode* node, int depth, Color player);
  float AverageScore(GameNode* node, int depth);
};
