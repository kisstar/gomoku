#include "../include/player.h"

Player::Player(ChessBoard& cb)
  :chess_borad(cb)
{
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

  chess_borad.chessDown(pos, kWhite);
}
