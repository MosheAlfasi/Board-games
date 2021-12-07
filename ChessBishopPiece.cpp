#include "ChessBishopPiece.h"

ChessBishopPiece::ChessBishopPiece(position data, char player) : ChessPiece(data, player) {}; // Ctor

void ChessBishopPiece::operator=(const ChessBishopPiece& other) {
	if (this != &other) // Checking whether a self copy was done
	{
		ChessPiece::operator=(other); // Father copy
	}
}

ChessBishopPiece::ChessBishopPiece(const ChessBishopPiece& other) // Copy ctor
{
	*this = other;
}

void ChessBishopPiece::setLegalMoves(vector<vector<GamePiece*>> board) {

	position move;
	position kingPosition;
	bool validDirection = true;
	bool isDirectionChecked;

	findKingPosition(board, &kingPosition, player <= 'Z' ? 'K' : 'k');

	for (int i = -1; i <= 1; i += 2)      // When we add 2 to i/j, we make sure there are no straight lines.
		for (int j = -1; j <= 1; j += 2)
		{
			isDirectionChecked = false; // Checking only one cell in each direction (if the direction is ok, no need to check the whole line)
			move.x = data.x + i;
			move.y = data.y + j;


			while (validDirection && inRange(move) && board[move.x - 1][move.y - 1] == nullptr) {

				if (!isDirectionChecked) {
					if (isKingThreatened(kingPosition, data, move, board, this)) // If moving in the direction exposes the king, it is invalid!
						validDirection = false;
					isDirectionChecked = true;
				}
				if (validDirection)
				{
					legalMoves.push_back(move); // Only if all conditions are met, add to legal moves
					move.x = move.x + i; // Create a new move
					move.y = move.y + j;
				}
			}
			if (validDirection && inRange(move))
				if (!isSamePlayer(move, board) && !isKingThreatened(kingPosition, data, move, board, this))
					legalMoves.push_back(move); // Only if all conditions are met, add to legal moves
		}
}


ChessBishopPiece::ChessBishopPiece(istream& in)
{
	load(in);
}

void ChessBishopPiece::save(ostream& out) const
{
	ChessPiece::save(out);
}

void ChessBishopPiece::load(istream& in)
{
	ChessPiece::load(in);
}