#include "../include/game-controller.h"

GameController::GameController(ChessBoard& cb, Ai& comp, Player& user)
  :chess_board(cb), ai(comp), player(user)
{
}

void GameController::Play()
{
  chess_board.Init();

  do
  {
    isAiTurn ? ai.go() : player.go();
    isAiTurn = !isAiTurn;
  } while (!chess_board.IsOver());
}
