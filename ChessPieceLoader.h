#pragma once

#include "generic.h"
#include "ChessPawnPiece.h"
#include "ChessKingPiece.h"
#include "ChessBishopPiece.h"
#include "ChessKnightPiece.h"
#include "ChessQueenPiece.h"
#include "ChessRookPiece.h"

class ChessPieceLoader
{
public:
	ChessPiece* load(istream& in);
};

