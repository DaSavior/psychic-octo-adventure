#ifndef SPRITE_PLUS_H
#define SPRITE_PLUS_H

#include "Common.h"

class SpritePlus: public sf::Sprite
{
private:


public:	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif