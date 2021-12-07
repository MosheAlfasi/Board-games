#include "CheckersPiece.h"

const int LEFT = -1;
const int RIGHT = 1;


CheckersPiece::CheckersPiece(position data, char player, bool isKing) : GamePiece(data, player), _isKing(isKing) {}; // Ctor

CheckersPiece::CheckersPiece(istream& in)
{
	load(in);
}

CheckersPiece::CheckersPiece(const CheckersPiece& other) { // Copy ctor
	*this = other;
}

void CheckersPiece::operator=(const CheckersPiece& other) {
	if (this != &other) // Checking for self assigning
	{
		GamePiece::operator=(other); // Father copy
		legalMoves = other.getLegalMoves(); // "Operator =" for lists
		threatMoves = other.getThreatMoves();
		_isKing = other.getIsKing(); // Shallow copy
	}
}

void CheckersPiece::setLegalMoves(vector<vector<GamePiece*>> board) {
	int direction;
	if (player == 'X')
		direction = 1;
	else
		direction = -1;

	legalMoves.clear();

	if (_isKing == false)
		legalPawnMoves(board, direction);
	else
		legalKingMoves(board);
}

void CheckersPiece::setIsKing(bool isKing) {
	_isKing = isKing;
}

void CheckersPiece::legalPawnMoves(vector<vector<GamePiece*>> board, int direction) {

	position move;
	int leftOrRight = LEFT;

	for (int i = 0; i < 2; i++, leftOrRight = RIGHT) // Checking for each side
	{
		move.x = data.x + direction; // Per color
		move.y = data.y + leftOrRight; // Per side

		if (inRange(move))
		{
			if (board[move.x - 1][move.y - 1] == nullptr) // No capture
				legalMoves.push_back(move);

			else
			{
				if (board[move.x - 1][move.y - 1]->getPlayer() != this->getPlayer())  // Capture
				{
					move.x = move.x + direction;
					move.y = move.y + leftOrRight;

					if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
						legalMoves.push_back(move);
				}
			}
		}
	}
}

void CheckersPiece::legalKingMoves(vector<vector<GamePiece*>> board) {
	int direction, leftOrRight;
	direction = 1;
	leftOrRight = RIGHT;
	position move;


	for (int i = 0; i < 4; i++) // Can move in 4 diagonal directions
	{
		move.x = data.x + direction;
		move.y = data.y + leftOrRight;

		while ((inRange(move)) && board[move.x - 1][move.y - 1] == nullptr) // No capture
		{
			legalMoves.push_back(move);
			move.x = move.x + direction;
			move.y = move.y + leftOrRight;
		}
		if (inRange(move) && board[move.x - 1][move.y - 1]->getPlayer() != this->getPlayer()) // Capture
		{
			move.x = move.x + direction;
			move.y = move.y + leftOrRight;
			if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
				legalMoves.push_back(move);
		}

		if (leftOrRight == RIGHT)
			leftOrRight = LEFT;
		else
		{
			direction = -1;
			leftOrRight = RIGHT;
		}
	}
}

void CheckersPiece::setThreatMoves(vector<vector<GamePiece*>> board)
{
	threatMoves.clear();

	pawnThreats(board);
	kingsThreats(board);
}

void CheckersPiece::pawnThreats(vector<vector<GamePiece*>> board)
{
	int direction, leftOrRight;

	if (player == 'X')
		direction = 1;
	else
		direction = -1;

	leftOrRight = RIGHT;

	for (int i = 0; i < 2; i++, leftOrRight = LEFT)
	{
		position move;

		move.x = data.x + -1 * direction;
		move.y = data.y + leftOrRight;

		if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
		{
			move.x = data.x + direction;
			move.y = data.y + -1 * leftOrRight;

			if (inRange(move) && board[move.x - 1][move.y - 1] != nullptr && board[move.x - 1][move.y - 1]->getPlayer() != this->getPlayer())
				threatMoves.push_back(move);
				
		}
	}
}

void CheckersPiece::kingsThreats(vector<vector<GamePiece*>> board)
{
	int direction = 1, leftOrRight = RIGHT;
	position move;

	for (int i = 0; i < 4; i++)
	{
		move.x = data.x + -1 * direction;
		move.y = data.y + leftOrRight;

		if (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
		{
			move.x = data.x + direction;
			move.y = data.y + -1 * leftOrRight;
			while (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
			{
				move.x = move.x + direction;
				move.y = move.y + -1 * leftOrRight;
			}
			if (inRange(move))
			{
				CheckersPiece* t = dynamic_cast <CheckersPiece*>(board[move.x - 1][move.x - 1]);
				if (t != nullptr)
					if (inRange(move) && t->getPlayer() != this->getPlayer() && t->getIsKing() == true)
						threatMoves.push_back(move);
			}
		}
		if (leftOrRight == RIGHT)
			leftOrRight = LEFT;
		else
		{
			direction = -1;
			leftOrRight = RIGHT;
		}
	}
}

const bool CheckersPiece::getIsKing() const {
	return _isKing;
}


bool CheckersPiece::inRange(position move)
{
	if (move.x > 0 && move.x <= 8 && move.y > 0 && move.y <= 8)
		return true;
	return false;
}

void CheckersPiece::printLegalMoves() const
{
	printPositionList(legalMoves);
}

void CheckersPiece::printThreatMoves() const {
	printPositionList(threatMoves);
}

const list<position>& CheckersPiece::getLegalMoves() const
{
	return legalMoves;
}

list<position>& CheckersPiece::getLegalMoves()
{
	return legalMoves;
}

const list<position>& CheckersPiece::getThreatMoves() const
{
	return threatMoves;
}

list<position>& CheckersPiece::getThreatMoves()
{
	return threatMoves;
}

const char CheckersPiece::getColor() const {
	return player;
}


void CheckersPiece::save(ostream& out) const
{
	GamePiece::save(out);

	int size = threatMoves.size();

	out.write(rcastcc(&(size)), sizeof(int));

	for (auto itr = threatMoves.begin(); itr != threatMoves.end(); ++itr)
		out.write(rcastcc(&(*itr)), sizeof(position));

	out.write(rcastcc(&_isKing), sizeof(bool));
}



void CheckersPiece::load(istream& in)
{
	GamePiece::load(in);

	threatMoves.clear();

	int size;
	in.read(rcastc(&size), sizeof(int));

	for (int i = 0 ; i < size ; ++i)
	{
		position pos;
		in.read(rcastc(&pos), sizeof(position));
		threatMoves.push_back(pos);
	}

	in.read(rcastc(&_isKing), sizeof(bool));
}