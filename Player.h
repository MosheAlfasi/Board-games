#pragma once

#include "generic.h"

class GamePiece;

class Player {
private:
	bool				   _isPlaying;
	bool				   _isLoser;
	char				   _whichPlayer;
	int					   _numOfPieces;
	int					   _sizeBoard;
	list<position>		   pieces;

public:

	                       Player(const bool isPlaying, const char whichPlayer);
	                       Player() = default;
	                       Player(const Player&);

    const Player& operator=(const Player& other);

	void				   setIsPlaying(bool isPlaying);
	void				   setIsLoser(bool isWinner);
	void				   setWhichPlayer(char whichPlayer);

	void				   initPieces(vector<vector<GamePiece*>> board, int sizeBoard);
	void				   setNumOfPieces(int numOfPieces);

	const int			   getNumOfPieces() const;
	const int			   getSizeBoard() const;
	const bool			   getIsPlaying() const;
	const bool			   getIsLoser() const;
	const int			   getWhichPlayer() const;
	list<position>&          getPieces();
	const list<position>&    getPieces() const;

	void save(ostream& out) const;
	void load(istream& in);
};



