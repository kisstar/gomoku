#include "../include/ai.h"

Ai::Ai(ChessBoard& cb)
  :chess_board(cb)
{
}

void Ai::ResetScores()
{
  pair<int, int> chess_layout = chess_board.getChessLayout();

  for (int i = 0; i < chess_layout.first; i++)
  {
    vector<int> row;

    for (int j = 0; j < chess_layout.second; j++)
    {
      row.push_back(0);
    }

    scores.push_back(row);
  }
}

void Ai::CalculateQuantity(QuantityParams qp)
{
  pair<int, int> chess_layout = chess_board.getChessLayout();
  int chess_row = chess_layout.first;
  int chess_cell = chess_layout.second;
  int row = qp.row;
  int cell = qp.cell;
  int i = qp.i;
  int j = qp.j;
  PieceType target_type = qp.target_type;

  // 每个方向延申 4 个子
  for (int k = 0; k < 4; k++)
  {
    int current_row = row + k * i;
    int current_cell = cell + k * j;

    if (current_row < 0 || current_row >= chess_row || current_cell < 0 || current_cell >= chess_cell)
    {
      break;
    }

    PieceType  current_type = chess_board.GetChessData(current_row, current_cell);

    if (target_type == current_type)
    {
      break;
    }
    else if (kEmpty == current_type)
    {
      qp.blank_count += 1;
    }
    else {
      qp.chess_count += 1;
    }
  }

  // 每个方向反向的棋子分布情况
  for (int k = 0; k < 4; k++)
  {
    int current_row = row - k * i;
    int current_cell = cell - k * j;

    if (current_row < 0 || current_row >= chess_row || current_cell < 0 || current_cell >= chess_cell)
    {
      break;
    }

    PieceType  current_type = chess_board.GetChessData(current_row, current_cell);

    if (target_type == current_type)
    {
      break;
    }
    else if (kEmpty == current_type)
    {
      qp.blank_count += 1;
    }
    else {
      qp.chess_count += 1;
    }
  }
}

int Ai::GetScore(int chess_count, int blank_count, PieceType type) const
{
  bool isAi = kWhite == type;

  if (0 == chess_count && isAi) {
    return 5;
  }
  if (1 == chess_count)
  {
    return 10;
  }
  if (2 == chess_count)
  {
    if (1 == blank_count)
    {
      return isAi ? 25 : 30;
    }
    if (2 == blank_count)
    {
      return isAi ? 50 : 40;
    }
  }
  if (3 == chess_count)
  {
    if (1 == blank_count)
    {
      return isAi ? 55 : 60;
    }
    if (2 == blank_count)
    {
      return isAi ? 10000 : 5000; // 200 -> 5000
    }
  }
  if (4 == chess_count)
  {
    return isAi ? 30000 : 20000; // 2k -> 2w
  }

  return 0;
}

ChessPosition Ai::FindNextPosition()
{
  pair<int, int> chess_layout = chess_board.getChessLayout();
  int row = chess_layout.first;
  int cell = chess_layout.second;
  vector<ChessPosition> max_scores;
  int max_score = 0;
  int current_score = 0;

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < cell; j++) {
      current_score = scores[i][j];

      if (current_score > max_score)
      {
        max_score = current_score;
        max_scores.clear();
        max_scores.push_back(ChessPosition{ i,j });
      }
      else if (current_score == max_score)
      {
        max_scores.push_back(ChessPosition{ i,j });
      }
    }
  }

  // 随机落子，如果有多个点的话
  int index = rand() % max_scores.size();

  return max_scores[index];
}

void Ai::CalculateScore()
{
  pair<int, int> chess_layout = chess_board.getChessLayout();
  int row = chess_layout.first;
  int cell = chess_layout.second;
  int chess_count = 0;
  int blank_count = 0;

  // 遍历计算所有可落棋点的得分
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < cell; j++)
    {
      PieceType current_type = chess_board.GetChessData(i, j);

      if (kEmpty != current_type)
      {
        continue;
      }

      chess_count = 0;
      blank_count = 0;

      // 一共 4 种方向
      for (int m = -1; m <= 1; m++)
      {
        for (int n = 0; n <= 1; n++)
        {
          if ((0 == m && 0 == n) || (1 == m && 0 == n))
          {
            continue;
          }

          this->CalculateQuantity(QuantityParams{ i, j, m, n, kWhite, blank_count, chess_count });
          int score = this->GetScore(chess_count, blank_count, kBlack);
          scores[i][j] += score;

          // 开始计算白棋的得分
          chess_count = 0;
          blank_count = 0;

          this->CalculateQuantity(QuantityParams{ i, j, m, n, kBlack, blank_count, chess_count });
          score = this->GetScore(chess_count, blank_count, kWhite);
          scores[i][j] += score;
        }
      }
    }
  }
}

void Ai::go(void)
{
  this->ResetScores();
  this->CalculateScore();
  ChessPosition cp = this->FindNextPosition();
  Sleep(1000);
  chess_board.ChessDown(cp, kWhite);
}
