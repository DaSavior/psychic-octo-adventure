#ifndef PROPS_H
#define PROPS_H

#include "Common.h"
#include "Character.h"
#include "ClassUtilities.h"
#include "UIUtilities.h"

class Props: public Fileable
{
private:
	std::vector<std::vector<PropObject>> propList_;
	short room_;
	AllTextures textures;

public:
	Props();

	void updateRoom(short room);

	//for character
	std::string charInteract(const Character &character) const;
	bool charCanWalk(const Character &character) const;

	//virtuals
	
	virtual bool load(int file);
	virtual void save(int file);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class PropObject : public SpritePlus, public Fileable
{
private:
	direction facing_;
	propType type_;
public:
	PropObject();
	
	//gets
	std::string getText() const;
	direction getDirection() const;
	propType getType() const;
	
	//sets
	void setText(std::string text);
	void setDirection(direction facing);
	void setType(propType type);

	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, PropObject prop);
	friend std::ofstream& operator<< (std::ostream &out, PropObject prop);

};

#endif
