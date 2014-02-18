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
    direction dir = keyToDirection(key);

	if (character_.getDirection() == dir && character_.canWalk())
		character_.startWalk();

	else if((character_.getDirection() != dir) && (dir != NO_DIRECTION))
		character_.setDirection(dir);

	else if(dir == NO_DIRECTION)
	{
		if (key == sf::Keyboard::Escape)
			loc = PAUSE_MENU;

		else if (key == sf::Keyboard::Space)	//basic interact
		{
			if (textbox_.isOpen())
			{
				if (textbox_.hasNextLine())
					textbox_.finishLine();
				else if (textbox_.hasScroll())
					textbox_.scrollText();
				else
					textbox_.close();
			}
			else
			{
				textbox_.setScroll(story_.charInteract(character_));
				if (textbox_.hasScroll())
					textbox_.scrollText();
			}
			puzzle_.charInteract(character_);
		}
		else if (key == sf::Keyboard::E)	//give energy
		{
			if (!character_.movingArm())
			{
				puzzle_.charToPlugEnergy(character_);
				character_.raiseArm();
			}
		}
		else if (key == sf::Keyboard::Q)	//take energy
		{
			if (!character_.movingArm())
			{
				puzzle_.charFromPlugEnergy(character_);
				character_.raiseArm();
			}
		}
	}

	return loc;
}

location Game::keyReleased(sf::Keyboard::Key key, location loc)
{
    direction dir = keyToDirection(key);

	if (character_.getDirection() == dir && character_.isWalking())
		character_.stopWalk(); 

	else if(dir == NO_DIRECTION)
		if (key == sf::Keyboard::Space || (key == sf::Keyboard::E || key == sf::Keyboard::Q))
			character_.lowerArm();
			
	return loc;
}

void Game::animate();
