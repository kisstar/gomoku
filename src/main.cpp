#include<iostream>
#include"../include/game-controller.h"

int main(void)
{
  using namespace std;

  ChessBoard chess_board;
  Ai ai(chess_board);
  Player player(chess_board);

  GameController game_controller(chess_board, ai, player);
  game_controller.Play();

  return 0;
}
