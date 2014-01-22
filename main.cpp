#include "include\Common.h"
#include "include\Game.h"
#include "include\Menus.h"
#include "include\GodMode.h"
#include "include\Threads.h"
#include <functional>

int main()
{
#pragma region initialize
	bool can_continue = false;

	can_continue = progressFileExists();

	SettingsInfo settings;

	if (can_continue)
		settings.loadFromFile(FILE_PROGRESS);

	Game game;
	MainMenu mainMenu;
	PauseMenu pauseMenu;
	OptionsMenu optionsMenu(&settings);
	sf::Event event;

	sf::RenderWindow window(settings.resolution, settings.window_name, settings.style);
	location	prev_menu = MAIN_MENU,
				loc = MAIN_MENU;


	//HACK: sf::Thread music_thread(musicThreadFunction);
	//HACK: sf::Thread console_thread(std::bind(&godModeConsole, game, window, settings));

	//HACK: console_thread.launch();
	//HACK: music_thread.launch();

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
