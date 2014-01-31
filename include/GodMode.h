#ifndef GODMODE_H
#define GODMODE_H

#include "Common.h"
#include "Game.h"

class GodMode
{
private:
    Game *game_p;
    sf::RenderWindow *window_p;
    SettingsInfo *settings_p;

public:
	GodMode(Game *t_game_p, sf::RenderWindow *t_window_p, SettingsInfo *t_settings_p);
	~GodMode();

	void toggleClipping();
	void gotoActRoom(int act, int room);
	void setCharEnergy(unsigned short energy);
	void load(int file);
	void save(int file);
	void toggleCollisionBoxVisibility();
    sf::Vector2i getCharPosition();
	void reloadRooms();
};


#endif
