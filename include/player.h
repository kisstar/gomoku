#ifndef __Player_H__
#define __Player_H__

#include <graphics.h>
#include "./chess-board.h"

class Player
{
private:
  ChessBoard& chess_borad;

public:
  Player(ChessBoard& chess_borad);
  void go(void);
};

#endif
