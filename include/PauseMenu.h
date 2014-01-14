#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Common.h"
#include "ClassUtilities.h"
#include "UIUtilities.h"

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