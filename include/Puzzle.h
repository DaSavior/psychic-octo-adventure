#ifndef PUZZLE_H
#define PUZZLE_H

#include "Common.h"
#include "ClassUtilities.h"

class Puzzle: public Fileable
{
private:
    //std::vector<std::vector<sf::IntRect>> refers to room then objects within the room
	std::vector<std::vector<DoorObject>> doors;
	std::vector<std::vector<CircuitObject>> circuits;
	std::vector<std::vector<WireObject>> wires;

public:
	Puzzle();

	//gets
	std::vector<std::vector<DoorObject>> getDoors();
	std::vector<std::vector<CircuitObject>> getCircuits();
	std::vector<std::vector<WireObject>> getWires();

	//for character
	void charToPlugEnergy(Character &character);
	void charFromPlugEnergy(Character &character);
	void charInteract(Character &character);
	bool charCanWalk(Character &character) const;

	//virtuals
	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

class DoorObject: public Fileable, public SpritePlus
{
private:
	short answer_;
	direction facing_;
	short circuitFrom_;

	bool open_;

public:
	DoorObject();
	DoorObject(std::ifstream& in);

	//gets
	short getAnswer() const;
	direction getFacing() const;
	short getCircuitFrom() const;
	
	//sets
	short setAnswer();
	direction setFacing();
	short setCircuitFrom();

	//checks
	bool isOpen() const; //is the door open
	bool checkAnswer(short answer) const;

	//changes
	void open();
	void close();
	
	//virtuals
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

class LeverObject: public SpritePlus, public Fileable
{
private:
	leverState state_;
public:
	LeverObject();

	//gets
	leverState getLeverState() const;

	//sets
	void setLeverState(leverState state);

	//changes
	void toggleState();

	//virtuals
	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

class CircuitObject: public Fileable, public sf::Drawable
{
private:
	LeverObject lever_;
	std::vector<BulbObject> bulbs_;
public:
	CircuitObject();
	CircuitObject(std::ifstream &file);

	//gets
	unsigned short getEnergy() const;

	//sets
	void setEnergy(unsigned short energy);

	//checks
	bool intersects(sf::IntRect globalRect);

	//changes
	bool addEnergy(unsigned short energy);
	bool removeEnergy(unsigned short energy);
	
	//virtuals
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states);
};

class WireObject: public Fileable, public sf::IntRect
{
private:

public:
	WireObject();
	WireObject(std::ifstream &file);

	void setStart(sf::Vector2i point);
	void setEnd(sf::Vector2i point);
	void setWidth(float width);

	//virtuals
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

class BulbObject: public Fileable, public SpritePlus
{
private:

public:
	BulbObject();
	
	//virtuals
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

#endif