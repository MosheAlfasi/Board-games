#pragma once

#include "Game.h"
#include "AmazonsPiece.h"
#include "generic.h"


const int ROW_AMAZONS = 10;
const int COL_AMAZONS = 10;
const int NUM_OF_INPUTS_FOR_AMAZONS_MOVE = 3;

class  AmazonsGame : public Game
{
private:
	vector<vector<GamePiece*>> board;
  
public:
	                       AmazonsGame(); 
						   AmazonsGame(istream& in);
    virtual                ~AmazonsGame() {};
	                       AmazonsGame(const AmazonsGame&);
	                       AmazonsGame(const AmazonsGame&&);

	void                   operator=(const AmazonsGame& other);

	virtual  vector<vector<GamePiece*>>  getBoard() const;
	virtual void           updateBoard();
	GamePiece&             getGamePiece(const position data);
	GamePiece&             getGamePiece(const position data) const;
	void			       updateLegalMoves(const position& from, const position& to);
	void                   lookForWinner();
	bool	               isPlayerLoser(Player* player);

	virtual void     isLegalMove(const position& from, const position& to);
	virtual void	   isBelongToCurrTurn(const position& from);
	virtual void		   playMove (position* movePositions);
	virtual const bool	   isEmptyCell(const position& data) const;
	virtual void     validInputToPrintThreat(const position& data) const;
	virtual void     validInputToPrintLegal(const position& data) const;
	void checkValidMoveArrow(position to, position arrow);

	virtual void printLegalMoves(position& data);
	virtual void printThreatMoves(position& data);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};



