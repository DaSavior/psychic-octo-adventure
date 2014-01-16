#ifndef MENUS_H
#define MENUS_H

#include "Common.h"
#include "ClassUtilities.h"
#include "UIUtilities.h"
#include "GodMode.h"

class MainMenu: public Inputable, public sf::Drawable
{
private:
	
	//new game button
	//continue button
	//options button
	//close button
	//canContinue bool


public:	
	friend GodMode;
	MainMenu();

	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);
	/*
		if (.contain new game
			clear save
			loc = GAME
		else if (stuff migiger
		return loc
	*/
	//	new game putton also clears save file

	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class OptionsMenu: public Inputable, public sf::Drawable
{
private:
	//fullscreen toggle button
	//volume ppicture button
	//resolution up/down buttons?


public:
	OptionsMenu();
	
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);	//loc is the menu that entered options menu
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class PauseMenu: public Inputable, public sf::Drawable
{
private:



public:
	PauseMenu();
	
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif