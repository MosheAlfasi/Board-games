#include "ChessKingPiece.h"

ChessKingPiece::ChessKingPiece(position data, char player) : ChessPiece(data, player) {}; // Ctor

void ChessKingPiece::operator=(const ChessKingPiece& other) {
	if (this != &other) //Making sure no self copy is done
	{
		ChessPiece::operator=(other); // Copy father
	}
}

ChessKingPiece::ChessKingPiece(const ChessKingPiece& other) // Copy ctor
{
	*this = other;
}

void ChessKingPiece::setLegalMoves(vector<vector<GamePiece*>> board) {

	position move, saver;

	saver = data;

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			{
				move.x = saver.x + i; // Creating a "dummy" move
				move.y = saver.y + j;
				board[saver.x - 1][saver.y - 1] = nullptr;

				if (inRange(move) && (board[move.x - 1][move.y - 1] == nullptr || !isSamePlayer(move, board))) { //Nullptr for empty cell, Is not same player for eating.
					data = move;

					setThreatMoves(board);

					if (threatMoves.empty()) // Making sure the move is not threatening the king
					{
						legalMoves.push_back(move);
					}

					threatMoves.clear();
				}
			}
		}
	data = saver;
	board[data.x - 1][data.y - 1] = this; // Moving King to old position
}

ChessKingPiece::ChessKingPiece(istream& in)
{
	load(in);
}

void ChessKingPiece::save(ostream& out) const
{
	ChessPiece::save(out);
}

void ChessKingPiece::load(istream& in)
{
	ChessPiece::load(in);
}