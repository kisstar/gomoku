#include "../include/game-controller.h"

GameController::GameController(const ChessBoard& chess_board, const Ai& ai, const Player& player)
{
  this->chess_borad = chess_board;
  this->ai = ai;
  this->player = player;
}

void GameController::Play()
{
  while (chess_borad.IsOver())
  {
    isAiTurn ? ai.go() : player.go();
    isAiTurn = !isAiTurn;
  }
}
