#include "AmazonsPiece.h"



AmazonsPiece::AmazonsPiece(position data, char player) : GamePiece(data, player) {}; // Ctor

AmazonsPiece::AmazonsPiece(istream& in)
{
	load(in);
}

AmazonsPiece::AmazonsPiece(const AmazonsPiece& other) { // Copy ctor
	*this = other;
}

void AmazonsPiece::operator=(const AmazonsPiece& other) {
	if (this != &other) // Making sure no self copy is made
	{
		GamePiece::operator=(other);
		legalMoves = other.getLegalMoves();
	}
}

void AmazonsPiece::setLegalMoves(vector<vector<GamePiece*>> board) {
	int direction;
	position move;

	legalMoves.clear();

	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0) // Covering all directions besides staying at place
			{
				move.x = data.x + i;
				move.y = data.y + j;

				while ((inRange(move)) && board[move.x - 1][move.y - 1]->getPlayer() == '0')
				{
					legalMoves.push_back(move);
					move.x = move.x + i;
					move.y = move.y + j;
				}
			}
		}
}

bool AmazonsPiece::inRange(position move)
{
	if (move.x > 0 && move.x <= 10 && move.y > 0 && move.y <= 10)
		return true;
	return false;
}

void AmazonsPiece::printLegalMoves() const
{
	printPositionList(legalMoves);
}

const list<position>& AmazonsPiece::getLegalMoves() const
{
	return legalMoves;
}

list<position>& AmazonsPiece::getLegalMoves()
{
	return legalMoves;
}

const list<position>& AmazonsPiece::getThreatMoves() const
{
	return legalMoves;
}

list<position>& AmazonsPiece::getThreatMoves()
{
	return legalMoves;
}

const char AmazonsPiece::getColor() const {
	return player;
}

void AmazonsPiece::printThreatMoves() const
{
	printPositionList(legalMoves);
}

void AmazonsPiece::save(ostream& out) const
{
	GamePiece::save(out);
}
void AmazonsPiece::load(istream& in)
{
	GamePiece::load(in);
}