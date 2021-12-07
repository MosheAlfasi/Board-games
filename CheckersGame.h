#pragma once
#include "Game.h"
#include "CheckersPiece.h"

const int ROW_CHECKERS = 8;
const int COL_CHECKERS = 8;
const int NUM_OF_INPUTS_FOR_CHECKERS_MOVE = 2;

class CheckersGame : public Game {
private:
	vector<vector<GamePiece*>> board;

public:
	                          CheckersGame();
							  CheckersGame(istream& in);
    virtual                   ~CheckersGame();
	                          CheckersGame(const CheckersGame&);
							  CheckersGame(const CheckersGame&&);
	                          void operator=(const CheckersGame& other);

	virtual  vector<vector<GamePiece*>>     getBoard() const;
	virtual void              updateBoard();
	GamePiece&                getGamePiece(const position data);
	GamePiece&                getGamePiece(const position data) const;

	void			          updateLegalAndThreatMoves(const position& from, const position& to);
	void                      didCapture(position& data, const position& from, const position& to);
	virtual void               validInputToPrintLegal(const position& data) const;
	void                      lookForWinner();
	bool	                  isPlayerLoser(Player* player);

	virtual const bool		  isEmptyCell(const position& data) const;
	virtual void        validInputToPrintThreat(const position& data) const;
	virtual void              playMove(position* movePositions);
	virtual void		  isLegalMove(const position& from, const position& to);
	virtual void		  isBelongToCurrTurn(const position& from);

	virtual void printLegalMoves(position& data);
	virtual void printThreatMoves(position& data);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};



