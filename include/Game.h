#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "ClassUtilities.h"
#include "Character.h"
#include "Puzzle.h"
#include "Story.h"
#include "Props.h"
#include "GodMode.h"

//TODO: fill out game
class Game: public Fileable, public Inputable, public Animateable, public sf::Drawable
{
private:
	//
	//classses
	Character character;
	Props props;
	Story story;
	Puzzle puzzle;
	AllTextures textures;
	Textbox textbox;
    short act_, room_;

	std::string findActFile(short act);


public:
	friend class GodMode;
	Game();

	void resetGame();
	void updateRoom(short act, short room);


	//gets

	//sets

	//checks

	//changes

	//virtual functions
	virtual bool load(int file); //if file <= 0, then use progress file
	virtual void save(int file);

	virtual location keyPressed(sf::Keyboard::Key key, location loc);
	virtual location keyReleased(sf::Keyboard::Key key, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void animate();


};

#endif
