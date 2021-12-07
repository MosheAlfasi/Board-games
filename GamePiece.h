#pragma once

#include "Game.h"
#include "generic.h"

class GamePiece {

protected:
	position data;
	char player;
	list<position> legalMoves;
	list<position> threatMoves;

public:

	GamePiece(position data, char player);
	GamePiece() = default;
	GamePiece(const GamePiece& other);
	void operator=(const GamePiece& other);

	virtual void setLegalMoves(vector<vector<GamePiece*>> board) = 0;
	virtual const list<position>& getLegalMoves() const = 0;
	virtual list<position>& getLegalMoves() = 0;
	virtual void  printLegalMoves() const = 0;

	virtual const list<position>& getThreatMoves() const = 0;
	virtual  list<position>& getThreatMoves()  = 0;
	virtual void setThreatMoves(vector<vector<GamePiece*>> board) {};
	virtual void  printThreatMoves() const = 0;

	void printPositionList(list<position> lst) const;

	void              setPos(position currPos);
	void			  setPlayer(char curPlayer);

	const  position       getPos() const;
	const char		  getPlayer() const;
	virtual const char getColor() const = 0;

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};


