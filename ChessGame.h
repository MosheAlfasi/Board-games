#pragma once
#include "Game.h"
#include "ChessPawnPiece.h"
#include "ChessKingPiece.h"
#include "ChessBishopPiece.h"
#include "ChessKnightPiece.h"
#include "ChessQueenPiece.h"
#include "ChessRookPiece.h"
#include "ChessPieceLoader.h"

#include <string>


class ChessGame : public Game
{
private:
	vector<vector<GamePiece*>> board;
public:
	position _kingPositionW, _kingPositionB;

public:
	                                         ChessGame();
											 ChessGame(istream& in);
	virtual                                  ~ChessGame();
	                                         ChessGame(const ChessGame&);
											 ChessGame(const ChessGame&&);
	void                                     operator=(const ChessGame& other);
	
	virtual void                             updateBoard();
	GamePiece&                               getGamePiece(const position data);
	 GamePiece&                              getGamePiece(const position data) const;
	void			                         updateLegalAndThreatMoves(position& capturePos, const position& from, const position& to);
	void                                     didCapture(position& data, const position& from, const position& to);
	virtual void                              validInputToPrintLegal(const position& data) const;
	void                                     lookForWinner();
	bool	                                 isPlayerLoser(Player* player);
	const position&                          getKingPositionW() const;
	const position&                          getKingPositionB() const;

	virtual  vector<vector<GamePiece*>>                   getBoard() const;
	virtual void                            playMove(position* movePositions);
	virtual const bool		                 isEmptyCell(const position& data) const;
	virtual void                       validInputToPrintThreat(const position& data) const;
	virtual void	                 isLegalMove(const position& from, const position& to);
	virtual void		                 isBelongToCurrTurn(const position& from);

	virtual void printLegalMoves(position& data);
	virtual void printThreatMoves(position& data);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};

