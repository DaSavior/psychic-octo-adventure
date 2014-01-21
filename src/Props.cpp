#include "..\include\Props.h"

#pragma region Props

Props::Props();
void Props::update(short room)
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

bool Props::loadProgress();
void Props::saveProgress();
bool Props::load(std::ifstream &in);
void Props::save(std::ofstream &out);
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
}
	
std::string PropObject::getText() const;
	
void PropObject::setText(std::string text);

bool PropObject::load();
void PropObject::save();
bool PropObject::load(std::ifstream &in);
void PropObject::save(std::ofstream &out);

#pragma endregion