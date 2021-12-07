#pragma once
#include "GamePiece.h"
#include "generic.h"


class AmazonsPiece : public GamePiece {

public:
	                                 AmazonsPiece (position data, char player);
									 AmazonsPiece(istream& in);
	                                 AmazonsPiece (const AmazonsPiece& other);

	void	                         operator=(const AmazonsPiece& other);

	bool                             inRange(position move);
	const char                       getColor() const;

	virtual void		             setLegalMoves(vector<vector<GamePiece*>> board);
	virtual const list<position>&      getLegalMoves() const;
	virtual list<position>&            getLegalMoves();
	virtual void			         printLegalMoves() const;

	virtual const list<position>&      getThreatMoves() const;
	virtual  list<position>&           getThreatMoves();
	virtual void			         printThreatMoves() const;


	virtual void save(ostream& out) const;
	virtual void load(istream& in);
};

