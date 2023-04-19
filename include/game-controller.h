#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "./chess-board.h"
#include "./ai.h"
#include "./player.h"

class GameController
{
public:
  GameController(ChessBoard& chess_board, Ai& ai, Player& player);
  void Play(void);

private:
  bool isAiTurn = false;
  ChessBoard& chess_board;
  Ai& ai;
  Player& player;
};

#endif
