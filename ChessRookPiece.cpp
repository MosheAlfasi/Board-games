#include "ChessRookPiece.h"

ChessRookPiece::ChessRookPiece(position data, char player) : ChessPiece(data, player) {};

void ChessRookPiece::operator=(const ChessRookPiece& other) {
	if (this != &other)
		ChessPiece::operator=(other);
}

ChessRookPiece::ChessRookPiece(const ChessRookPiece& other)
{
	*this = other;
}
void ChessRookPiece::setLegalMoves(vector<vector<GamePiece*>> board) {

	position move;
	position kingPosition;
	bool validDirection = true;
	bool isDirectionChecked;

	findKingPosition(board, &kingPosition, player <= 'Z' ? 'K' : 'k');      // Checking where the king is

	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j)
		{
			if (abs(i) != abs(j))
			{
				isDirectionChecked = false;
				move.x = data.x + i;
				move.y = data.y + j;

				while (validDirection && inRange(move) && board[move.x - 1][move.y - 1] == nullptr) { // in range && empty place

					if (!isDirectionChecked) {       // moves to this direction are not threat the king

						if (isKingThreatened(kingPosition, data, move, board, this))
							validDirection = false;
						isDirectionChecked = true;
						board[move.x - 1][move.y - 1] = nullptr;
					}
					if (validDirection)
					{
						legalMoves.push_back(move);
						move.x = move.x + i;
						move.y = move.y + j;
					}
				}
				if (validDirection && inRange(move))           // checking capture
				{
					if (!isSamePlayer(move, board) && !isKingThreatened(kingPosition, data, move, board, this))
						legalMoves.push_back(move);
				}
			}
		}
}





ChessRookPiece::ChessRookPiece(istream& in)
{ load(in); }

void ChessRookPiece::save(ostream& out) const
{ ChessPiece::save(out); }

void ChessRookPiece::load(istream& in)
{ ChessPiece::load(in); }