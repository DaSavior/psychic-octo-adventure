#ifndef STORY_H
#define STORY_H

#include "Common.h"
#include "ClassUtilities.h"

class Story: public Inputable
{
private:
    //std::vector<std::vector<sf::IntRect>> refers to room then objects within the room
    std::vector<std::vector<StoryObject>> new_room_tiles;
    std::vector<std::vector<StoryObject>> floor_text;

public:
	Story();

    std::vector<std::vector<StoryObject>> getNewRoomTiles() const;
    std::vector<std::vector<StoryObject>> getFloorText() const;

	std::string getActFile() const;

	virtual bool load();
	virtual void save();
	virtual bool load(std::ifstream &in);
	virtual void save(std::ofstream &out);
};

class StoryObject : public sf::IntRect , public Fileable
{
private:
    sf::Vector2i next_room;
    std::string text;

    unsigned short state; //HACK: dont let the character walk after picking up the book
public:
	//gets
    std::string getText() const;
    unsigned short getState() const;
    sf::Vector2i getNextRoom() const;

	//sets
    void setText(std::string t_text);
    void setState(unsigned short t_state);
    void setNextRoom(sf::Vector2i t_next_room);
	
	//virtuals
	virtual bool load();
	virtual void save();
};

#endif
