#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Common.h"
#include "ClassUtilities.h"
#include "UIUtilities.h"

class MainMenu: public Inputable, public sf::Drawable
{
private:
	
	//new game button
	//continue button
	//options button
	//close button
	//canContinue bool


public:	
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

#endif