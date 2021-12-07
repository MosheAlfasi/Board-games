#pragma once

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

enum class GameType { CHECKERS, AMAZONS, CHESS };


// struct the presented position in the board.


struct position {
	int x;
	int y;
	
	void operator=(const position& other)
	{
		x = other.x;
		y = other.y;
	}

	bool operator==(const position& other)
	{
		return x == other.x && y == other.y;
	}
};
