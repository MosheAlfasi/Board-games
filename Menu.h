#pragma once

#include "GamePiece.h"
#include "generic.h"
#include "Player.h"
#include "GameLoader.h"

using namespace std;

ostream& operator<<(ostream& os, const Game& game);

class Menu
{
private:
	int				_userChoice;
	list<Game*> _gameList;
	bool			_isValidInput;
	list<Game*>::iterator _currGameNode;

public:
	Menu();
	Menu(const Menu& other);

	void			operator=(const Menu& other);

	void			gamePlay();

private:

	void			printMenu();
	void			getUserChoiceFromUser();
	bool			getIsValidInput() const;        
	int				getUserChoice() const;

	Game* getCurrGameNode() const;

	void			setUserChoice(int userChoice);             
	void			checkInputMenu(int userChoice);   

	void			addGame(); 
	void			deleteGame(); 
	void			next(); 
	void			printGameDetails();           
	void			printLegalMoves();            
	void			getPositionToLegalOrThreatMoves(position& data);
	void			printThreatMoves();
	void			playMove();
	void			exitGame();
	void           saveCurrGame();
	void           loadGame();
};