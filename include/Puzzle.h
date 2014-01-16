#ifndef PUZZLE_H
#define PUZZLE_H

#include "Common.h"
#include "ClassUtilities.h"

class Puzzle
{
private:

public:

};

class DoorObject: public Fileable, public SpritePlus
{
private:

public:
	DoorObject();

	virtual bool loadFromFile();
	virtual bool saveTofile();
};

class CircuitObject: public Fileable
{
private:

public:
	CircuitObject();

	virtual bool loadFromFile();
	virtual bool saveTofile();
};

class WireObject: public Fileable, public sf::IntRect
{
private:

public:
	WireObject();
	virtual friend std::istream& operator>>(std::istream &is, WireObject wire);

	virtual bool loadFromFile();
	virtual bool saveTofile();
};

class BulbObject: public Fileable, public SpritePlus
{
private:

public:
	BulbObject();

	virtual bool loadFromFile();
	virtual bool saveTofile();
};

#endif