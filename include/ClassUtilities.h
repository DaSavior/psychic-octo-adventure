#ifndef CLASS_UTILITIES_H
#define CLASS_UTILITIES_H

#include "Common.h"

class Fileable
{
public:
	virtual bool loadFromFile() =0;
	virtual bool saveTofile() =0;

};

class Inputable
{
public:
	location input(sf::Event event, location loc)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			loc = keyPressed(event.key.code, loc);
			break;
		case sf::Event::MouseButtonPressed:
			loc = mousePressed(sf::Mouse::getPosition(), loc);
			break;
		case sf::Event::MouseMoved:
			loc = mouseMoved(sf::Mouse::getPosition(), loc);
			break;
		}
		return loc;
	}
	virtual location keyPressed(sf::Keyboard::Key key, location loc) {return loc;};
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc) {return loc;};
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc) {return loc;};
};

class SpritePlus: public sf::Sprite
{
private:


public:	
	SpritePlus();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif