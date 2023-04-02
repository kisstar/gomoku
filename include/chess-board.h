#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

enum ChessType
{
  EMPTY = -1,
  BLACK,
  WHITE
};

class ChessBoard
{
private:
  ChessType chess_type = BLACK;

public:
  bool IsOver();
};

#endif
