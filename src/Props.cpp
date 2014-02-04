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

bool Props::load(int file);
void Props::save(int file);
void Props::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (int c = 0; c < propList_[room_].size(); c++)
		target.draw(propList_[room_][c], states);
}

#pragma endregion

#pragma region PropObject

PropObject::PropObject() :SpritePlus::SpritePlus()
{
	text_ = "";
	facing_ = NO_DIRECTION;
	type_ = NO_OBJECT;
}
	
std::string PropObject::getText() const
{
	return text_;
}
direction PropObject::getDirection() const
{
	return facing_;
}
propType PropObject::getType() const
{
	return type_;
}
	
void PropObject::setText(std::string text)
{
	text_ = text;
}
void PropObject::setDirection(direction facing)
{
	facing_ = facing;
}
void PropObject::setType(propType type)
{
	type_ = type;
}

std::ifstream& operator>> (std::istream &in, PropObject prop);
std::ofstream& operator<< (std::ostream &out, PropObject prop);

#pragma endregion