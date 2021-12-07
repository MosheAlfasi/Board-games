#include "GamePiece.h"


GamePiece::GamePiece(position posi, char player) : player(player), data(posi) {
}


void GamePiece::setPos(position currPos)
{
	data = currPos;
}

void GamePiece::setPlayer(char curPlayer)
{
	player = curPlayer;
}

const position GamePiece::getPos() const
{
	return data;
}

const char GamePiece::getPlayer() const
{
	return player;
}

GamePiece::GamePiece(const GamePiece& other) {

	*this = other;
}

void GamePiece::operator=(const GamePiece& other) {
	data = other.getPos();
	player = other.getPlayer();
}


void GamePiece::printPositionList(list<position> lst) const
{
	if (lst.empty())
	{
		cout << "EMPTY!" << endl;
	}
	else
	{
		for (auto itr = lst.begin(); itr != lst.end(); ++itr)
			cout << (*itr).x << ", " << (*itr).y << endl;
	}
}


void GamePiece::save(ostream& out) const
{
	out.write(rcastcc(&data), sizeof(position));
	out.write(rcastcc(&player), sizeof(char));

	int size = legalMoves.size();

	out.write(rcastcc(&size), sizeof(int));

	for (auto itr = legalMoves.begin(); itr != legalMoves.end(); ++itr)
		out.write(rcastcc(&(*itr)), sizeof(position));
}

void GamePiece::load(istream& in)
{
	in.read(rcastc(&data), sizeof(position));
	in.read(rcastc(&player), sizeof(char));

	int size;
	in.read(rcastc(&size), sizeof(int));

	for (int i = 0 ; i < size ; ++i)
	{
		position pos;
		in.read(rcastc(&pos), sizeof(position));
		legalMoves.push_back(pos);
	}

}