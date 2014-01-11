
#include "Common.h"

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

int main()
{
	/*
#pragma region initialize 
	//TODO: make all variables
	//TODO: make window
	//TODO: make settings
	location loc = MAIN_MENU
#pragma endregion

	while (window.isOpen())
	{

#pragma region Handle Events
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close
			if (type == key)
				if ((event.key.alt) && (event.key.code == tab))
					minimize
			switch (loc)
			{
			case GAME:
				loc = game.input(event, loc);
				break;
			case MAIN_MENU:
				loc = mainMenu.input(event, loc);
				break;
			case PAUSE_MENU:
				loc = pauseMenu.input(event, loc);
				break;
			case OPTIONS_MENU:
				loc = optionsMenu.input(event, loc);
				break;
			}
		}
#pragma endregion
		
#pragma region Draw
		switch (loc)
		{
		case GAME:
			window.draw(game);		
			break;
		case MAIN_MENU:
			window.draw(mainMenu);
			break;
		case PAUSE_MENU:
			window.draw(pauseMenu);
			break;
		case OPTIONS_MENU:
			window.draw(optionsMenu);
			break;
		}
#pragma endregion


	}

	*/


	return 0;
}



