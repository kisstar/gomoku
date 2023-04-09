#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

#include<vector>
#include <graphics.h>
#include <conio.h>

using std::vector;

enum PieceType
{
  kEmpty, // 未落棋
  kBlack, // 黑棋
  kWhite
};

class ChessBoard
{
private:
  int chess_width = 897; // 棋盘的宽度
  int chess_height = 895;
  int chess_size = 13; // 棋盘的大小: 13x13
  float piece_size = 67.4; // 棋子的大小: 67.4x67.4

  PieceType piece_type = kBlack; // 下一步落棋的类型
  vector<vector<PieceType>> chesses;
  IMAGE piece_black, piece_white; // 棋子

public:
  bool IsOver();
  void Init();
};

#endif
