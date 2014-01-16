#ifndef STORY_H
#define STORY_H

#include "Common.h"
#include "ClassUtilities.h"

class StoryObject : public sf::IntRect;

class Story: public Inputable
{
private:
    //std::vector<std::vector<sf::IntRect>> refers to room then objects within the room
    std::vector<std::vector<StoryObject>> new_room_tiles;
    std::vector<std::vector<StoryObject>> floor_text;
    unsigned short act_, room_;


public:
	Story();

    std::vector<sf::IntRect> getNewRoomTiles();

	virtual bool loadFromFile();
	virtual bool saveTofile();
};

class StoryObject : public sf::IntRect , public Fileable
{
private:
    sf::Vector2i next_room;
    std::string text;

    unsigned short state; //HACK: dont let the character walk after picking up the book
public:
    std::string getText();
    unsigned short getState();
    sf::Vector2i getNextRoom();

    void setText(std::string t_text);
    void setState(unsigned short t_state);
    void setNextRoom(sf::Vector2i t_next_room);
};

#endif
