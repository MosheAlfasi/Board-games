#include "Game.h"

Game::Game(int numRows, int numCols, int numOfInputForMove) : _isGameOver(false), _currTurn('O'), _numCols(numRows), _numRows(numCols), _numOfInputForMove(numOfInputForMove), _playerO(true, 'O'), _playerX(false, 'X') {}

Game::Game(const Game& other)
{
	*this = other;
}


void Game::operator=(const Game& other)
{
	_playerX = other.getPlayerX();
	_playerO = other.getPlayerO();
	_winner = other.getWinner();
	_isGameOver = other.getIsGameOver();
	_currTurn = other.getCurrTurn();
	_numRows = other.getNumRows();
	_numCols = other.getNumCols();
	_numOfInputForMove = other.getNumOfInputForMove();
}


void Game::setCurrTurn()      // change currTurn
{
	if (_currTurn == 'X')
	{
		_currTurn = 'O';
		_playerX.setIsPlaying(false);
		_playerO.setIsPlaying(true);
	}
	else
	{
		_currTurn = 'X';
		_playerX.setIsPlaying(true);
		_playerO.setIsPlaying(false);
	}
}


void Game::setWinner(char winner) {
	_winner = winner;
}

const char Game::getWinner() const
{
	return _winner;
}

const bool Game::getIsGameOver() const {
	return _isGameOver;
}

const char Game::getCurrTurn() const {
	return _currTurn;
}

const Player& Game::getPlayerX() const
{
	return _playerX;
}


const Player& Game::getPlayerO() const
{
	return _playerO;
}

void Game::setIsGameOver(bool isOver) {
	_isGameOver = isOver;
}

const int Game::getNumRows() const {
	return _numRows;
}

const int Game::getNumCols() const {
	return _numCols;
}

const int Game::getNumOfInputForMove() const {
	return _numOfInputForMove;
}

void Game::checkIfPosInRange(const position& data) const {           // check if position is in range of the board
	if (data.x < 1 || data.x > _numRows || data.y < 1 || data.y > _numCols)
		throw (out_of_range("please enter a correct position"));
}

void Game::checkValidMoveFrom(const position& data)                  
{
	try
	{
		checkIfPosInRange(data);
		isBelongToCurrTurn(data);
	}
	catch (exception& ex)
	{
		throw ex;
	}
}

void Game::checkValidMoveTo(const position& from, const position& to)
{
	try
	{
		checkIfPosInRange(to);
		isLegalMove(from, to);
	}
	catch (exception& ex)
	{
		throw ex;
	}

}

bool Game::isPosFound(list<position>& lst, const position& posToFind)
{
	for (position pos : lst)
		if (pos == posToFind)
			return true;

	return false;
}

int Game::numOfPieces() {
	return _playerX.getNumOfPieces() + _playerO.getNumOfPieces();
}

void Game::updateNodePos(position oldPos, position newPos, list<position>& lst)
{
	for (position& pos : lst)
	{
		if (pos == oldPos)
		{
			pos = newPos;
			break;
		}
	}
}

void Game::deleteNode(list<position>& lst, position pos)
{
	for (auto itr = lst.begin(); itr != lst.end(); ++itr)
		if ((*itr) == pos)
		{
			lst.erase(itr);
			break;
		}
}

void Game::save(ostream& out) const
{
	_playerX.save(out);
	_playerO.save(out);

	out.write(rcastcc(&_winner), sizeof(char));
	out.write(rcastcc(&_isGameOver), sizeof(bool));
	out.write(rcastcc(&_currTurn), sizeof(char));
	out.write(rcastcc(&_numRows), sizeof(int));
	out.write(rcastcc(&_numCols), sizeof(int));
	out.write(rcastcc(&_numOfInputForMove), sizeof(int));
}

void Game::load(istream& in)
{
	_playerX.load(in);
	_playerO.load(in);

	in.read(rcastc(&_winner), sizeof(char));
	in.read(rcastc(&_isGameOver), sizeof(bool));
	in.read(rcastc(&_currTurn), sizeof(char));
	in.read(rcastc(&_numRows), sizeof(int));
	in.read(rcastc(&_numCols), sizeof(int));
	in.read(rcastc(&_numOfInputForMove), sizeof(int));
}


