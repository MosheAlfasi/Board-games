#pragma once
#include "GamePiece.h"

const int ROW_CHESS = 8;
const int COL_CHESS = 8;
const int NUM_OF_INPUTS_FOR_CHESS_MOVE = 2;

class ChessPiece : public GamePiece
{

public:
	ChessPiece(position data, char player);
	ChessPiece() = default;
	ChessPiece(const ChessPiece& other);
	void operator=(const ChessPiece& other);

	bool isSamePlayer(position other, vector<vector<GamePiece*>> board);

	virtual void setLegalMoves(vector<vector<GamePiece*>> board) = 0;
	virtual const list<position>& getLegalMoves() const;
	virtual list<position>& getLegalMoves();
	virtual void  printLegalMoves() const;

	virtual void setThreatMoves(vector<vector<GamePiece*>> board);
	virtual const list<position>& getThreatMoves() const;
	virtual list<position>& getThreatMoves();
	virtual const char getColor() const;
	void  printThreatMoves() const;

	bool inRange(position move);
	void findKingPosition(vector<vector<GamePiece*>> board, position* kingPos, char king);

	bool isKingThreatened(position kingPos, position currPos, position move, vector<vector<GamePiece*>>, ChessPiece* This);

	virtual void save(ostream& out) const;
	virtual void load(istream& in);

};
