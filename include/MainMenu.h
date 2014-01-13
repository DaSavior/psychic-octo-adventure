#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Common.h"
#include "Inputable.h"

class MainMenu: public Inputable, public sf::Drawable
{
private:
	
	//new game button
	//continue button
	//options button
	//close button
	//canContinue


public:	
	MainMenu();
	void setContinue (bool can_continue);

	virtual location mousePressed(sf::Vector2i mouse_pos, location loc)
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