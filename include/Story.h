#ifndef STORY_H
#define STORY_H

#include "Common.h"
#include "ClassUtilities.h"

class Story: public Inputable
{
private:
    //std::vector<std::vector<sf::IntRect>> refers to room then objects within the room
	std::vector<std::vector<NewRoomTile>> newRoomTiles_;
	std::vector<std::vector<TextTile>> interactText_;
	std::vector<std::vector<TextTile>> walkOverText_;
	short room_;

public:
	Story();

	void update(short room);

	//for character
	std::string charWalk(const Character &character);		//for text
	std::string charInteract(const Character &character);	//for text
	short charNewRoomCheck(Character &character);			//for new room tiles, will move character if there is one and returns the room of the character or NEXTACT

	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

class NewRoomTile : public TextTile
{
private:
    short nextRoom_;	//999 = next act //HACK: could be a define
	direction exiting_;	//for where the character will move after

public:
	//gets
    short getNextRoom() const;
	direction getExitDirection() const;

	//sets
    void setNextRoom(short nextRoom);
	void setExitDirection(direction exit);

	//virtuals
	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

class TextTile : public sf::IntRect , public Fileable
{
private:
    std::string text_;
	short repeat; //repeat forever if == -1
public:
	//gets
    std::string getText() const;
    unsigned short getState() const;

	//sets
    void setText(std::string text);
    void setState(unsigned short state);

	std::string useTile();//return text and lowers repeat
	
	//virtuals
	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

#endif
