#include "AmazonsGame.h"

AmazonsGame::AmazonsGame() : Game(ROW_AMAZONS, COL_AMAZONS, NUM_OF_INPUTS_FOR_AMAZONS_MOVE) { //Each game needs row, col, num of inputs (amazons needs 3, chess and checkers need 2)
	int i, j;

	try
	{
		for (i = 0; i < ROW_AMAZONS; i++)
		{
			board.push_back(vector<GamePiece*>());
			for (j = 0; j < COL_AMAZONS; ++j)
			{
				position data;
				data.x = i + 1;
				data.y = j + 1;

				board[i].push_back(new AmazonsPiece(data, '0')); // Polymorphism
			}
		}
	}

	catch (bad_alloc& ex)
	{
		throw ex;
	}

	board[6][0]->setPlayer('O'); // Initializing pieces
	board[9][3]->setPlayer('O');
	board[9][6]->setPlayer('O');
	board[6][9]->setPlayer('O');

	board[3][0]->setPlayer('X');
	board[0][3]->setPlayer('X');
	board[0][6]->setPlayer('X');
	board[3][9]->setPlayer('X');

	_playerX.setNumOfPieces(4);
	_playerO.setNumOfPieces(4);

	updateBoard(); // Initialize board
}

AmazonsGame::AmazonsGame(istream& in)
{ load(in); }


void AmazonsGame::updateBoard()
{
	int i, j;
	for (i = 0; i < ROW_AMAZONS; i++)
		for (j = 0; j < COL_AMAZONS; j++)
			board[i][j]->setLegalMoves(board);

	_playerX.initPieces(board, ROW_AMAZONS);
	_playerO.initPieces(board, ROW_AMAZONS);
}

GamePiece& AmazonsGame::getGamePiece(const position data)
{
	return *(board[data.x - 1][data.y - 1]);
}

GamePiece& AmazonsGame::getGamePiece(const position data) const
{
	return *(board[data.x - 1][data.y - 1]);
}

void AmazonsGame::operator=(const AmazonsGame& other)
{
	if (this != &other) // Making sure no self copy is made
	{
		Game::operator=(other); // Father copy first

		position data;

		for (int i = 0; i < ROW_AMAZONS; i++) // Copying fields
			for (int j = 0; j < COL_AMAZONS; j++)
			{
				data.x = i + 1;
				data.y = j + 1;

				*board[i][j] = other.getGamePiece(data); // Copying value, not address
			}
	}
}

AmazonsGame::AmazonsGame(const AmazonsGame& other) // Copy ctor
{
	*this = other;
}

AmazonsGame::AmazonsGame(const AmazonsGame&& other) // Move ctor
{
	position data;

	for (int i = 0; i < ROW_AMAZONS; i++)
		for (int j = 0; j < COL_AMAZONS; j++)
		{
			data.x = i + 1;
			data.y = j + 1;

			board[i][j] = &(other.getGamePiece(data)); // Assigning address

			other.getBoard()[i][j] = nullptr; // Pointing old addresses to null
		}
}

const bool AmazonsGame::isEmptyCell(const position& data) const
{
	if (board[data.x - 1][data.y - 1]->getPlayer() == '0')
		return true;
	return false;
}

vector<vector<GamePiece*>> AmazonsGame::getBoard() const {
	return board;
}

void AmazonsGame::playMove(position* movePositions) // Getting an array for the inputs (Amazons has 3 inputs)
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

	position from, to, arrow;
	from = movePositions[0]; // Initial position
	to = movePositions[1]; // Wanted position
	arrow = movePositions[2]; // Arrow position

	board[to.x - 1][to.y - 1]->setPlayer(_currTurn); // Assigning new position with current piece
	board[from.x - 1][from.y - 1]->setPlayer('0');   // Assigning old position with "empty" (0)
	board[to.x - 1][to.y - 1]->setLegalMoves(board);

	if (_currTurn == 'X') 
		updateNodePos(from, to, _playerX.getPieces());
	else 
		updateNodePos(from, to, _playerX.getPieces());
	

	bool validArrow = false;

	while (!validArrow)
	{
		validArrow = true;
		try
		{
			checkValidMoveArrow(to, arrow);
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
			cin >> arrow.x;
			cin >> arrow.y;

			validArrow = false;
		}
	}

	board[arrow.x - 1][arrow.y - 1]->setPlayer('A');
	board[arrow.x - 1][arrow.y - 1]->getLegalMoves().clear();

	updateLegalMoves(from, to); // After each move, LegalMoves should be updated

	lookForWinner();            // After each move, a player may win

	setCurrTurn();              // Change turns
}

