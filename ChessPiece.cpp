#include "ChessPiece.h"
#include <math.h>

ChessPiece::ChessPiece(position data, char player) : GamePiece(data, player) {
};

ChessPiece::ChessPiece(const ChessPiece& other) {
	*this = other;
}

void ChessPiece::operator=(const ChessPiece& other) {
	if (this != &other)
	{
		GamePiece::operator=(other);
		threatMoves = other.getThreatMoves();
		legalMoves = other.getLegalMoves();
	}
}

void ChessPiece::setThreatMoves(vector<vector<GamePiece*>> board) {
	position move;
	int i, j;

	for (i = -2; i <= 2; ++i, (i == 0 ? ++i : true))            // checking all knight directions
		for (j = -2; j <= 2; ++j, (j == 0 ? ++j : true))
		{
			if (abs(i) != abs(j))                               // can't move diagonally
			{
				move.x = data.x + i;
				move.y = data.y + j;

				if (inRange(move) && board[move.x - 1][move.y - 1] != nullptr)
				{
					char pieceType = board[move.x - 1][move.y - 1]->getPlayer();
					if ((pieceType == 'N' || pieceType == 'n') && !isSamePlayer(move, board))
					{
						threatMoves.push_back(move);
					}
				}
			}
		}

	for (i = -1; i <= 1; i++)                                  // checking rest pieces
		for (j = -1; j <= 1; j++)
		{
			if (i != 0 || j != 0)
			{
				move.x = data.x + i;
				move.y = data.y + j;

				while (inRange(move) && board[move.x - 1][move.y - 1] == nullptr)
				{
					move.x = move.x + i;
					move.y = move.y + j;
				}
				if (inRange(move) && !isSamePlayer(move, board))
				{
					char pieceType = board[move.x - 1][move.y - 1]->getPlayer();

					if (pieceType == 'K' || pieceType == 'k')
						if (abs(data.x - move.x) == 1 || abs(data.y - move.y) == 1)
							threatMoves.push_back(move);

					if (move.x == data.x || move.y == data.y)
					{
						if (pieceType == 'R' || pieceType == 'r' || pieceType == 'Q' || pieceType == 'q')
							threatMoves.push_back(move);
					}
					else
					{
						if (pieceType == 'B' || pieceType == 'b' || pieceType == 'Q' || pieceType == 'q')
						    threatMoves.push_back(move);
						
						else if (pieceType == 'P' || pieceType == 'p')
						{
							int direction;
							direction = player >= 'a' ? -1 : 1;

							if (data.x + direction == move.x)
								threatMoves.push_back(move);
						}
					}
				}
			}
		}
}

const list<position>& ChessPiece::getThreatMoves() const
{
	return threatMoves;
}

list<position>& ChessPiece::getThreatMoves()
{
	return threatMoves;
}

void ChessPiece::printThreatMoves() const
{
	printPositionList(threatMoves);
}

bool ChessPiece::inRange(position move)
{
	if (move.x > 0 && move.x <= ROW_CHESS && move.y > 0 && move.y <= COL_CHESS)
		return true;
	return false;
}

void ChessPiece::printLegalMoves() const
{
	printPositionList(legalMoves);
}

const list<position>& ChessPiece::getLegalMoves() const
{
	return legalMoves;
}

list<position>& ChessPiece::getLegalMoves()
{
	return legalMoves;
}

bool ChessPiece::isSamePlayer(position other, vector<vector<GamePiece*>> board)    // return true if other is same player like this
{
	ChessPiece* t = dynamic_cast<ChessPiece*>(board[other.x - 1][other.y - 1]);
	if (t != nullptr)
	{
		return  t->getColor() == getColor();
	}
}


void ChessPiece::findKingPosition(vector<vector<GamePiece*>> board, position* kingPos, char king)  // find my king position
{
	int i, j;
	bool isFound = false;
	for (i = 0; i < ROW_CHESS && !isFound; ++i)
		for (j = 0; j < COL_CHESS && !isFound; ++j)
			if (board[i][j] != nullptr && board[i][j]->getPlayer() == king)
			{
				(*kingPos).x = i + 1;
				(*kingPos).y = j + 1;
				isFound = true;
			}
}

const char ChessPiece::getColor() const       // return to whom the stone belongs X or O
{
	if (player <= 'Z')
		return 'X';
	return 'O';
}

bool ChessPiece::isKingThreatened(position kingPos, position currPos, position move, vector<vector<GamePiece*>> board, ChessPiece* This)
{
	bool validMove;
	GamePiece* saver = board[move.x - 1][move.y - 1];

	 // make dummy move:
	board[currPos.x - 1][currPos.y - 1] = nullptr;
	board[move.x - 1][move.y - 1] = This;
	board[kingPos.x - 1][kingPos.y - 1]->setThreatMoves(board);

	// checking if thread movevs is empty = legal move
	validMove = !board[kingPos.x - 1][kingPos.y - 1]->getThreatMoves().empty();

	// undo move:
	board[currPos.x - 1][currPos.y - 1] = This;
	board[move.x - 1][move.y - 1] = saver;
	board[kingPos.x - 1][kingPos.y - 1]->getThreatMoves().clear();

	return validMove;
}



void ChessPiece::save(ostream& out) const
{
	GamePiece::save(out);

	int size = threatMoves.size();

	out.write(rcastcc(&size), sizeof(int));
		
	for (auto itr = threatMoves.begin(); itr != threatMoves.end(); ++itr)
		out.write(rcastcc(&(*itr)), sizeof(position));
}

void ChessPiece::load(istream& in)
{
	GamePiece::load(in);

	int size;

	in.read(rcastc(&size), sizeof(int));

	threatMoves.clear();

	for (int i = 0 ; i < size ; ++i)
	{
		position pos;
		in.read(rcastc(&pos), sizeof(position));
		threatMoves.push_back(pos);
	}
}