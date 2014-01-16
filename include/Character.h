#ifndef CHARACTER_H
#define CHARACTER_H

#include "Common.h"
#include "ClassUtilities.h"

class Character: public SpritePlus 
{
private:
	unsigned short energy_;
	direction facing_;

public:
	Character();

	//gets
	unsigned short getEnergy() const;

	//sets
	void setEnergy(unsigned short energy);

	//checks

	//changes
	
	//console stuff
	void toggleCollision();

};

#endif