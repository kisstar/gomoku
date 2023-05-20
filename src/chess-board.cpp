#include "../include/chess-board.h"

pair<int, int> ChessBoard::getChessLayout()
{
  return pair<int, int>(chess_row, chess_cell);
}

bool ChessBoard::IsOver()
{
  if (this->IsWin()) {
    Sleep(1500);

    if (kBlack == last_chess.type) {
      loadimage(NULL, _T("resource/images/success.jpg"));
    }
    else {
      loadimage(NULL, _T("resource/images/fail.jpg"));
    }

    _getch();
    return true;
  }

  return false;
}

bool ChessBoard::IsWin()
{
  PieceType target_type = last_chess.type;
  int row = last_chess.pos.row;
  int cell = last_chess.pos.col;
  int chess_count = 1;

  for (int i = -1; i <= 1; i++)
  {
    for (int j = 0; j <= 1; j++)
    {
      if ((0 == i && 0 == j) || (1 == i && 0 == j))
      {
        continue;
      }

      // 每个方向延申 4 个子
      for (int k = 1; k <= 4; k++)
      {
        int current_row = row + k * j;
        int current_cell = cell + k * i;

        if (current_row < 0 || current_row >= chess_row || current_cell < 0 || current_cell >= chess_cell)
        {
          break;
        }

        PieceType current_type = this->GetChessData(current_row, current_cell);

        if (target_type == current_type)
        {
          chess_count += 1;
        }
        else {
          break;
        }
      }

      // 每个方向反向的棋子分布情况
      for (int k = 1; k <= 4; k++)
      {
        int current_row = row - k * j;
        int current_cell = cell - k * i;

        if (current_row < 0 || current_row >= chess_row || current_cell < 0 || current_cell >= chess_cell)
        {
          break;
        }

        PieceType current_type = this->GetChessData(current_row, current_cell);

        if (target_type == current_type)
        {
          chess_count += 1;
        }
        else {
          break;
        }
      }
    }
  }

  return 5 == chess_count;
}

void ChessBoard::Init()
{
  initgraph(chess_width, chess_height);
  loadimage(NULL, _T("resource/images/chess.jpg"));
  loadimage(&piece_black, _T("resource/images/black.png"), piece_size, piece_size, true);
  loadimage(&piece_white, _T("resource/images/white.png"), piece_size, piece_size, true);

  for (int i = 0; i < chess_row; i++)
  {
    vector<PieceType> row;

    for (int i = 0; i < chess_cell; i++)
    {
      row.push_back(kEmpty);
    }

    chesses.push_back(row);
  }
}

bool ChessBoard::IsValidated(short x, short y, ChessPosition& pos)
{
  bool isValidated = false;
  int distance;

  int row = (y - margin_top) / chess_cell_height; // 点击处在第几行下
  int col = (x - margin_left) / chess_cell_width;
  int leftTopX = margin_left + chess_cell_width * col; // 点击点所属格左上角
  int leftTopY = margin_top + chess_cell_height * row;

  do
  {
    // 距离左上角的距离
    distance = sqrt(pow(x - leftTopX, 2) + pow(y - leftTopY, 2));

    if (distance < offset && chesses[row][col] == kEmpty)
    {
      pos.row = row;
      pos.col = col;
      isValidated = true;
      break;
    }

    // 距离右上角的距离
    distance = sqrt(pow(x + chess_cell_width - leftTopX, 2) + pow(y - leftTopY, 2));

    if (distance < offset && chesses[row][col + 1] == kEmpty)
    {
      pos.row = row;
      pos.col = col + 1;
      isValidated = true;
      break;
    }

    // 距离左下角的距离
    distance = sqrt(pow(x - leftTopX, 2) + pow(y + chess_cell_height - leftTopY, 2));

    if (distance < offset && chesses[row + 1][col] == kEmpty)
    {
      pos.row = row + 1;
      pos.col = col;
      isValidated = true;
      break;
    }

    // 距离右下角的距离
    distance = sqrt(pow(x + chess_cell_width - leftTopX, 2) + pow(y + chess_cell_height - leftTopY, 2));

    if (distance < offset && chesses[row + 1][col + 1] == kEmpty)
    {
      pos.row = row + 1;
      pos.col = col + 1;
      isValidated = true;
      break;
    }
  } while (0);

  return isValidated;
}

void ChessBoard::ChessDown(ChessPosition& pos, PieceType type)
{
  int x = margin_left + (pos.col - 0.5) * chess_cell_width;
  int y = margin_top + (pos.row - 0.5) * chess_cell_height;
  IMAGE piece = type == kWhite ? piece_white : piece_black;

  putimage(x, y, &piece);
  this->UpdateChess(pos, type);
  this->UpdateLastPosition(pos, type);
}

PieceType ChessBoard::GetChessData(int row, int cell)
{
  return this->chesses[row][cell];
}

void ChessBoard::UpdateChess(ChessPosition& pos, PieceType type)
{
  chesses[pos.row][pos.col] = type;
}

void ChessBoard::UpdateLastPosition(ChessPosition& pos, PieceType type)
{
  last_chess.pos.row = pos.row;
  last_chess.pos.col = pos.col;
  last_chess.type = type;
}
