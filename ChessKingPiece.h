#pragma once
#include "ChessPiece.h"
class ChessKingPiece : public ChessPiece
{
public:
	                      ChessKingPiece(position data, char player);
						  ChessKingPiece(istream& in);
	                      ChessKingPiece(const ChessKingPiece& other);

	void	              operator=(const ChessKingPiece& other);

	virtual void          setLegalMoves(vector<vector<GamePiece*>> board);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};

