
#include "..\include\GodMode.h"

GodMode::GodMode(Game *t_game_p, sf::RenderWindow *t_window_p, SettingsInfo *t_settings_p)
{
    game_p = t_game_p;
    window_p = t_window_p;
    settings_p = t_settings_p;
    return;
}

GodMode::~GodMode()
{
    if (game_p != NULL)
    {
        game_p = NULL;
    }
    if (window_p != NULL)
    {
        window_p = NULL;
    }
    if (settings_p != NULL)
    {
        settings_p = NULL;
    }
    return;
}

void GodMode::toggleClipping()
{
	game_p->character.toggleCollision();
}

void GodMode::gotoActRoom(int act, int room)
{
    game_p->update(act, room);
}

void GodMode::setCharEnergy(unsigned short energy)
{
    game_p->character.setEnergy(energy);
}


void GodMode::toggleCollisionBoxVisibility()
{

}

sf::Vector2i GodMode::getCharPosition()
{
	return sf::Vector2i(game_p->character.getPosition().x,game_p->character.getPosition().y);
}

void GodMode::reloadRooms()
{
	std::ifstream stream(game_p->findActFile(game_p->act_));

	game_p->props.load(stream);
	game_p->puzzle.load(stream);
	game_p->story.load(stream);

	stream.close();
}