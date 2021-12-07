#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "Player.h"
#include "generic.h"

using namespace std;

class Player;

class Game 
{
protected:
	Player			  _playerX;
	Player		  	  _playerO;
	char			  _winner;
	bool			  _isGameOver;
	char			  _currTurn;
	int               _numRows, _numCols;
	int               _numOfInputForMove;

public:
	Game(int numRows, int numCols, int numOfInputForMove);

	Game() = default;            
	Game(const Game&);
	void operator=(const Game&);

	const char        getWinner() const;
	const bool        getIsGameOver() const;
	const char        getCurrTurn() const;
	const int         getNumRows() const;
	const int         getNumCols() const;
	const int         getNumOfInputForMove() const;

	const Player&     getPlayerX() const;
	const Player&	  getPlayerO() const;

	void			  setWinner(char winner);
	void              setIsGameOver(bool isOver);
	void              setCurrTurn();    
	void		  checkIfPosInRange(const position& data) const;

	virtual void playMove (position* movePositions) = 0; 
	
	virtual void       validInputToPrintThreat(const position& data) const = 0;
	virtual void        validInputToPrintLegal(const position& data)const = 0;
	virtual const bool		  isEmptyCell(const position& data) const = 0;
	virtual vector<vector<GamePiece*>> getBoard() const = 0;
	virtual void        isBelongToCurrTurn(const position& from) = 0;
	virtual void        isLegalMove(const position& from, const position& to) = 0;

	void checkValidMoveFrom(const position& data);
	void checkValidMoveTo(const position& from, const position& to);

	virtual void printLegalMoves(position& data) = 0;
	virtual void printThreatMoves(position& data) = 0;

	int numOfPieces();

	bool isPosFound(list<position>& lst, const position& posToFind);
	void updateNodePos(position oldPos, position newPos, list<position>& lst);
	void deleteNode(list<position>& lst, position pos);


	virtual void save(ostream& out) const;
	virtual void load(istream& in);

};




