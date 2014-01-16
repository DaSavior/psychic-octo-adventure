#ifndef CLASS_UTILITIES_H
#define CLASS_UTILITIES_H

#include "Common.h"

class Fileable
{
public:
	virtual bool load() =0;
	virtual void save() =0;

	virtual bool load(std::ifstream &in) =0;
	virtual void save(std::ofstream &out) =0;
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
		case sf::Event::KeyReleased:
			loc = keyReleased(event.key.code, loc);
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
	virtual location keyReleased(sf::Keyboard::Key key, location loc) {return loc;};
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc) {return loc;};
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc) {return loc;};
};

class Animateable
{
public:
	virtual void animate() = 0;
};

class SpritePlus: public sf::Sprite
{
private:
	sf::IntRect collisionRectangle_;
	
public:	
	SpritePlus();
	
	//gets
	sf::IntRect getCollisionRectangle() const;
	sf::IntRect getGlobalCollisionRectangle() const;
	sf::Vector2f getFrame() const;

	//sets
	void setCollisionRectangle(sf::IntRect collisionRectangle);
	void setFrame(sf::Vector2f frame);
	void setFrame(float x, float y);
	
	//checks
	bool collides(sf::IntRect rect) const;
	bool collides(sf::Vector2i point) const;

	//changes
	void moveFrame(sf::Vector2f move);
	void moveFrame(float dx, float dy);

};

#endif