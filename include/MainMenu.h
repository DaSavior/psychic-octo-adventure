#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Common.h"
#include "Inputable.h"

class MainMenu: public Inputable, public sf::Drawable
{
private:



public:

	
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif