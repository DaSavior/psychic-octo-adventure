#ifndef STORY_H
#define STORY_H

#include "Common.h"
#include "ClassUtilities.h"
#include "Character.h"

//TODO: IMPORTANT, when will character update for the new room, because it needs to know things from story (the new room tiles)

class Story: public Inputable, public Fileable
{
private:
    //std::vector<std::vector<sf::IntRect>> refers to room then objects within the room
	std::vector<std::vector<NewRoomTile>> newRoomTiles_;
	std::vector<std::vector<TextTile>> interactText_;
	std::vector<std::vector<TextTile>> walkOverText_;
	short room_;

public:
	Story();

	void updateRoom(short room);

	//for character
	std::string charWalk(const Character &character);		//for text
	std::string charInteract(const Character &character);	//for text
	short charNewRoomCheck(Character &character);			//for new room tiles, will move character if there is one and returns the room of the character or NEXT_ACT

	
	virtual bool load(int file);
	virtual void saveProgress();
	virtual bool loadRoom(int room);
	virtual void saveRoom(int room);
};

class TextTile : public sf::IntRect , public Fileable
{
protected:
    std::string text_;
	short repeat_; //repeat forever if == -1
public:
	TextTile();

	//gets
    std::string getText() const;
    unsigned short getRepeat() const;

	//sets
    void setText(std::string text);
    void setRepeat(short repeat);

	std::string useTile();//return text and lowers repeat
	
	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, TextTile tile);
	friend std::ofstream& operator<< (std::ostream &out, TextTile tile);
};

class NewRoomTile : public TextTile
{
private:
    short nextRoom_;	//999 = next act 
	direction exiting_;	//for where the character will move after

public:
	NewRoomTile();

	//gets
    short getNextRoom() const;
	direction getExitDirection() const;

	//sets
    void setNextRoom(short nextRoom);
	void setExitDirection(direction exit);

	//virtuals
	
	friend std::ifstream& operator>> (std::istream &in, NewRoomTile tile);
	friend std::ofstream& operator<< (std::ostream &out, NewRoomTile tile);
};

#endif
