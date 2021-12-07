#include "CheckersGame.h"


#include "CheckersGame.h"


CheckersGame::CheckersGame() : Game(ROW_CHECKERS, COL_CHECKERS, NUM_OF_INPUTS_FOR_CHECKERS_MOVE) { // Ctor, getting row, col and num of inputs (2 for checkers)
	int i, j;

	try
	{
		for (i = 0; i < ROW_CHECKERS; i++)
		{
			board.push_back(vector<GamePiece*>());
			for (j = 0; j < COL_CHECKERS; j++)
			{
				position data;
				data.x = i + 1;
				data.y = j + 1;

				if (((i + 1) + (j + 1)) % 2 == 1 && (i < 3 || i > 4))
					board[i].push_back(new CheckersPiece(data, i < 3 ? 'X' : 'O', false));
				else
					board[i].push_back(nullptr);

			}
		}
	
	}
	catch (bad_alloc& ex)
	{
		int k, n;

		for (k = 0; k < i; ++k)
			for (n = 0; n < COL_CHECKERS; ++n)
			{
				if (board[k][n] != nullptr)
					delete board[k][n];

				if (k == i - 1 && n == j - 1)
					break;
			}
		throw ex;
	}

	_playerX.setNumOfPieces(12);
	_playerO.setNumOfPieces(12);

	updateBoard();
}

CheckersGame::CheckersGame(istream& in)
{ load(in); }

CheckersGame::~CheckersGame() { }


void CheckersGame::updateBoard()
{
	int i, j;
	for (i = 0; i < ROW_CHECKERS; i++)
		for (j = 0; j < COL_CHECKERS; j++)
		{
			if (board[i][j] != nullptr)
			{
				board[i][j]->setLegalMoves(board);
				board[i][j]->setThreatMoves(board);
			}
		}

	_playerX.initPieces(board, ROW_CHECKERS);
	_playerO.initPieces(board, ROW_CHECKERS);
}

GamePiece& CheckersGame::getGamePiece(const position data)
{
	return *(board[data.x - 1][data.y - 1]);
}

GamePiece& CheckersGame::getGamePiece(const position data) const
{
	return *(board[data.x - 1][data.y - 1]);
}

void CheckersGame::operator=(const CheckersGame& other)
{
	if (this != &other) // Checking for self assigning
	{
		Game::operator=(other); // Father copy
		position data;
		for (int i = 0; i < ROW_CHECKERS; i++)
		{
			for (int j = 0; j < COL_CHECKERS; j++)
			{
				if (board[i][j] != nullptr) // Copying non-empty cells
				{
					data.x = i;
					data.y = j;

					board[i][j] = &(other.getGamePiece(data));
				}
			}
		}
	}
}
CheckersGame::CheckersGame(const CheckersGame& other) // Copy ctor
{
	*this = other;
}

CheckersGame::CheckersGame(const CheckersGame&& other) // Move ctor
{
	position data;

	for (int i = 0; i < ROW_CHECKERS; i++)
		for (int j = 0; j < COL_CHECKERS; j++)
		{
			data.x = i + 1;
			data.y = j + 1;

			board[i][j] = &(other.getGamePiece(data)); // Copying address

			other.getBoard()[i][j] = nullptr; // Old cells will point to null
		}
}

const bool CheckersGame::isEmptyCell(const position& data) const
{
	if (board[data.x - 1][data.y - 1] == nullptr)
		return true;
	return false;
}

vector<vector<GamePiece*>> CheckersGame::getBoard() const {
	return board;
}

void CheckersGame::playMove(position* movePositions)
{
	try
	{
		checkValidMoveFrom(movePositions[0]);
		checkValidMoveTo(movePositions[0], movePositions[1]);
	}
	catch (exception& ex)
	{
		throw ex;
	}
	
	position from, to;

	from = movePositions[0];

	to = movePositions[1];

	board[to.x - 1][to.y - 1] = board[from.x - 1][from.y - 1]; // Moving the piece (old position's piece moves to the new position)
	board[from.x - 1][from.y - 1] = nullptr; // Old position is now empty
	board[to.x - 1][to.y - 1]->setPos(to);

	if (_currTurn == 'X') {
		updateNodePos(from, to, _playerX.getPieces()); // Updating piece list
	}
	else {
		updateNodePos(from, to, _playerO.getPieces());
	}

	if (to.x == 1 || to.x == 8)
	{
		CheckersPiece* t = dynamic_cast <CheckersPiece*>(board[to.x - 1][to.y - 1]); // Checking if a pawn got to last line (then make him a king)
		if (t != nullptr)
		{
			t->setIsKing(true);
		}
	}

	updateLegalAndThreatMoves(from, to);

	lookForWinner();

	setCurrTurn();
}

void CheckersGame::isBelongToCurrTurn(const position& from)
{
	try
	{
		if (isEmptyCell(from) || board[from.x - 1][from.y - 1]->getPlayer() != _currTurn)
		{
			throw invalid_argument("The chosen cell is either empty or belongs to the enemy.");
		}
	}
	catch (exception& ex)
	{
		throw ex;
	}
}

