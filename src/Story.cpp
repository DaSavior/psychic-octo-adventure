#include "..\include\Story.h"

#pragma region Story

Story::Story()
{
	room_ = 0;
}

void Story::updateRoom(short room)
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

bool Story::load(int file)
{
	int count;
	while (loadRoom(count))
		count++;
	
}
void Story::save(int file);
bool Story::loadRoom(int room);
void Story::saveRoom(int room);
#pragma endregion

#pragma region TextTile

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
	
std::ifstream& operator>> (std::istream &in, TextTile tile)
{
	std::string blank;
	int x, y;

	in >> blank >> tile.left >> tile.top
		>> blank >> tile.width >> tile.height
		>> blank >> tile.repeat_;

	in >> blank;
	std::getline(in, tile.text_, '*');
}
std::ofstream& operator<< (std::ostream &out, TextTile tile)
{
	out << "  position " << tile.left << ' ' << tile.top << '\n'
		<< "  size " << tile.width << ' ' << tile.height << '\n'
		<< "  repeat " << tile.repeat_ << '\n'
		<< "  text " << tile.text_ << '*' << '\n'
}

#pragma endregion

#pragma region NewRoomTile

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

std::ifstream& operator>> (std::istream &in, NewRoomTile tile)
{
	std::string blank;
	int x, y;

	in >> blank >> tile.left >> tile.top
		>> blank >> tile.width >> tile.height
		>> blank >> tile.repeat_;

	in >> blank;
	std::getline(in, tile.text_, '*');

	in >> blank >> blank;
	tile.exiting_ = stringToDirection(blank);
}
std::ofstream& operator<< (std::ostream &out, NewRoomTile tile)
{
	out << "  position " << tile.left << ' ' << tile.top << '\n'
		<< "  size " << tile.width << ' ' << tile.height << '\n'
		<< "  repeat " << tile.repeat_ << '\n'
		<< "  text " << tile.text_ << '*' << '\n'
		<< "  direction " << directionToString(tile.exiting_) << '\n';
}

#pragma endregion