#include "Menu.h"

Menu::Menu() : _isValidInput(false), _userChoice(0) {}

void Menu::gamePlay() {
	while (_userChoice != 8)                           // Initialized to 0
	{
		printMenu();

		try
		{
			getUserChoiceFromUser();

			switch (_userChoice)
			{
			case 1:
				addGame();
				break;
			case 2:
				next();
				break;
			case 3:
				deleteGame();
				break;
			case 4:
				printGameDetails();
				break;
			case 5:
				printLegalMoves();
				break;
			case 6:
				printThreatMoves();
				break;
			case 7:
				playMove();
				break;
			case 8:
				exitGame();
				break;
			case 9:
				saveCurrGame();
				break;
			case 10:
				loadGame();
				break;
			}
		}
		catch (bad_alloc& ex)
		{
			cout << ex.what() << endl;
			exit(1);
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
		}
		catch (const char* fileExp)
		{
			cout << "Error: " << fileExp << endl;
		}
	}
}

void Menu::printMenu() {
	cout << "MENU:" << "\n" << "1.Add a new game\n" << "2.Go to next game\n" << "3.Delete current game\n" << "4.Show game details\n" << "5.Show piece's legal moves (enter row then col)\n" << "6.Show cell's threat moves (enter row then col)\n" << "7.Make a move\n" << "8.Exit\n" << "9. Save current game\n" << "10. Load current game\n";
}

void Menu::getUserChoiceFromUser() {
	int userChoice;
	cin >> userChoice;
	try 
	{
		checkInputMenu(userChoice);
	}
	catch (exception& ex)
	{
		throw(ex);
	}
	
}

void Menu::setUserChoice(int userChoice)
{
	_userChoice = userChoice;
}

void Menu::checkInputMenu(int userChoice) {


	if (userChoice <= 0 || userChoice >= 11)
	{
		throw invalid_argument("Please enter a number between 1 to 10.");
	}
	else if (_gameList.empty() && (userChoice != 1 && userChoice != 8 && userChoice != 10))
	{
		throw invalid_argument("You have no game yet.");
	}
	else {
		setUserChoice(userChoice);
	}
}

void Menu::addGame() {
	int numOfGame = 0;
	bool valid = false;
	cout << "Choose game: \n1 - Checkers.\n2 - Amazons.\n3 - Chess." << endl;
	while (!valid)
	{
		try
		{
			cin >> numOfGame;
			if (numOfGame >= 1 && numOfGame <= 3)
			{
				valid = true;
			}
			else {
				throw invalid_argument("Please enter a correct number: (between 1 to 3):");
			}
		}
		catch (exception& ex)
		{
			cout << "Error: " << ex.what() << endl;
		}
	}

	Game* _newGame;

	if (numOfGame == 1)
	{
		_newGame = new CheckersGame;
	}
	else if (numOfGame == 2)
	{
		_newGame = new AmazonsGame;
	}
	else {
		_newGame = new ChessGame;
	}       
	_gameList.push_back(_newGame);
	_currGameNode = --_gameList.end();
}

bool Menu::getIsValidInput() const
{
	return _isValidInput;
}

int	Menu::getUserChoice() const
{
	return _userChoice;
}

Game* Menu::getCurrGameNode() const
{
	return *_currGameNode;
}

Menu::Menu(const Menu& other)
{
	*this = other;
}

void Menu::operator=(const Menu& other)
{
	if (this != &other)
	{
		_userChoice = other._userChoice;
		_gameList = other._gameList;
		_isValidInput = other._isValidInput;
		_currGameNode = other._currGameNode;
	}
}

void Menu::next() {
	if (_currGameNode == --_gameList.end())
		_currGameNode = _gameList.begin();
	else
		_currGameNode++;

}

void Menu::deleteGame() {
	if (_currGameNode == --_gameList.end())
	{
		_gameList.pop_back();
		_currGameNode = _gameList.begin();
	}
	else
	{
		_currGameNode = _gameList.erase(_currGameNode);
	}
}

