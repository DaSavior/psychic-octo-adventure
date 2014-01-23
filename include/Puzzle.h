#ifndef PUZZLE_H
#define PUZZLE_H

#include "Common.h"
#include "ClassUtilities.h"
#include "Character.h"

class Puzzle: public Fileable
{
private:
    //std::vector<std::vector<sf::IntRect>> refers to room then objects within the room
	std::vector<std::vector<DoorObject>> doors_;
	std::vector<std::vector<CircuitObject>> circuits_;
	std::vector<std::vector<WireObject>> wires_;
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
	virtual bool loadProgress();
	virtual void saveProgress();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class DoorObject: public Fileable, public SpritePlus
{
private:
	short answer_;
	sf::Text doorNumber_;

	direction facing_;
	short circuitFrom_;

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
	virtual bool loadProgress();
	virtual void saveProgress();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

class WireObject: public Fileable, public sf::RectangleShape	//HACK: Try to make a "CurveShape" instead of rectangle shape, allowing multiple points in any orientation, curveshape can hold multiple "LineShapes"
{
private:

public:
	WireObject();
	WireObject(std::ifstream &file);

	void setState(leverState state);

	//virtuals
	virtual bool loadProgress();
	virtual void saveProgress();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};


class CircuitObject: public Fileable, public sf::Drawable
{
	friend Puzzle;

private:
	PlugObject plug_;
	std::vector<BulbObject> bulbs_;
	LeverObject lever_;

	unsigned short circuitNumber_;

public:
	CircuitObject();
	CircuitObject(std::ifstream &file);

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
	virtual bool loadProgress();
	virtual void saveProgress();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states);
};

class BulbObject: public Fileable, public SpritePlus
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
	virtual bool loadProgress();
	virtual void saveProgress();
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
	virtual bool loadProgress();
	virtual void saveProgress();
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
	void setFrom(sf::Vector2i from);

	//virtuals
	virtual bool loadProgress();
	virtual void saveProgress();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};


#endif