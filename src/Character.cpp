#include "..\include\Character.h"


Character::Character()
{
	setEnergy(0);
	setDirection(EAST);
	stopWalk();
	lowerArm();
	collides_ = true;
	walkDistance_ = 1000;//TODO: initialize walkDistance_ to something
}

unsigned short Character::getEnergy() const
{
	return energy_;
}
direction Character::getDirection() const
{
	return facing_;
}
sf::IntRect Character::getWalkCollision() const //collision box with next step
{
	sf::IntRect temp = rectMove(getGlobalCollisionRectangle(), facing_, walkDistance_);
	return rectMake_Containing(getGlobalCollisionRectangle(), temp);
}
sf::IntRect Character::getInteractCollision() const //collision box for interact events (flipping a switch, etc...
{
	sf::FloatRect box1 = getGlobalBounds();
	sf::IntRect box2 = sf::IntRect(box1.left, box1.top, box1.width, box1.height);
	sf::IntRect temp = rectMove(box2, facing_, walkDistance_);

	return rectMake_Containing(box2, temp);
}

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