#include "GameLoader.h"


Game* GameLoader::load(istream& in) const
{
	GameType type;

	in.read(rcastc(&type), sizeof(type));

	switch (type) {
	case GameType::CHECKERS:
		return new CheckersGame(in);
		break;
	case GameType::AMAZONS:
		return new AmazonsGame(in);
		break;
	case GameType::CHESS:
		return new ChessGame(in);
	}
}