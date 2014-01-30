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

	if (character.getDirection() == dir && character.canWalk())
		character.startWalk();

	else if((character.getDirection() != dir) && (dir != NO_DIRECTION))
		character.setDirection(dir);

	else if(dir == NO_DIRECTION)
	{
		if (key == sf::Keyboard::Escape)
			loc = PAUSE_MENU;

		else if (key == sf::Keyboard::Space)	//TODO: interact
		{
			if (
			props.charInteract(character)
		}
		else if (key == sf::Keyboard::E)	//give energy
		{
			if (!character.movingArm())
			{
				puzzle.charToPlugEnergy(character);
				character.raiseArm();
			}
		}
		else if (key == sf::Keyboard::Q)	//take energy
		{
			if (!character.movingArm())
			{
				puzzle.charFromPlugEnergy(character);
				character.raiseArm();
			}
		}
	}

	return loc;
}

location Game::keyReleased(sf::Keyboard::Key key, location loc)
{
    direction dir = convertKeyToDirection(key);

	if (character.getDirection() == dir && character.isWalking())
		character.stopWalk(); 

	else if(dir == NO_DIRECTION)
		if (key == sf::Keyboard::Space || (key == sf::Keyboard::E || key == sf::Keyboard::Q))
			character.lowerArm();
			
	return loc;
}

void Game::animate();
