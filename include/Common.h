#ifndef COMMON_H
#define COMMON_H

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>

#pragma region enums

enum location {GAME, MAIN_MENU, PAUSE_MENU, OPTIONS_MENU};

#pragma endregion

#pragma region defines



#pragma endregion

#pragma region functions



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



