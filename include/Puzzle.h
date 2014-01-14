#ifndef PUZZLE_H
#define PUZZLE_H

#include "Common.h"
#include "Fileable.h"
#include "SpritePlus.h"

class Puzzle
{
};

class DoorObject: public Fileable, public SpritePlus
{
private:

public:
	DoorObject();
};

class CircuitObject
{
private:

public:
	CircuitObject();
};


class WireObject: sf::IntRect
{
private:

public:
	CircuitObject();
};

class BulbObject: public Fileable, public SpritePlus
{
private:

public:
	BulbObject();
};

#endif