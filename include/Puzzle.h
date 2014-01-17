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
	std::vector<std::vector<CircuitObject>> getCircuits();
	std::vector<std::vector<DoorObject>> getDoors();
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

class WireObject: public Fileable, public sf::IntRect
{
private:

public:
	WireObject();
	WireObject(std::ifstream &file);

	void setStart(sf::Vector2i point);
	void setEnd(sf::Vector2i point);
	void setWidth(float width);
	void setState(leverState state);s

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
	LeverObject(std::ifstream& file);

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

class PlugObject: public SpritePlus, public Fileable
{
private:
	plugState state_;
	sf::Vector2i from_;
public:
	PlugObject();
	PlugObject(std::ifstream& file);

	//gets
	plugState getPlugState() const;
	sf::Vector2i getFrom() const;

	//sets
	void setPlugState(plugState state);

	//virtuals
	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

class CircuitObject: public Fileable, public sf::Drawable, public Animateable
{
	friend Puzzle;

private:
	LeverObject lever_;
	std::vector<BulbObject> bulbs_;
	PlugObject plug_;

	unsigned short circuitNumber_;

public:
	CircuitObject();
	CircuitObject(std::ifstream &file);

	//gets
	unsigned short getCircuitNumber() const;
	unsigned short getEnergy() const; //energy in bulbs
	short getOutput() const; //energy sent by circuit with lever (can be negative)
	std::vector<sf::Vector2i> getCenterPoints () const; //returns centers of objects on screen to draw wires with

	//sets
	void setEnergy(unsigned short energy);
	void setCircuitNumber(short number);

	//checks
	bool intersects(sf::IntRect globalRect) const;

	//changes
	bool addEnergy(unsigned short energy);
	bool removeEnergy(unsigned short energy);
	
	//virtuals
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states);
	virtual void animate();
};

class BulbObject: public Fileable, public SpritePlus, public Animateable
{
private:
	bool on_;
public:
	BulbObject();
	//using SpritePlus::SpritePlus;
	//HACK: can I inherit constructors from SpritePlus without redefining each one

	//checks
	bool isOn() const;

	//changes
	void turnOn();
	void turnOff();
	void toggle();

	//virtuals
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
	virtual void animate();
};
#endif