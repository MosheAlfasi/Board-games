#pragma once
#include "ChessPiece.h"
class ChessQueenPiece : public ChessPiece
{
public:
	ChessQueenPiece(position data, char player);
	ChessQueenPiece(istream& in);
	void			operator=(const ChessQueenPiece& other);
	ChessQueenPiece(const ChessQueenPiece& other);

	virtual void    setLegalMoves(vector<vector<GamePiece*>> board);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};