void Menu::printGameDetails() {
	cout << **_currGameNode;

	if ((*_currGameNode)->getIsGameOver())
	{
		cout << "Game over" << endl;
		cout << "Player: " << (*_currGameNode)->getWinner() << " won" << endl;
	}
	else
	{
		cout << "Game is not over" << endl;
		cout << "Player: " << (*_currGameNode)->getCurrTurn() << " is playing" << endl;
	}
}

ostream& operator<<(ostream& os, const Game& game) {
	int i, j;
	int row = game.getNumCols();
	int col = game.getNumRows();
	os << "  ";
	for (i = 1; i <= col; i++)
		os << " " << i;

	os << "\n" << " ";

	int numOfHyphen = row * 2 + 2;
	for (i = 0; i < numOfHyphen; i++)
		os << "-";
	os << "\n";

	for (i = 0; i < row; i++)
	{
		os << i + 1;
		if (i < 9) {
			os << " ";
		}
		for (j = 0; j < col; j++)
		{
			os << "|";
			position data;
			data.x = i + 1;
			data.y = j + 1;

			if (game.isEmptyCell(data))
				os << " ";
			else
			{
				char temp = game.getBoard()[i][j]->getPlayer();
				os << temp;
			}
		}
		os << "|" << endl;
	}

	os << " ";
	for (i = 0; i < numOfHyphen; i++)
		os << "-";
	os << "\n";

	return os;
}

void Menu::printLegalMoves() {
	position data;
	bool validInput = false;

	while (!validInput)
	{
		validInput = true;
		getPositionToLegalOrThreatMoves(data);        
		try
		{
			(*_currGameNode)->printLegalMoves(data);
		}
		catch (exception& ex)
		{
			validInput = false;
			cout << "Error: " << ex.what() << endl;
		}
	}
}



void Menu::printThreatMoves() {
	position data;
	bool validInput = false;

	while (!validInput)
	{
		validInput = true;
		getPositionToLegalOrThreatMoves(data);
		try
		{
			(*_currGameNode)->printThreatMoves(data);
		}
		catch (exception& ex)
		{
			validInput = false;
			cout << "Error: " << ex.what() << endl;
		}
	}
}


void Menu::getPositionToLegalOrThreatMoves(position& data) {
	cout << "enter row then col: " << endl;
	cin >> data.x;
	cin >> data.y;
}
		

void Menu::playMove() {
	int size = (*_currGameNode)->getNumOfInputForMove();        // Each game needs a diffrent number of input in order to play a move.
	bool validMove = false;
	
	position* movePositions = new position[size];
	
	while (!validMove)
	{
		validMove = true;
		cout << "Enter " << size << " positions for move (row then col):" << endl;
		for (int i = 0; i < size; i++) {
			cin >> movePositions[i].x;
			cin >> movePositions[i].y;
		}
		try
		{
			(*_currGameNode)->playMove(movePositions);
		}
		catch (exception& ex)
		{
			validMove = false;
			cout << "Error: " << ex.what() << endl;
		}
	}

	delete[](movePositions);
}

void Menu::exitGame() {
	cout << "Bye";
}

void Menu::saveCurrGame()
{
	string fileName;
	cout << "Please enter file name:" << endl;

	cin >> fileName;
	
	ofstream outfile(fileName, ios::binary | ios::trunc);

	if (!outfile)
		throw ("Error with outfile");

	(*_currGameNode)->save(outfile);

	outfile.close();
}

void Menu::loadGame()
{
	string fileName;
	cout << "Please enter file name:" << endl;

	cin >> fileName;

	ifstream infile(fileName, ios::binary);

	if (!infile.is_open())
		throw ("Error with infile");

	GameLoader loader;
	Game* game = loader.load(infile);

	_gameList.push_back(game);

	infile.close();

	_currGameNode = --_gameList.end();
}