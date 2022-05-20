#include "GameTree.h"
#include <math.h>
#include <iostream>

GameNode::GameNode(CheckersBoard* board)
  : Board(board)
{
}

GameNode::~GameNode()
{
}

float GameNode::EvaluateScore()
{
  int black_count = 0, white_count = 0;
  int black_kings = 0, white_kings = 0;
  int black_pos_sum = 0, white_pos_sum = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (Board->Squares[i][j] == Color::black)
      {
        ++black_count;
        if (Board->States[i][j] == PieceState::king) ++black_kings;
        black_pos_sum += 7 - j;
      }
      else if (Board->Squares[i][j] == Color::white)
      {
        ++white_count;
        if (Board->States[i][j] == PieceState::king) ++white_kings;
        white_pos_sum += j;
      }
    }
  }
  
  //std::cout << "WhiteCount" <<white_count << '\n';
  //std::cout << "BlackCount" <<black_count << '\n';
  //std::cout << "Eval score: " << 0.75f * (black_count - white_count) + 0.25f * (12.0f - white_count) << '\n';
  float weights[] = { 0.75f, 0.125f, 0.125f };
  return weights[0] * (black_count - white_count) * 2.0f / (black_count + white_count)+ weights[1] * (black_kings - white_kings) / 12.0f + weights[2] * (black_pos_sum - white_pos_sum) / 72.0f;
}

void GameNode::Free(int depth)
{
  // Recursively free all nodes created by FillTree
  for (GameNode* subnode : Branches)
  {
    if (subnode)
    {
      subnode->Free(depth + 1);
    }
  }
  Branches.clear();
  if (depth != 0)
  {
    delete Board;
  }
}

int pieces (CheckersBoard* board, Color color){
  int count = 0;
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0;  i < 8; i++)
    {
      if (board->Squares[i][j] == color)
      {
        ++count;
      }
    }
  }
  return count;
}

float max (float one, float two){
  if (one>=two)
    return one;
  else 
    return two;
}

float min(float one, float two)
{
  if (one<=two)
    return one;
  else 
    return two;
}

void GameNode::FillTree(CheckersBoard* startBoard, Color startColor, int depth)
{
  if (depth > maxdepth) return;
  
  int x0, y0, x1, y1;
  CheckersBoard* addBoard;
  CheckersBoard* testBoard = new CheckersBoard();
  *testBoard = *startBoard;
  
  for (int i = 0; i < 64; i++)
  {
    for (int j = 0; j < 64; j++)
    {
      x0 = i % 8;
      y0 = (int)floor(i / 8);
      x1 = j % 8;
      y1 = (int)floor(j / 8);
      
      if (testBoard->TryMove(x0, y0, x1, y1, startColor)) // if move is valid
      {
        addBoard = new CheckersBoard();
        *addBoard = *testBoard; // add board gets set to state of startBoard after move is made
        GameNode* addNode = new GameNode(addBoard);
        Branches.push_back(addNode);
        *testBoard = *startBoard; // reset test board
      }
    }
  }
  for (GameNode* gameNode : Branches)
  {
    Color nextColor;
    if (startColor == Color::black) {nextColor = Color::white;}
    else {nextColor = Color::black;}
    gameNode->FillTree(gameNode->Board, nextColor, depth + 1);    
  }

  delete testBoard;
}
//MAKE SCORE EVALUATION EQUAL BLACKPIECES-WHITEPIECES

// Returns best move (for black player)
GameNode* GameNode::GetBestMove()
{
  GameNode* bestMove = Branches[0];
  if (!bestMove) return this;
  float bestMoveScore = MiniMax(bestMove, 1, Color::white);
  for (GameNode* move : Branches)
  {
    float score = MiniMax(move, 1, Color::white);
    if (score > bestMoveScore)
    {
      bestMove = move;
      bestMoveScore = score;
    }
  }
  //std::cout << "BestMoveScore: " << bestMoveScore << '\n';
  return bestMove;
}

float GameNode::MiniMax(GameNode* node, int depth, Color player, float alpha, float beta)
{
  // Black is maximizing player, white is minimizing
  Color winningPlayer = Color::none;
  //Color winningPlayer = isTerminal(node->Board);
  if (winningPlayer != Color::none)
  {
    return node->EvaluateScore();
  }

  if (depth == maxdepth)
  {
    return node->EvaluateScore();
  }
  
  if (player == Color::black)
  {
    float value = -999.0f;
    for (GameNode* move : node->Branches)
    {
      value = max(value, MiniMax(move, depth + 1, Color::white, alpha, beta));
      if (value >= beta)
          break;
      alpha = max(alpha, value);
    }
    return value;
  }
  else
  {
    float value = 999.0f;
    for (GameNode* move : node->Branches)
    {
      value = min(value, MiniMax(move, depth + 1, Color::black));
      if (value <= alpha)
        break;
      beta = min(beta, value);
    }
    return value;
  }
}

GameNode* GameNode::BestPotentialMove(GameNode* node, int depth, Color player)
{
  if (depth == maxdepth)
  {
    return node;
  }

  float bestPotentialMoveScore = node->EvaluateScore();
  GameNode* bestPotentialMove = node;
  if (Branches[0])
  {
    bestPotentialMove = Branches[0];
    bestPotentialMoveScore = Branches[0]->EvaluateScore();
  }
  if (player == Color::black)
  {
    for (GameNode* move : node->Branches)
    {
      float currScore = BestPotentialMove(move, depth + 1, Color::black)->EvaluateScore();
      if (currScore > bestPotentialMoveScore)
      {
        bestPotentialMoveScore = currScore;
        bestPotentialMove = move;
      }
    }
  }
  else if (player == Color::white)
  {
    for (GameNode* move : node->Branches)
    {
      float currScore = BestPotentialMove(move, depth + 1, Color::white)->EvaluateScore();
      if (currScore < bestPotentialMoveScore)
      {
        bestPotentialMoveScore = currScore;
        bestPotentialMove = move;
      }
    }
  }
  return bestPotentialMove;
}

GameNode* GameNode::BestAverageMove(GameNode* node, int depth, Color player)
{
  return nullptr;
}

float GameNode::AverageScore(GameNode* node, int depth)
{
  
}




Color GameNode::isTerminal(CheckersBoard* board)
{
  if (pieces(board, Color::white) == 0) return Color::black;
  if (pieces(board, Color::black) == 0) return Color::white;

  // Count legal moves for black and white
  int legalMovesBlack = 0, legalMovesWhite = 0;
  int x0, y0, x1, y1;
  CheckersBoard* blackTestBoard = new CheckersBoard();
  CheckersBoard* whiteTestBoard = new CheckersBoard();
  for (int i = 0; i < 64; i++)
  {
    for (int j = 0; j < 64; j++)
    {
      x0 = i % 8;
      y0 = (int)floor(i / 8);
      x1 = j % 8;
      y1 = (int)floor(j / 8);

      *blackTestBoard = *board;
      *whiteTestBoard = *board;
      if (blackTestBoard->TryMove(x0, y0, x1, y1, Color::black))
      {
        ++legalMovesBlack;
      }
      if (whiteTestBoard->TryMove(x0, y0, x1, y1, Color::white))
      {
        ++legalMovesWhite;
      }
    }
  }
  delete blackTestBoard;
  delete whiteTestBoard;
  if (legalMovesBlack == 0) return Color::white;
  if (legalMovesWhite == 0) return Color::black;
  return Color::none;
}
