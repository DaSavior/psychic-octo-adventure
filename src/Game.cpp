#include "..\include\Game.h"


void Game::update(int act, int room)
{
    act_ = act;
    room_ = room;



    std::vector<sf::IntRect> t_new_room_tiles story.getNewRoomTiles();



    return;
}

location Game::keyPressed(sf::Keyboard::Key key, location loc)
{
    /*
    direction dir = convertKeyToDirection(key);
    if((character.getDirection() != dir) && (dir != direction::NONE))    //TODO: finish this
        character.setDirection(dir);
    */
}

location Game::keyReleased(sf::Keyboard::Key key, location loc)
{
    /*
    switch(key)
    {
    case 'up':
    case 'W':
        char.startWalk();
        break;
    case:
        break;
    case:
        break;
    case:
        break;
    }
    */
}
