#include "..\include\Props.h"

#pragma region Props

Props::Props();
void Props::updateRoom(short room)
{
	room_ = room;
	saveProgress();
}

std::string Props::charInteract(const Character &character) const
{
	for (int c = 0; c < propList_[room_].size(); c++)
		if (propList_[room_][c].collides(character.getInteractCollision()))
			return propList_[room_][c].getText();

	return "";
}
bool Props::charCanWalk(const Character &character) const
{
	for (int c = 0; c < propList_[room_].size(); c++)
		if (propList_[room_][c].collides(character.getWalkCollision()))
			return false;

	return true;
}

bool Props::load(int file)
{	
	propList_.clear();

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
bool Props::loadNextRoom(std::istream &stream)
{
	int room;
	std::string blank = "";
	while (blank != "#props")
		stream >> blank;

	stream >> blank >> room;

	int count;
	
	stream >> blank >> count;
	for (int c = 0; c < count; c++)
		stream >> propList_[room][c];

	setTextures(room);
}
void Props::saveProgress()
{
	for (int c = 0; c < propList_.size(); c++)
		progressFile_ += roomSave(c); //TODO: IMPORTANT, when the save functions are all called, progressFile needs to be erased first
}
std::string Props::roomSave(int room)
{
	std::stringstream stream;
	stream << "#props room " << room;

	for (const auto &x : propList_[room])
		stream << x;

	return stream.str();
}
void Props::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int c = 0; c < propList_[room_].size(); c++)
		target.draw(propList_[room_][c], states);
}

#pragma endregion

#pragma region PropObject

PropObject::PropObject() :SpritePlus::SpritePlus()
{
	facing_ = NO_DIRECTION;
	type_ = NO_PROP;
}
direction PropObject::getDirection() const
{
	return facing_;
}
propType PropObject::getType() const
{
	return type_;
}
void PropObject::setDirection(direction facing)
{
	facing_ = facing;
}
void PropObject::setType(propType type)
{
	type_ = type;
}

std::ifstream& operator>> (std::istream &in, PropObject prop)
{
	std::string blank;
	int x, y;
	sf::IntRect r;

	in >> blank >> blank;
	prop.setType(stringToPropType(blank));
	
	std::getline(in, blank, '*');
	
	in >> blank >> blank;
	prop.setDirection(stringToDirection(blank));

		//gelbin

	in >> blank >> x >> y;
	prop.setPosition(x, y);

	in >> blank >> r.left >> r.top >> r.width >> r.height;
	prop.setCollisionRectangle(r);
}
std::ofstream& operator<< (std::ostream &out, PropObject prop);

#pragma endregion