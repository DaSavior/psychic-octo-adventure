#ifndef CLASS_UTILITIES_H
#define CLASS_UTILITIES_H

#include "Common.h"
#include <cmath>

class Fileable
{
protected:
	static std::string progressFile_;
	static std::vector<std::string> actFiles_;	

public:
	void loadFiles();

	virtual void checkpoint()=0;
	
	virtual bool load(int file); //if file <= 0, then use progress file
	virtual void save(int file);

	//TODO: this
	friend std::ifstream& operator>> (std::istream &in, Fileable fileable)
	{
		fileable.load(in);
		return in;
	}
	friend std::ofstream& operator<< (std::ostream &out, Fileable fileable)
	{
		fileable.save(out);
		return out;
	}
};
 
class Inputable
{
public:
	location input(sf::Event event, location loc); //is defined TODO: LineShape location?????
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

class LineShape: public sf::RectangleShape //TODO: set AA to x8/x16
{
private:
	sf::Vector2i start;
	sf::Vector2i end;

	int theta; // the angle between the line formed by the 2 points and the x-axis
	int distance; // the distance between the 2 points

public:
	LineShape(sf::Vector2i t_start, sf::Vector2i t_end, sf::Color color = sf::Color::Green);

	//gets
	sf::Vector2i getStart();
	sf::Vector2i getEnd();
	int getThickness();
	sf::Color getColor();

	//sets
	void setStart(sf::Vector2i point);
	void setEnd(sf::Vector2i point);
	void setThickness(int thickness);
	void setColor(sf::Color color);

	//checks
	bool intersects(LineShape other);
	bool intersects(sf::RectangleShape other);

	//changes

};

class CurveShape : public sf::Drawable //TODO: what else goes in this??
{
private:
	std::vector<LineShape> lines;
public:
	CurveShape(std::vector<sf::Vector2i> points, sf::Color color = sf::Color::Green); //points are in order from beginning to end, color is of whole line

	void setTexture(sf::Texture texture);
	
	void addPoint(sf::Vector2i);
	//void removePoint();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
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
class AllFiles
{

};

#endif