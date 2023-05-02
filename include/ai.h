#ifndef __AI_H__
#define __AI_H__

#include <vector>
#include "./chess-board.h"

using std::vector;

struct QuantityParams
{
  int row;
  int cell;
  int i;
  int j;
  PieceType target_type;
  int& blank_count;
  int& chess_count;
};

class Ai
{
public:
  Ai(ChessBoard& chess_board);
  void ResetScores();
  void CalculateScore();
  void CalculateQuantity(QuantityParams qp);
  int GetScore(int chess_count, int blank_count, PieceType type) const;
  ChessPosition FindNextPosition();
  void go(void);

private:
  ChessBoard& chess_board;
  vector<vector<int>> scores;
};

#endif
