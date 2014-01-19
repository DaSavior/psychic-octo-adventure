#ifndef CLASS_UTILITIES_H
#define CLASS_UTILITIES_H

#include "Common.h"

class Fileable
{
public:
	virtual bool load(); //used for progress
	virtual void save();

	virtual bool load(std::ifstream &in); //used for main file
	virtual void save(std::ofstream &out);

	friend std::ifstream& operator>> (std::ifstream &in, Fileable fileable)
	{
		fileable.load(in);
		return in;
	}
	friend std::ofstream& operator<< (std::ofstream &out, Fileable fileable)
	{
		fileable.save(out);
		return out;
	}
};
 
class Inputable
{
public:
	location input(sf::Event event, location loc); //is defined
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
	SpritePlus(const sf::IntRect &collision = sf::IntRect());
	SpritePlus(const sf::Sprite &sprite, const sf::IntRect &collision = sf::IntRect());
	SpritePlus(const sf::Texture &texture, const sf::IntRect &collision = sf::IntRect());
	SpritePlus(const sf::Texture &texture, const sf::IntRect &rectangle, const sf::IntRect &collision = sf::IntRect());
	
	
	//gets
	sf::IntRect getCollisionRectangle() const;
	sf::IntRect getGlobalCollisionRectangle() const;
	sf::Vector2f getFrame() const;
	sf::Vector2f getFrameFit() const;

	//sets
	void setCollisionRectangle(sf::IntRect collisionRectangle);
	void setFrame(float x, float y);
	void setFrame(sf::Vector2f framePosition);
	
	//checks
	bool collides(sf::IntRect globalRect) const;
	bool collides(sf::Vector2i globalPoint) const;
	bool frameAt(direction position) const;

	//changes
	void moveFrame(float dx, float dy);
	void moveFrame(sf::Vector2f move);
	void moveFrameTo(direction position);
};


#endif