void AmazonsGame::checkValidMoveArrow(position to, position arrow)
{
	try
	{
		checkValidMoveTo(to, arrow);
	}
	catch (exception& ex)
	{
		throw invalid_argument("Arrow coordinates invalid. Please enter a new coordinate (enter row then col):");
	}
}

void AmazonsGame::isBelongToCurrTurn(const position& from)
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


void AmazonsGame::isLegalMove(const position& from, const position& to)
{
	try
	{
		if (!(isPosFound(board[from.x - 1][from.y - 1]->getLegalMoves(), to)))
		{
			throw invalid_argument("The move is not legal.");
		}
	}
	catch (exception& ex)
	{
		throw ex;
	}
}


void AmazonsGame::updateLegalMoves(const position& from, const position& to)
{
	int i, j;

	for (i = 0; i < ROW_AMAZONS; i++)
		for (j = 0; j < COL_AMAZONS; j++)
		{
			if (board[i][j]->getPlayer() != 'A')
			{
				board[i][j]->getLegalMoves().clear();
				board[i][j]->setLegalMoves(board);
			}
		}
}

bool AmazonsGame::isPlayerLoser(Player* player) {

	bool isLoser = true;
	list<position> pieces = player->getPieces();
	auto curr = pieces.begin();
	while ( curr != pieces.end() && isLoser) { // Iterating through piece list
		if (!(board[curr->x - 1][curr->y - 1]->getLegalMoves().empty()))  // A player lost if he has no legal moves with every piece   
			isLoser = false;
		curr++;
	}
	return isLoser;
}

void AmazonsGame::lookForWinner() // Setting winner if necessary
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


void AmazonsGame::validInputToPrintThreat(const position& data) const { // In Amazons, option 6 is only for empty cells
	if (!(board[data.x - 1][data.y - 1]->getPlayer() == '0'))
		throw (invalid_argument("please enter a correct position"));
}

void AmazonsGame::validInputToPrintLegal(const position& data) const { // Print legal moves only if there's a player in the cell
	if (!(board[data.x - 1][data.y - 1]->getPlayer() == 'X' || board[data.x - 1][data.y - 1]->getPlayer() == 'O'))
		throw (invalid_argument("please enter a correct position"));
}


void AmazonsGame::printLegalMoves(position& data) {
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

void AmazonsGame::printThreatMoves(position& data) {
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


void AmazonsGame::save(ostream& out) const
{
	GameType type = GameType::AMAZONS;
	out.write(rcastcc(&type), sizeof(GameType));

	Game::save(out);

	int i, j;
	for (i = 0; i < ROW_AMAZONS; ++i)
		for (j = 0; j < COL_AMAZONS; ++j)
		{
			if (board[i][j] != nullptr)
			{
				board[i][j]->save(out);
			}
		}
}

void AmazonsGame::load(istream& in)
{
	Game::load(in);
	int i, j;

	try
	{
		for (i = 0; i < ROW_AMAZONS; ++i)
		{
			board.push_back(vector<GamePiece*>());
			for (j = 0; j < COL_AMAZONS; ++j)
			{
				GamePiece* piece = new AmazonsPiece(in);

				board[i].push_back(piece);
			}
		}
	}

	catch (bad_alloc& ex)
	{
		int k, n;

		for (k = 0; k < i; ++k)
			for (n = 0; n < COL_AMAZONS; ++n)
			{
				delete board[k][n];

				if (k == i - 1 && n == j - 1)
					break;
			}
		throw ex;
	}
}