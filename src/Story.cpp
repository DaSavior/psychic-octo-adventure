#include "..\include\Story.h"

Story::Story()
{
	room_ = 0;
}

void Story::update(short room)
{
	room_ = room;
	saveProgress();
}

std::string Story::charWalk(const Character &character)
{
	for (TextTile& tile : walkOverText_[room_])
		if (tile.intersects( character.getWalkCollision()))
			return tile.useTile();

	return "";
}
std::string Story::charInteract(const Character &character)
{
	for (TextTile& tile : interactText_[room_])
		if (tile.intersects( character.getWalkCollision()))
			return tile.useTile();

	return "";
}
short Story::charNewRoomCheck(Character &character)
{
	for (NewRoomTile& tile : newRoomTiles_[room_])
		if (tile.intersects( character.getWalkCollision()))
			return tile.getNextRoom();

	return room_;
}

bool Story::loadProgress();
void Story::saveProgress();
bool Story::load(std::ifstream &in);
void Story::save(std::ofstream &out);



TextTile::TextTile() : sf::IntRect()
{
	text_ = "";
	repeat_ = 0;
}

std::string TextTile::getText() const
{
	return text_;
}
unsigned short TextTile::getRepeat() const
{
	return repeat_;
}

void TextTile::setText(std::string text)
{
	text_ = text;
}
void TextTile::setRepeat(short repeat)
{
	repeat_ = repeat;
}

std::string TextTile::useTile()
{
	if (repeat_ == 0)
		return "";
	if (repeat_ > 0)
		repeat_--;
	return text_;
}
	
bool TextTile::load();
void TextTile::save();
bool TextTile::load(std::ifstream &in);
void TextTile::save(std::ofstream &out);


NewRoomTile::NewRoomTile() : TextTile::TextTile()
{
	nextRoom_ = -1;
	exiting_ = NONE;
}

short NewRoomTile::getNextRoom() const
{
	return nextRoom_;
}
direction NewRoomTile::getExitDirection() const
{
	return exiting_;
}

void NewRoomTile::setNextRoom(short nextRoom)
{
	nextRoom_ = nextRoom;
}
void NewRoomTile::setExitDirection(direction exit)
{
	exiting_ = exit;
}

bool NewRoomTile::load();
void NewRoomTile::save();
bool NewRoomTile::load(std::ifstream &in);
void NewRoomTile::save(std::ofstream &out);
