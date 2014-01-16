#ifndef COMMON_H
#define COMMON_H

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>

#pragma region enums

enum location {GAME, MAIN_MENU, PAUSE_MENU, OPTIONS_MENU};
enum direction {NONE = -1, NORTH, EAST, SOUTH, WEST};

#pragma endregion

#pragma region defines

#define UNCOLIDABLE_BOX sf::IntRect()
#define CHAR_COL_BOX sf::IntRect(100,100,100,100)

#pragma endregion

#pragma region functions

direction convertKeyToDirection(sf::Keyboard::Key key)
{
    direction dir;
    switch(key)
    {
    case sf::Keyboard::UP:
    case sf::Keyboard::W:
        dir = NORTH;
        break;
    case sf::Keyboard::RIGHT:
    case sf::Keyboard::D:
        dir = EAST;
        break;
    case sf::Keyboard::DOWN:
    case sf::Keyboard::S:
        dir = SOUTH;
        break;
    case sf::Keyboard::LEFT:
    case sf::Keyboard::A:
        dir = WEST;
        break;
    default:
        dir = NONE;
        break;
    }
    return dir;
}

#pragma endregion

#pragma region structs

struct SettingsInfo
{
	SettingsInfo(sf::VideoMode win_res = sf::VideoMode(800, 600), unsigned short vol = 50, sf::Uint32 t_style = sf::Style::Fullscreen, std::string window_title = "Psychosis")
	{
		window_name = window_title;
		resolution = win_res;
		style = t_style;
		if (vol >= 100)
			volume = 100;
		else
			volume = vol;
	}
	std::string window_name;
	sf::VideoMode resolution;
	unsigned short volume;
	sf::Uint32 style;
};

#pragma endregion



#endif



