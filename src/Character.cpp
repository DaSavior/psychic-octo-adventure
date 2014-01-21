#include "..\include\Character.h"


Character::Character()
{
	setEnergy(0);
	setDirection(EAST);
	stopWalk();
	lowerArm();
	collides_ = true;
}

unsigned short Character::getEnergy() const
{
	return energy_;
}
direction Character::getDirection() const
{
	return facing_;
}
sf::IntRect Character::getWalkCollision() const; //collision box with next step
sf::IntRect Character::getInteractCollision() const; //collision box for interact events (flipping a switch, 

void Character::setEnergy(unsigned short energy)
{
	energy_ = energy;
}
void Character::setDirection(direction facing)
{
	facing_ = facing;
}

bool Character::canWalk() const
{
	return (!(movingArm() || raisingArm_));
}
bool Character::hasEnergy() const
{
	return (energy_ > 0);
}
bool Character::movingArm() const
{
	return (getFrame().x >= ARM_DOWN || getFrame().x <= ARM_UP);
}

void Character::startWalk()
{
	if (canWalk())
		walking_ = true;
}
void Character::stopWalk()
{
	walking_ = false;
}
void Character::raiseArm()
{
	raisingArm_ = true;
}
void Character::lowerArm()
{
	raisingArm_ = false;
}
	
bool Character::addEnergy(unsigned short energy)
	{
		setEnergy(getEnergy() + energy);
	}
bool Character::removeEnergy(unsigned short energy)
	{
		if (energy > getEnergy())
			return false;

		setEnergy(getEnergy() - energy);
		return true;
	}
	
void Character::animate();

void Character::toggleCollision()
{
	collides_ = !collides_;
}