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
	newRoomTiles_.clear();
	interactText_.clear();
	walkOverText_.clear();

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
bool Story::loadNextRoom(std::istream &stream)
{
	int room;
	std::string blank = "";
	while (blank != "#story")
		stream >> blank;

	stream >> blank >> room;

	int count;
	
	stream >> blank >> count;
	for (int c = 0; c < count; c++)
		stream >> interactText_[room][c];

	stream >> blank >> count;
	for (int c = 0; c < count; c++)
		stream >> walkOverText_[room][c];

	stream >> blank >> count;
	for (int c = 0; c < count; c++)
		stream >> newRoomTiles_[room][c];

}
void Story::saveProgress()
{
	for (int c = 0; c < newRoomTiles_.size(); c++)
		progressFile_ += roomSave(c); //TODO: IMPORTANT, when the save functions are all called, progressFile needs to be erased first
}
std::string Story::roomSave(int room)
{
	std::stringstream stream;
	stream << "#story room " << room;

	for (const auto &x : interactText_[room])
		stream << x;
	for (const auto &x : walkOverText_[room])
		stream << x;
	for (const auto &x : newRoomTiles_[room])
		stream << x;

	return stream.str();
}
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

	in >> blank >> tile.left >> tile.top
		>> blank >> tile.width >> tile.height
		>> blank >> tile.repeat_;

	in >> blank;
	std::getline(in, tile.text_, '*');
}
std::ofstream& operator<< (std::ostream &out, TextTile tile)
{
	out << '\n'
		<< "  position " << tile.left << ' ' << tile.top << '\n'
		<< "  size " << tile.width << ' ' << tile.height << '\n'
		<< "  repeat " << tile.repeat_ << '\n'
		<< "  text " << tile.text_ << '*' << '\n';
}

#pragma endregion

#pragma region NewRoomTile

NewRoomTile::NewRoomTile() : TextTile::TextTile()
{
	nextRoom_ = -1;
	exiting_ = NO_DIRECTION;
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
	out << '\n'
		<< "  position " << tile.left << ' ' << tile.top << '\n'
		<< "  size " << tile.width << ' ' << tile.height << '\n'
		<< "  repeat " << tile.repeat_ << '\n'
		<< "  text " << tile.text_ << '*' << '\n'
		<< "  direction " << to_string(tile.exiting_) << '\n';
}

#pragma endregion