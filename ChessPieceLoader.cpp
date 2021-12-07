#include "ChessPieceLoader.h"

ChessPiece* ChessPieceLoader::load(istream& in)
{
	char type;
	in.read(rcastc(&type), sizeof(type));

	switch (type) {
	case 'K':
		return new ChessKingPiece(in);
		break;
	case 'Q':
		return new ChessQueenPiece(in);
		break;
	case 'P':
		return new ChessPawnPiece(in);
		break;
	case 'N':
		return new ChessKnightPiece(in);
		break;
	case 'R':
		return new ChessRookPiece(in);
		break;
	case 'B':
		return new ChessBishopPiece(in);
		break;
	}
}

