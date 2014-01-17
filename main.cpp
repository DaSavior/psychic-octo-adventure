#include "include\Common.h"
#include "include\Game.h"
#include "include\Menus.h"
#include "include\GodMode.h"
#include <iostream>
#include <functional>

void godModeConsole(Game &t_game_r, sf::RenderWindow &t_window_r, SettingsInfo &t_settings_r);
void musicThreadFunction();

int main()
{
#pragma region initialize
	Game game;
	MainMenu mainMenu;
	PauseMenu pauseMenu;
	OptionsMenu optionsMenu;
	sf::Event event;

	SettingsInfo settings;
	sf::RenderWindow window(settings.resolution, settings.window_name, settings.style);
	location	prev_menu = MAIN_MENU,
				loc = MAIN_MENU;


	//HACK: sf::Thread music_thread(musicThreadFunction);
	//HACK: sf::Thread console_thread(std::bind(&godModeConsole, game, window, settings));

	//HACK: console_thread.launch();

#pragma endregion

	while (window.isOpen())
	{

#pragma region Handle Events
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//if (event.type == sf::Event::KeyPressed)
				//if ((event.key.alt) && (event.key.code == sf::Keyboard::Key::Tab))

			switch (loc) //
			{
			case GAME:
				loc = game.input(event, loc);
				break;
			case MAIN_MENU:
				prev_menu = MAIN_MENU;
				loc = mainMenu.input(event, loc);
				break;
			case PAUSE_MENU:
				prev_menu = PAUSE_MENU;
				loc = pauseMenu.input(event, loc);
				break;
			case OPTIONS_MENU:
				if (event.type == sf::Event::KeyPressed)
					break;
				loc = optionsMenu.input(event, prev_menu);
				break;
			}
		}
#pragma endregion

#pragma region Animate
		switch (loc)
		{
		case GAME:
			game.animate();
			break;
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

	//HACK: console_thread.wait();
	//HACK: music_thread.wait();

	return 0;
}



void godModeConsole(Game &t_game_r, sf::RenderWindow &t_window_r, SettingsInfo &t_settings_r)
{
	GodMode console(Game &t_game_r, sf::RenderWindow &t_window_r, SettingsInfo &t_settings_r);
	unsigned short cmd;

	while (t_window_r.isOpen())
	{
		std::cout << "Cmd" << std::endl
				  << "1: goto act,room" << std::endl
				  << "2: get act, room" << std::endl
				  << "3: toggle clipping" << std::endl
				  << "4: set char energy" << std::endl
				  << "5: load File" << std::endl
				  << "6: save File" << std::endl
				  << "7: toggle Collision Box visibilty" << std::endl
				  << "8: get character position" << std::endl
				  << "9: exit program" << std::endl;

		std::cin >> cmd;


		switch (cmd)
		{
		case 1: //goto act,room
			break;
		case 2: //get act, room
			break;
		case 3: //toggle clipping
			break;
		case 4: //set char energy
			break;
		case 5: //load File
			break;
		case 6: //save File
			break;
		case 7: //toggle Collision Box visibilty
			break;
		case 8: //get character position
			break;
		case 9: //exit program
			break;
		}
	}

}


void musicThreadFunction()
{

}