#ifndef PROPS_H
#define PROPS_H

class Props;
class PropObject;

#include "Common.h"
#include "Character.h"
#include "ClassUtilities.h"
#include "UIUtilities.h"

class PropObject : public SpritePlus
{
private:
	direction facing_;
	propType type_;
public:
	PropObject();
	
	//gets
	direction getDirection() const;
	propType getType() const;
	
	//sets
	void setDirection(direction facing);
	void setType(propType type);

	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, PropObject prop);
	friend std::ofstream& operator<< (std::ostream &out, PropObject prop);

};

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
	bool charCanWalk(const Character &character) const;

	void setTextures(int room);

	//virtuals
	
	virtual bool load(int file);
	virtual bool loadNextRoom(std::istream &stream);
	virtual void saveProgress();
	virtual std::string roomSave(int room);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
