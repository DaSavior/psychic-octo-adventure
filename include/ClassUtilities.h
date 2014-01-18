#ifndef CLASS_UTILITIES_H
#define CLASS_UTILITIES_H

#include "Common.h"

class Fileable
{
public:
	virtual bool load() =0; //used for progress
	virtual void save() =0;

	virtual bool load(std::ifstream &in) =0; //used for main file
	virtual void save(std::ofstream &out) =0;
/*
	friend std::ifstream& operator>> (std::ifstream &in, Fileable fileable);
	friend std::ofstream& operator<< (std::ofstream &out, Fileable fileable);*/
	//TODO: make class not abstract and uncomment these lines
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
	SpritePlus(const sf::Sprite &sprite, const sf::IntRect &collision = sf::IntRect());
	SpritePlus(const sf::Texture &texture, const sf::IntRect &collision = sf::IntRect());
	SpritePlus(const sf::Texture &texture, const sf::IntRect &rectangle, const sf::IntRect &collision = sf::IntRect());
	
	
	//gets
	sf::IntRect getCollisionRectangle() const;
	sf::IntRect getGlobalCollisionRectangle() const;
	sf::Vector2f getFrame() const;

	//sets
	void setCollisionRectangle(sf::IntRect collisionRectangle);
	void setFrame(sf::Vector2f framePosition);
	void setFrame(float x, float y);
	
	//checks
	bool collides(sf::IntRect rect) const;
	bool collides(sf::Vector2i point) const;
	bool frameAt(direction position) const;

	//changes
	void moveFrame(sf::Vector2f move);
	void moveFrame(float dx, float dy);
	void moveFrameTo(direction position);

};


#endif