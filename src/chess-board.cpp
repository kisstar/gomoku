#include "../include/chess-board.h"

pair<int, int> ChessBoard::getChessLayout()
{
  return pair<int, int>(chess_row, chess_cell);
}

bool ChessBoard::IsOver()
{
  return false;
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
}

PieceType ChessBoard::GetChessData(int row, int cell)
{
  return this->chesses[row][cell];
}
