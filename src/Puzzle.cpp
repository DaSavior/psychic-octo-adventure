#include "..\include\Puzzle.h"

//TODO: define >> and << for objects

#pragma region Puzzle

Puzzle::Puzzle()
{
	room_ = 0;
}

void Puzzle::updateRoom(short room)
{
	room_ = room;
}

bool Puzzle::charToPlugEnergy(Character &character)
{
	for (CircuitObject &circuit : circuits_[room_])
		if (circuit.charToPlugEnergy(character))
			return true;

	return false;
}
bool Puzzle::charFromPlugEnergy(Character &character)
{
	for (CircuitObject &circuit : circuits_[room_])
		if (circuit.charFromPlugEnergy(character))
			return true;
	
	return false;
}
bool Puzzle::charInteract(const Character &character) 
{
	for (CircuitObject &circuit : circuits_[room_])
		if (circuit.charInteract(character))
			return LEVER;

	return false;
}
bool Puzzle::charCanWalk(const Character &character) const
{
	for (const CircuitObject &circuit : circuits_[room_])
		if (circuit.charCanWalk(character))
			return false;

	for (const DoorObject &door : doors_[room_])
		if (door.collides(character.getWalkCollision()))
			return false;

	return true;
}

bool Puzzle::load(int file)
{	
	doors_.clear();
	circuits_.clear();
	wires_.clear();

	std::stringstream checkingFile;
	if (file <= 0)
		checkingFile << progressFile_;
	else
		checkingFile << actFiles_[file];

	if (!loadNextRoom(checkingFile))
		return false;
	while (loadNextRoom(checkingFile));

	return true;
}
bool Puzzle::loadNextRoom(std::istream &stream)
{
	int room;
	std::string blank = "";
	while (blank != "#puzzle")
		stream >> blank;

	stream >> blank >> room;

	int count;
	
	stream >> blank >> count;
	for (int c = 0; c < count; c++)
		stream >> doors_[room][c];

	stream >> blank >> count;
	for (int c = 0; c < count; c++)
		stream >> circuits_[room][c];

	 makeWires(room);
}
void Puzzle::saveProgress();
void Puzzle::saveRoom(int room);

void Puzzle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const CircuitObject &circuit : circuits_[room_])
		target.draw(circuit, states);

	for (const DoorObject &door : doors_[room_])
		target.draw(door, states);

	for (const WireObject &wire : wires_[room_])
		target.draw(wire, states);
}

#pragma endregion

#pragma region Door

//TODO: figure out this weird error
DoorObject::DoorObject()
{
	setAnswer(0);
	setFacing(SOUTH);
	setCircuitFrom(0);
}

void DoorObject::fit()
{
	sf::Vector2f point = getCenter(getGlobalBounds());
	point.x -= 5;
	point.y -= 20;
	doorNumber_.setPosition(point);
}

short DoorObject::getAnswer() const
{
	return answer_;
}
direction DoorObject::getFacing() const
{
	return facing_;
}
short DoorObject::getCircuitFrom() const
{
	return circuitFrom_;
}

void DoorObject::setAnswer(short answer)
{
	answer_ = answer;
	fit();
}
void DoorObject::setFacing(direction facing)
{
	setFrame(getFrame().x, (int)facing);
}
void DoorObject::setCircuitFrom(short from)
{
	circuitFrom_ = from;
}

bool DoorObject::isOpen() const
{
	return (getFrame().x == 1);
}
bool DoorObject::checkAnswer(short answer) const
{
	return (answer_ == answer);
}

void DoorObject::open()
{
	setFrame(1, getFrame().y);
}
void DoorObject::close()
{
	setFrame(0, getFrame().y);
}

std::ifstream& operator>> (std::istream &in, DoorObject door);
std::ofstream& operator<< (std::ostream &out, DoorObject door);

void DoorObject::draw(sf::RenderTarget &target, sf::RenderStates states) const;

#pragma endregion

#pragma region Wire

WireObject::WireObject()
{
	setState (NO_LEVER);
}

void WireObject::setState(leverState state)
{
	switch (state)
	{
	case NEUTRAL:
		setColor(sf::Color(150,150,150));
		break;
	case NO_LEVER:
	case POSITIVE:
		setColor(sf::Color::Green);
		break;
	case NEGATIVE:
		setColor(sf::Color::Red);
		break;
	}
}

std::ifstream& operator>> (std::istream &in, WireObject wire);
std::ofstream& operator<< (std::ostream &out, WireObject wire);

#pragma endregion

#pragma region Circuit

CircuitObject::CircuitObject()
{
	circuitNumber_ = 0;
}

unsigned short CircuitObject::getCircuitNumber() const
{
	return circuitNumber_;
}
unsigned short CircuitObject::getEnergy() const
{
	int energy = 0;

	for (int c = 0; c < bulbs_.size(); c--)
	{
		if (bulbs_[c].isOn())
			energy += pow(2, c);
	}

	return energy;

}
unsigned short CircuitObject::getMaxEnergy() const
{
	return (pow(2, bulbs_.size()) -1);
}
unsigned short CircuitObject::getSpace() const
{
	return (getMaxEnergy() - getEnergy());
}
short CircuitObject::getOutput() const
{
	switch (lever_.getLeverState())
	{
	case NEUTRAL:
		return 0;
	case NO_LEVER:
	case POSITIVE:
		return getEnergy();
	case NEGATIVE:
		return (-1 * getEnergy());
	}
	return 0;
}
std::vector<sf::Vector2i> CircuitObject::getCenterPoints () const // ITS NOT PARSING AAAAAAAAAAAAAAAAAAAAA
{
	std::vector<sf::Vector2i> centers;
	
	//ITS NOT PARSING AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	
}

