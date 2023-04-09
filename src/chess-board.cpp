#include "../include/chess-board.h"

bool ChessBoard::IsOver()
{
    return false;
}

void ChessBoard::Init()
{
  initgraph(chess_width, chess_height);
  loadimage(NULL, _T("resource/images/chess.jpg"));
  loadimage(&piece_black, _T("resource/images/black.png"), piece_size, piece_size, true);
  loadimage(&piece_white, _T("resource/images/white.png"), piece_size, piece_size, true);

  for (int i = 0; i < chess_size; i++)
  {
    vector<PieceType> row;

    for (int i = 0; i < chess_size; i++)
    {
      row.push_back(kEmpty);
    }

    chesses.push_back(row);
  }
}