void CheckersGame::isLegalMove(const position& from, const position& to)
{
	try
	{
		if (!isPosFound(board[from.x - 1][from.y - 1]->getLegalMoves(), to))
			throw invalid_argument("The move is not legal.");
	
	}
	catch (exception& ex)
	{
		throw ex;
	}

}

void CheckersGame::updateLegalAndThreatMoves(const position& from, const position& to)
{
	int i, j;
	Player* currEnemy;
	position data;
	data.x = 0;
	data.y = 0;
	if (_currTurn == 'X') {
		currEnemy = &_playerO;
	}
	else {
		currEnemy = &_playerX;
	}
	didCapture(data, from, to);

	if (data.x != 0) // If there is a capture
	{
		delete board[data.x - 1][data.y - 1];
		board[data.x - 1][data.y - 1] = nullptr;

		currEnemy->setNumOfPieces(currEnemy->getNumOfPieces() - 1); //Updating num of pieces
		deleteNode(currEnemy->getPieces(), data);
	}

	for (i = 0; i < ROW_CHECKERS; i++)
		for (j = 0; j < COL_CHECKERS; j++)
		{
			if (board[i][j] != nullptr)
			{
				board[i][j]->getLegalMoves().clear();
				board[i][j]->setLegalMoves(board);

				board[i][j]->getThreatMoves().clear();
				board[i][j]->setThreatMoves(board);
			}
		}
}

void CheckersGame::didCapture(position& data, const position& from, const position& to) {
	position potentialCaptured;

	potentialCaptured.x = to.x + (from.x < to.x ? -1 : 1);
	potentialCaptured.y = to.y + (from.y < to.y ? -1 : 1);

	if (board[potentialCaptured.x - 1][potentialCaptured.y - 1] != nullptr)
	{
		data = potentialCaptured;
	}
}

bool CheckersGame::isPlayerLoser(Player* player) {
	bool isLoser = true;

	list<position> pieces = player->getPieces();
	if (player->getNumOfPieces() != 0) // If there are some piecs left
	{
		auto curr = pieces.begin();
		while (curr != pieces.end() && isLoser) {
			if (!(board[curr->x - 1][curr->y - 1]->getLegalMoves().empty())) // If there are no legal moves left
				isLoser = false;
			curr++;
		}
	}
	return isLoser;
}

void CheckersGame::lookForWinner()
{
	Player* potentialLoser;

	if (_currTurn == 'X')
		potentialLoser = &_playerO;
	else
		potentialLoser = &_playerX;

	if (isPlayerLoser(potentialLoser))
	{
		setIsGameOver(true);
		setWinner(_currTurn);
		potentialLoser->setIsLoser(true);
	}
}

void  CheckersGame::validInputToPrintThreat(const position& data) const {
	if (isEmptyCell(data))
		throw (invalid_argument("please enter a correct position"));
}

void CheckersGame::validInputToPrintLegal(const position& data) const {    
	try
	{
		validInputToPrintThreat(data);
	}
	catch (exception& ex)
	{
		throw ex;
	}
}

void CheckersGame::printLegalMoves(position& data) {
	try
	{
		checkIfPosInRange(data);
		validInputToPrintLegal(data);
	}
	catch (exception& ex)
	{
		throw ex;
	}

	board[data.x - 1][data.y - 1]->printLegalMoves();
}

void CheckersGame::printThreatMoves(position& data) {
	try
	{
		checkIfPosInRange(data);
		validInputToPrintThreat(data);
	}
	catch (exception& ex)
	{
		throw ex;
	}
	
	board[data.x - 1][data.y - 1]->printThreatMoves();
}

void CheckersGame::save(ostream& out) const
{
	GameType type = GameType::CHECKERS;
	out.write(rcastcc(&type), sizeof(GameType));

	Game::save(out);

	int i, j;
	for (i = 0; i < ROW_CHECKERS; ++i)
		for (j = 0; j < COL_CHECKERS; ++j)
		{
			if (board[i][j] != nullptr)
			{
				out.write(rcastcc(&i), sizeof(int));
                out.write(rcastcc(&j), sizeof(int));
				board[i][j]->save(out);
			}
		}
}

void CheckersGame::load(istream& in)
{
	Game::load(in);
	int i, j;
	int idxI, idxJ;

	int numPieces = numOfPieces();

	for (i = 0; i < ROW_CHECKERS; i++)
	{
		board.push_back(vector<GamePiece*>());
		for (j = 0; j < COL_CHECKERS; ++j)
			board[i].push_back(nullptr);
	}

	try
	{
		for (i = 0; i < numPieces; ++i)
		{
			in.read(rcastc(&idxI), sizeof(int));
			in.read(rcastc(&idxJ), sizeof(int));

			GamePiece* piece = new CheckersPiece(in);

			board[idxI][idxJ] = piece;
		}
	}
	catch (bad_alloc& ex)
	{
		int k, n;

		for (k = 0; k < idxI; ++k)
			for (n = 0; n < COL_CHECKERS; ++n)
			{
				if (board[k][n] != nullptr)
					delete board[k][n];

				if (k == idxI - 1 && n == idxJ - 1)
					break;
			}
		throw ex;
	}
}

