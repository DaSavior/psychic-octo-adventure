#ifndef CHARACTER_H
#define CHARACTER_H

#include "Common.h"
#include "ClassUtilities.h"

class Character: public SpritePlus, public Animateable
{
private:
	unsigned short energy_;
	direction facing_;
	bool walking_;
	bool raisingArm_;

public:	
	Character();

	//gets
	unsigned short getEnergy() const;
	direction getDirection() const;
	sf::IntRect getWalkCollision() const; //collision box with next step
	sf::IntRect getInteractCollision() const; //collision box for interact events (flipping a switch, 

	//sets
	void setEnergy(unsigned short energy);
	void setDirection(direction facing);

	//checks
	bool canWalk() const; //can't while arm is raised
	bool hasEnergy() const;

	//changes
	void startWalk();
	void stopWalk();
	void raiseArm();
	void lowerArm();
	
	bool addEnergy(unsigned short energy)
	{
		setEnergy(getEnergy() + energy);
	}
	bool removeEnergy(unsigned short energy)
	{
		if (energy > getEnergy())
			return false;

		setEnergy(getEnergy() - energy);
		return true;
	}
	
	//virtuals
	virtual void animate();

	//console stuff
	void toggleCollision();
};

#endif