#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "Common.h"
#include "Inputable.h"

class OptionsMenu: public Inputable, public sf::Drawable
{
private:
	//fullscreen toggle button
	//volume ppicture button
	//resolution up/down buttons?


public:

	
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif