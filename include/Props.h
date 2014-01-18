#ifndef PROPS_H
#define PROPS_H

#include "Common.h"
#include "ClassUtilities.h"
#include "UIUtilities.h"

class Props: public Fileable
{
private:
	std::vector<std::vector<PropObject>> objects_;
	short room_;

public:
	Props();

	void update(short room);

	//for character
	std::string charInteract(const Character &character) const;
	bool charCanWalk(const Character &character) const;

	//virtuals
	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class PropObject : public SpritePlus, public Fileable
{
private:
	std::string text_;
public:
	
	//gets
	std::string getText() const;
	
	//sets
	void setText(std::string text);

	//virtuals
	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

#endif
