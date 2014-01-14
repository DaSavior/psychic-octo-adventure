#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "ClassUtilities.h"
#include "Puzzle.h"
#include "Story.h"
#include "Props.h"

class Game: public Inputable, public sf::Drawable
{
private:
	/*
	classses

	character
	props
	story
	puzzle
	act room
	
	*/


public:
	Game();

	void resetGame();
	void saveGame();
	void loadFromFile();
	void update(int act, int room);

	virtual location keyPressed(sf::Keyboard::Key key, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif