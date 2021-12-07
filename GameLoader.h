#pragma once

#include <iostream>

#include "generic.h"

#include "AmazonsGame.h"
#include "CheckersGame.h"
#include "ChessGame.h"


using namespace std;

class GameLoader {
public:
	Game* load(istream& in) const;
};
