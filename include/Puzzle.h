#ifndef PUZZLE_H
#define PUZZLE_H

class Puzzle;
class DoorObject;
class WireObject;
class CircuitObject;
class BulbObject;
class LeverObject;
class PlugObject;

#include "Common.h"
#include "ClassUtilities.h"
#include "Character.h"


class Puzzle: public Fileable
{
private:
    //std::vector<std::vector<sf::IntRect>> refers to room then objects within the room
	std::vector<std::vector<DoorObject>> doors_;
	std::vector<std::vector<CircuitObject>> circuits_;
	std::vector<std::vector<CurveShape>> wires_;
	short room_;

	AllTextures textures;
	AllFonts fonts;

public:
	Puzzle();

	//gets

	void updateRoom(short room);

	//for character
	bool charToPlugEnergy(Character &character);
	bool charFromPlugEnergy(Character &character);
	bool charInteract(const Character &character);
	bool charCanWalk(const Character &character) const;

	//virtuals
	virtual bool load(int file);
	virtual void save(int file);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class DoorObject: public SpritePlus
{
private:
	short answer_;
	sf::Text doorNumber_;
	
	short circuitFrom_;
	direction facing_;

public:
	DoorObject();

	void fit();

	//gets
	short getAnswer() const;
	direction getFacing() const;
	short getCircuitFrom() const;
	
	//sets
	void setAnswer(short answer);
	void setFacing(direction facing);
	void setCircuitFrom(short from);

	//checks
	bool isOpen() const; //is the door open
	bool checkAnswer(short answer) const;

	//changes
	void open();
	void close();
	
	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, DoorObject door);
	friend std::ofstream& operator<< (std::ostream &out, DoorObject door);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class WireObject: public CurveShape
{
private:

public:
	WireObject();
	WireObject(std::ifstream &file);

	void setState(leverState state);

	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, WireObject wire);
	friend std::ofstream& operator<< (std::ostream &out, WireObject wire);
};

class CircuitObject: public sf::Drawable
{
	friend Puzzle;

private:
	PlugObject plug_;
	std::vector<BulbObject> bulbs_;
	LeverObject lever_;

	unsigned short circuitNumber_;

public:
	CircuitObject();

	//gets
	unsigned short getCircuitNumber() const;
	unsigned short getEnergy() const; //energy in bulbs
	unsigned short getMaxEnergy() const;
	unsigned short getSpace() const;
	short getOutput() const; //energy sent by circuit with lever (can be negative)
	std::vector<sf::Vector2i> getCenterPoints () const; //returns centers of objects on screen to draw wires with

	//sets
	bool setEnergy(unsigned short energy);
	void setCircuitNumber(short number);

	//checks
	bool hasEnergy() const;
	bool hasSpace() const;
	bool collides(sf::IntRect globalRect) const;

	//changes
	bool addEnergy(unsigned short energy);
	bool removeEnergy(unsigned short energy);
	
	//for character
	bool charToPlugEnergy(Character &character);
	bool charFromPlugEnergy(Character &character);
	bool charInteract(const Character &character);
	bool charCanWalk(const Character &character) const;
	
	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, CircuitObject circuit);
	friend std::ofstream& operator<< (std::ostream &out, CircuitObject circuit);
	
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class BulbObject: public SpritePlus
{
private:
	bool on_;
public:
	BulbObject();

	//checks
	bool isOn() const;

	//changes
	void turnOn();
	void turnOff();
	void toggle();

	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, BulbObject bulb);
	friend std::ofstream& operator<< (std::ostream &out, BulbObject bulb);
};

class LeverObject: public SpritePlus
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
	
	friend std::ifstream& operator>> (std::istream &in, LeverObject lever);
	friend std::ofstream& operator<< (std::ostream &out, LeverObject lever);
};

class PlugObject: public SpritePlus
{
private:
	plugState state_;
	sf::Vector2i from_;
public:
	PlugObject();

	//gets
	plugState getPlugState() const;
	sf::Vector2i getFrom() const;

	//sets
	void setPlugState(plugState state);
	void setFrom(sf::Vector2i from);

	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, PlugObject plug);
	friend std::ofstream& operator<< (std::ostream &out, PlugObject plug);
};


#endif