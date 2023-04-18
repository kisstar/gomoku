#include "../include/player.h"

Player::Player(const ChessBoard& chess_borad)
{
  this->chess_borad = chess_borad;
}

void Player::go(void)
{
  ExMessage m;
  ChessPosition pos;

  while (1)
  {
    m = getmessage(EX_MOUSE);

    if (WM_LBUTTONDOWN == m.message && chess_borad.IsValidated(m.x, m.y, pos))
    {
      break;
    }
  }
}
