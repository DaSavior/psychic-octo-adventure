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
	sf::IntRect getWalkCollision() const;
	sf::IntRect getInteractCollision() const;

	//sets
	void setEnergy(unsigned short energy);
	void setDirection(direction facing);

	//checks

	//changes
	void startWalk();
	void stopWalk();
	void raiseArm();
	void lowerArm();
	
	//virtuals
	virtual void animate();

	//console stuff
	void toggleCollision();
};

#endif