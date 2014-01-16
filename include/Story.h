#ifndef STORY_H
#define STORY_H

#include "Common.h"
#include "ClassUtilities.h"

class Story: public Inputable
{
private:
    std::vector<sf::IntRect> new_room_tiles;

public:
	Story();

    std::vector<sf::IntRect> getNewRoomTiles();

	virtual bool loadFromFile();
	virtual bool saveTofile();
};

#endif
