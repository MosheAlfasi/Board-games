#include "ChessQueenPiece.h"

ChessQueenPiece::ChessQueenPiece(position data, char player) : ChessPiece(data, player) {};

void ChessQueenPiece::operator=(const ChessQueenPiece& other) {
	if (this != &other)
		ChessPiece::operator=(other);
}

ChessQueenPiece::ChessQueenPiece(const ChessQueenPiece& other)
{
	*this = other;
}

void ChessQueenPiece::setLegalMoves(vector<vector<GamePiece*>> board) {

	position move;
	position kingPosition;
	bool validDirection = true;
	bool isDirectionChecked;

	findKingPosition(board, &kingPosition, player <= 'Z' ? 'K' : 'k'); // Checking where the king is

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			{
				isDirectionChecked = false;
				move.x = data.x + i;
				move.y = data.y + j;

				while (validDirection && inRange(move) && board[move.x - 1][move.y - 1] == nullptr) {  // in range && empty place

					if (!isDirectionChecked) {
						if (isKingThreatened(kingPosition, data, move, board, this))
							validDirection = false;
						isDirectionChecked = true;
					}
					if (validDirection)    // moves to this direction are not threat the king
					{
						legalMoves.push_back(move);
						move.x = move.x + i;
						move.y = move.y + j;
					}
				}
				if (validDirection && inRange(move))          // checking capture
					if (!isSamePlayer(move, board) && !(isKingThreatened(kingPosition, data, move, board, this)))
						legalMoves.push_back(move);
			}
		}
}

ChessQueenPiece::ChessQueenPiece(istream& in)
{
	load(in);
}

void ChessQueenPiece::save(ostream& out) const
{
	ChessPiece::save(out);
}

void ChessQueenPiece::load(istream& in)
{
	ChessPiece::load(in);
}