bool CircuitObject::setEnergy(unsigned short energy)
{
	if (energy > getMaxEnergy())
		return false;
	if (energy == getEnergy())
		return true;

	for (int c = bulbs_.size()-1; c >= 0; c--)
	{
		if (pow(2, c) > energy)
		{
			energy -= pow(2, c);
			bulbs_[c].turnOn();
		}
		else
			bulbs_[c].turnOff();
	}

	return true;
}
void CircuitObject::setCircuitNumber(short number)
{
	circuitNumber_ = number;
}

bool CircuitObject::hasEnergy() const
{
	return (getEnergy() > 0);
}
bool CircuitObject::hasEnergy() const
{
	return (getSpace() > 0);
}
bool CircuitObject::collides(sf::IntRect globalRect) const
{
	if (lever_.collides(globalRect))
		return true;
	if (plug_.collides(globalRect))
		return true;
	for (BulbObject& bulb : bulbs_)
		if (bulb.collides(globalRect))
			return true;

	return false;
}

bool CircuitObject::addEnergy(unsigned short energy)
{
	if (energy  >  getSpace())
		return false;

	setEnergy(getEnergy() + energy);
}
bool CircuitObject::removeEnergy(unsigned short energy)
{
	if (energy > getEnergy())
		return false;

	setEnergy(getEnergy() - energy);
	return true;
}

bool CircuitObject::charToPlugEnergy(Character &character)
{
	if (plug_.collides(character.getWalkCollision()) 
		&& character.hasEnergy() && hasSpace())
	{
		character.removeEnergy(1);
		addEnergy(1);
		return true;
	}

	return false;
}
bool CircuitObject::charFromPlugEnergy(Character &character)
{
	if (plug_.collides(character.getWalkCollision()) 
		&& hasEnergy())
	{
		character.addEnergy(1);
		removeEnergy(1);
		return true;
	}

	return false;
}
bool CircuitObject::charInteract(const Character &character)
{
	if (!lever_.collides(character.getInteractCollision()) || lever_.getState() == NO_LEVER)
		return false;

	lever_.toggleState();
	return true;
}
bool CircuitObject::charCanWalk(const Character &character) const
{
	if (lever_.collides(character.getWalkCollision()))
		return true;
	if (plug_.collides(character.getWalkCollision()))
		return true;
	for (BulbObject& bulb : bulbs_)
		if (bulb.collides(character.getWalkCollision()))
			return true;

	return false;

}

	
std::ifstream& operator>> (std::istream &in, CircuitObject circuit);
std::ofstream& operator<< (std::ostream &out, CircuitObject circuit);

void CircuitObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(lever_, states);
	for (BulbObject& bulb : bulbs_)
		target.draw(bulb, states);
	target.draw(plug_, states);
}

#pragma endregion

#pragma region Bulbs

BulbObject::BulbObject() : SpritePlus::SpritePlus()
{

};

bool BulbObject::isOn() const
{
	return (getFrame().x == 1);
}

void BulbObject::turnOn()
{
	setFrame(1,0);
}
void BulbObject::turnOff()
{
	setFrame(0,0);
}
void BulbObject::toggle()
{
	if (isOn())
		turnOff();
	else
		turnOn();
}

std::ifstream& operator>> (std::istream &in, BulbObject bulb);
std::ofstream& operator<< (std::ostream &out, BulbObject bulb);

#pragma endregion

#pragma region Lever

LeverObject::LeverObject() : SpritePlus::SpritePlus()
{

}

leverState LeverObject::getLeverState() const
{
	return state_;
}

void LeverObject::setLeverState(leverState state)
{
	state_ = state;
	setFrame((int)state, 0);
}

void LeverObject::toggleState()
{
	switch (state_)
	{
	case NEGATIVE:
		setLeverState(NEUTRAL);
		break;
	case NEUTRAL:
		setLeverState(POSITIVE);
		break;
	case POSITIVE:
		setLeverState(NEGATIVE);
		break;
	}
}

std::ifstream& operator>> (std::istream &in, LeverObject lever);
std::ofstream& operator<< (std::ostream &out, LeverObject lever);

#pragma endregion

#pragma region PlugObject

PlugObject::PlugObject() : SpritePlus::SpritePlus()
{

};

plugState PlugObject::getPlugState() const
{
	return state_;
}
sf::Vector2i PlugObject::getFrom() const
{
	return from_;
}

void PlugObject::setPlugState(plugState state)
{
	state_ = state;
}
void PlugObject::setFrom(sf::Vector2i from)
{
	from_ = from;
}

std::ifstream& operator>> (std::istream &in, PlugObject plug);
std::ofstream& operator<< (std::ostream &out, PlugObject plug);

#pragma endregion