
#include "Common.h"
#include "Game.h"
#include <iostream>


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
		case 9:
			//console.close(); TODO: add close function to GodMode to close the window and the console;
			return;
			break;
		}
	}

}


void musicThreadFunction()
{

}
