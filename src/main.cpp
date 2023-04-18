#include<iostream>
#include"../include/game-controller.h"

int main(void)
{
  using namespace std;

  const ChessBoard chess_board;
  const Ai ai;
  const Player player(chess_board);

  GameController game_controller(chess_board, ai, player);
  game_controller.Play();

  return 0;
}
