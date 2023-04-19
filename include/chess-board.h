#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

#include <vector>
#include <cmath>
#include <graphics.h>
#include <conio.h>

using std::vector;

enum PieceType
{
  kEmpty, // 未落棋
  kBlack, // 黑棋
  kWhite
};

struct ChessPosition
{
  int row;
  int col;
};

class ChessBoard
{
private:
  int chess_width = 897; // 棋盘的宽度
  int chess_height = 895;
  int margin_left = 44; // 棋盘左边界距离左边第一列棋格的距离
  int margin_top = 43;
  int chess_row = 13; // 棋盘的行数
  int chess_cell = 13;
  int chess_cell_width = 72; // 格子的宽度
  int chess_cell_height = 72;
  int piece_size = 67; // 棋子的大小: 67x67
  int offset = piece_size * 0.4; // 点击允许的误差范围

  vector<vector<PieceType>> chesses;
  IMAGE piece_black, piece_white; // 棋子

public:
  bool IsOver();
  void Init();
  bool IsValidated(short x, short y, ChessPosition& pos);
  void chessDown(ChessPosition& pos, PieceType type);
};

#endif
