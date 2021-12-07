#pragma once
#include "ChessPiece.h"
class ChessPawnPiece : public ChessPiece
{
public:
	                  ChessPawnPiece(position data, char player);
					  ChessPawnPiece(istream& in);
					  ChessPawnPiece(const ChessPawnPiece& other);

	void	          operator=(const ChessPawnPiece& other);

	virtual void      setLegalMoves(vector<vector<GamePiece*>> board);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};

