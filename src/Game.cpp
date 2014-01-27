#include "..\include\Game.h"


void Game::updateRoom(short act, short room)
{
	/*
    act_ = act;
    room_ = room;

    std::vector<sf::IntRect> t_new_room_tiles story.getNewRoomTiles();

	*/
    return;
}

location Game::keyPressed(sf::Keyboard::Key key, location loc)
{
    direction dir = convertKeyToDirection(key);
	if((character.getDirection() != dir) && (dir != direction::NO_DIRECTION))    //TODO: finish this   
	{
	   character.setDirection(dir);
	   character.startWalk();
	}
	else if (character.getDirection() == dir)
	{
		character.startWalk(); //TODO: does this work?
	}

	//TODO: add stuf for lowering arm
}

location Game::keyReleased(sf::Keyboard::Key key, location loc)
{
    direction dir = convertKeyToDirection(key);
	if (dir != NO_DIRECTION && dir == character.getDirection() && character.isWalking())
		character.stopWalk();

	//TODO: add stuff for lowering arm
    switch(key)
    {
	case sf::Keyboard::Up:
    case sf::Keyboard::W:
	case sf::Keyboard::Right:
	case sf::Keyboard::D:
	case sf::Keyboard::Down:
	case sf::Keyboard::S:
	case sf::Keyboard::Left:
	case sf::Keyboard::A:
		character.stopWalk();
        break;
    }
	return loc;
}

void Game::animate()
{

}
