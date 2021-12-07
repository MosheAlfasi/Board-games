#pragma once
#include "ChessPiece.h"

class ChessBishopPiece : public ChessPiece
{
public:
	                 ChessBishopPiece(position data, char player);
					 ChessBishopPiece(istream& in);
					 ChessBishopPiece(const ChessBishopPiece& other);

	void	         operator=(const ChessBishopPiece& other);

	virtual void	 setLegalMoves(vector<vector<GamePiece*>> board);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};