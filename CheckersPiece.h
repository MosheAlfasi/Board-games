#pragma once
#include "GamePiece.h"

class CheckersPiece : public GamePiece {
private:

	bool _isKing;

public:
	                                 CheckersPiece(position data, char player, bool isKing);
									 CheckersPiece(istream& in);
					                 CheckersPiece(const CheckersPiece& other);

	void	                         operator=(const CheckersPiece& other);

	void                             printThreatMoves() const;
	void	                         legalPawnMoves(vector<vector<GamePiece*>> board, int direction);
	void	                         legalKingMoves(vector<vector<GamePiece*>> board);
	void	                         pawnThreats(vector<vector<GamePiece*>> board);
	void                             kingsThreats(vector<vector<GamePiece*>> board);
	bool                             inRange(position move);
	void                             setIsKing(bool isKing);
	const bool                       getIsKing() const;

	virtual void		             setLegalMoves(vector<vector<GamePiece*>> board);
	virtual const list<position>&      getLegalMoves() const;
	virtual list<position>&            getLegalMoves();
	virtual void			         printLegalMoves() const;
	virtual const list<position>&      getThreatMoves() const;
	virtual void                     setThreatMoves(vector<vector<GamePiece*>> board);
	virtual list<position>&            getThreatMoves();
	virtual const char               getColor() const;

	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};



