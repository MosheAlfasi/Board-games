#pragma once
#include "ChessPiece.h"
class ChessKnightPiece : public ChessPiece
{
public:
	                  ChessKnightPiece(position data, char player);
					  ChessKnightPiece(istream& in);
	                  ChessKnightPiece(const ChessKnightPiece& other);

	void	          operator=(const ChessKnightPiece& other);

	virtual void      setLegalMoves(vector<vector<GamePiece*>> board);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);



};

