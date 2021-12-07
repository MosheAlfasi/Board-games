#pragma once
#include "ChessPiece.h"
class ChessRookPiece : public ChessPiece
{
public:
	ChessRookPiece(position data, char player);
	ChessRookPiece(istream& in);
	void			operator=(const ChessRookPiece& other);
	ChessRookPiece(const ChessRookPiece& other);
	virtual void    setLegalMoves(vector<vector<GamePiece*>> board);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};

