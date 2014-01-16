#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "ClassUtilities.h"
#include "Character.h"
#include "Puzzle.h"
#include "Story.h"
#include "Props.h"
#include "GodMode.h"


class Game: public Inputable, public Animateable, public sf::Drawable
{
private:
	//classses
	Character character
	Props props
	Story story
	Puzzle puzzle



public:
	friend GodMode;
	Game();

	void resetGame();
	void saveGame();
	void loadFromFile();
	void update(int act, int room);


	//gets

	//sets

	//checks

	//changes

	//virtual functions
	virtual location keyPressed(sf::Keyboard::Key key, location loc);
	virtual location keyReleased(sf::Keyboard::Key key, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
