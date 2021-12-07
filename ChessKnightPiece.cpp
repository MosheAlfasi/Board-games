#include "ChessKnightPiece.h"

ChessKnightPiece::ChessKnightPiece(position data, char player) : ChessPiece(data, player) {};

void ChessKnightPiece::operator=(const ChessKnightPiece& other) {
	if (this != &other) // Making sure no self copy is done
	{
		ChessPiece::operator=(other); // Copy father
	}
}

ChessKnightPiece::ChessKnightPiece(const ChessKnightPiece& other) // Copy ctor
{
	*this = other;
}

void ChessKnightPiece::setLegalMoves(vector<vector<GamePiece*>> board) {

	position move;
	position kingPosition;

	findKingPosition(board, &kingPosition, player <= 'Z' ? 'K' : 'k');

	for (int i = -2; i <= 2; ++i, (i == 0 ? ++i : true))            // Checking all knight directions
		for (int j = -2; j <= 2; ++j, (j == 0 ? ++j : true))
		{
			if (abs(i) != abs(j))                           // Can't move diagonally
			{
				move.x = data.x + i;
				move.y = data.y + j;

				if (inRange(move) && (!isSamePlayer(move, board) || board[move.x - 1][move.y - 1] == nullptr))
					if (!isKingThreatened(kingPosition, data, move, board, this)) // Making sure king is not threatened if the move is made
						legalMoves.push_back(move); // Only if all conditions are met, add to legal moves
			}
		}
}

ChessKnightPiece::ChessKnightPiece(istream& in)
{
	load(in);
}

void ChessKnightPiece::save(ostream& out) const
{
	ChessPiece::save(out);
}

void ChessKnightPiece::load(istream& in)
{
	ChessPiece::load(in);
}