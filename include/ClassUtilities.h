#ifndef CLASS_UTILITIES_H
#define CLASS_UTILITIES_H

#include "Common.h"

class Fileable
{
public:
	virtual bool loadProgress()=0; //used for progress
	virtual void saveProgress()=0;

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

class LineShape: private sf::RectangleShape
{
private:
	sf::Vector2i start;
	sf::Vector2i end;
public:
	//gets
	sf::Vector2i getState();
	sf::Vector2i getEnd();
	int getThickness();
	sf::Color getColor();

	//sets
	void setState(sf::Vector2i point);
	void setEnd(sf::Vector2i point);
	void setThickness(int thickness);
	void setColor(sf::Color::color)

	//checks
	bool intersects(LineShape other);
	bool intersects(sf::RectangleShape other);

	//changes
};

class AllTextures
{
private:
	void loadSheets();

	static std::vector<sf::Texture[4]> props_;
	static std::vector<sf::Texture[4]> walls_;
	static std::vector<sf::Texture[4]> doors_;
	static std::vector<sf::Texture> floors_;
	static sf::Texture lever_;
	static sf::Texture plug_;
	static sf::Texture bulb_;
public:

	AllTextures();
	void loadAll();
	
	sf::Texture* prop(propType type, direction facing) const;
	sf::Texture* floor(floorType type) const;
	sf::Texture* walls(wallType type, direction facing) const;
	sf::Texture* lever() const;
	sf::Texture* bulb() const;
	sf::Texture* plug() const;
	sf::Texture* door(doorType type, direction facing) const;
	//TODO: list all textures needed

public:
	
};
class AllFonts
{
private:
	std::vector<sf::Font> fonts_;

public:

	void loadAll();
	sf::Font* arial() const;
	//TODO: list all fonts needed
};


#endif