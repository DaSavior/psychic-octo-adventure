#include "..\include\Menus.h"

#pragma region MainMenu

MainMenu::MainMenu();

location MainMenu::mousePressed(sf::Vector2i mouse_pos, location loc)
{
	if (newGame_.contains(mouse_pos))
	{
		std::ofstream file;
		file.open(FILE_PROGRESS);
		file.close();
		
		return GAME;
	}
	if (continue_.contains(mouse_pos))
		return GAME;
	if (options_.contains(mouse_pos))
		return OPTIONS_MENU;
	if (close_.contains(mouse_pos))
		return NO_LOCATION;
}
location MainMenu::mouseMoved(sf::Vector2i mouse_pos, location loc)
{
	menu_option = MAIN_NO_CHOICE;
	if (!newGame_.contains(mouse_pos))
		newGame_.removeHighlight();
	if (!continue_.contains(mouse_pos) && canContinue_)
		continue_.removeHighlight();
	if (!options_.contains(mouse_pos))
		options_.removeHighlight();
	if (!close_.contains(mouse_pos))
		close_.removeHighlight();

	if (!canContinue_)
		continue_.highlight(COLOR_GRAY);

	if (newGame_.contains(mouse_pos))
		newGame_.highlight(COLOR_MOUSE_OVER);
	if (continue_.contains(mouse_pos) && canContinue_)
		continue_.highlight(COLOR_MOUSE_OVER);
	if (options_.contains(mouse_pos))
		options_.highlight(COLOR_MOUSE_OVER);
	if (close_.contains(mouse_pos))
		close_.highlight(COLOR_MOUSE_OVER);

	return loc;
}
location MainMenu::keyPressed(sf::Keyboard::Key key, location loc)
{
	std::ofstream file;

	newGame_.removeHighlight();
	options_.removeHighlight();
	close_.removeHighlight();
	
	if (!canContinue_)
		continue_.highlight(COLOR_GRAY);
	else
		continue_.removeHighlight();

	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
	{
		switch (menu_option)
		{
		case NEW_GAME:
			menu_option = CLOSE;
			close_.highlight(COLOR_MOUSE_OVER);
			break;
		case CONTINUE:
			menu_option = NEW_GAME;
			newGame_.highlight(COLOR_MOUSE_OVER);
			break;
		case MAIN_OPTIONS:
			if (canContinue_)
			{
				menu_option = CONTINUE;
				continue_.highlight(COLOR_MOUSE_OVER);
			}
			else
			{
				menu_option = NEW_GAME;
				newGame_.highlight(COLOR_MOUSE_OVER);
			}
			break;
		case CLOSE:
			menu_option = MAIN_OPTIONS;
			options_.highlight(COLOR_MOUSE_OVER);
			break;
		case MAIN_NO_CHOICE:
			menu_option = CLOSE;
			close_.highlight(COLOR_MOUSE_OVER);
			break;
		}
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
	{
		switch (menu_option)
		{
		case MAIN_NO_CHOICE:
			menu_option = NEW_GAME;
			close_.highlight(COLOR_MOUSE_OVER);
			break;
		case NEW_GAME:
			if (canContinue_)
			{
				menu_option = CONTINUE;
				continue_.highlight(COLOR_MOUSE_OVER);
			}
			else
			{
				menu_option = MAIN_OPTIONS;
				options_.highlight(COLOR_MOUSE_OVER);
			}
			break;
		case CONTINUE:
			menu_option = MAIN_OPTIONS;
			options_.highlight(COLOR_MOUSE_OVER);
			break;
		case MAIN_OPTIONS:
			menu_option = CLOSE;
			close_.highlight(COLOR_MOUSE_OVER);
			break;
		case CLOSE:
			menu_option = NEW_GAME;
			close_.highlight(COLOR_MOUSE_OVER);
			break;
		}
	}
	else if (key == sf::Keyboard::Return)
	{
		switch (menu_option)
		{
		case NEW_GAME:
			file.open(FILE_PROGRESS);
			file.close();
			return GAME;
		case CONTINUE:
			return GAME;
		case MAIN_OPTIONS:
			return OPTIONS_MENU;
		case CLOSE:
			return EXIT_GAME;
		}
	}
	else if (key == sf::Keyboard::Escape)
	{
		return EXIT_GAME;
	}

	return MAIN_MENU;
}
void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(newGame_, states);
	target.draw(continue_, states);
	target.draw(options_, states);
	target.draw(close_, states);
}

#pragma endregion

#pragma region OptionsMenu

OptionsMenu::OptionsMenu(SettingsInfo *t_setting_p, sf::RenderWindow *t_window_p)
{
	changed = false;
	setting_p = t_setting_p;
	t_setting = *setting_p;
	window_p = t_window_p;
}
OptionsMenu::~OptionsMenu()
{
	if (setting_p == NULL)
		setting_p = NULL;
	if (window_p == NULL)
		window_p = NULL;
}

location OptionsMenu::mousePressed(sf::Vector2i mouse_pos, location loc)
{
	if (fullScreenToggle_.contains(mouse_pos))
	{
		if (t_setting.style == sf::Style::Fullscreen)
			t_setting.style = sf::Style::Close;
		else
			t_setting.style = sf::Style::Fullscreen;
	}
	if (volume_.contains(mouse_pos))
	{
		setting_p->volume = ((setting_p->volume+25) % 125);
	}
	if (resolution_up_.contains(mouse_pos))
	{
		int height = t_setting.resolution.height, width = t_setting.resolution.width;
		switch (width)
		{
		case 800:  //600
			t_setting.resolution = sf::VideoMode(1024,768);
			break;
		case 1024: //768
			t_setting.resolution = sf::VideoMode(1152,864);
			break;		
		case 1152: //864
			t_setting.resolution = sf::VideoMode(1280,720);
			break;		
		case 1280: //720 800 960 1024
			switch (height)
			{
			case 720:
				t_setting.resolution = sf::VideoMode(1280,800);
				break;
			case 800:
				t_setting.resolution = sf::VideoMode(1280,960);
				break;
			case 960:
				t_setting.resolution = sf::VideoMode(1280,1024);
				break;
			case 1024:
				t_setting.resolution = sf::VideoMode(1360,768);
				break;
			}
			break;
		case 1360: //768
			t_setting.resolution = sf::VideoMode(1366,768);
			break;
		case 1366: //768
			t_setting.resolution = sf::VideoMode(1400,1050);
			break;
		case 1400: //1050
			t_setting.resolution = sf::VideoMode(1440,900);
			break;
		case 1440: //900
			t_setting.resolution = sf::VideoMode(1600,900);
			break;
		case 1600: //900 1200
			switch (height)
			{
			case 900:
				t_setting.resolution = sf::VideoMode(1600,1200);
				break;
			case 1200:
				t_setting.resolution = sf::VideoMode(1680,1050);
				break;
			}
			break;
		case 1680: //1050
			t_setting.resolution = sf::VideoMode(1920,1080);
			break;
		case 1920: //1080 1200
			switch (height)
			{
			case 1080:
				t_setting.resolution = sf::VideoMode(1920,800);
				break;
			case 1200:
				t_setting.resolution = sf::VideoMode(800,600);
				break;
			}
			break;
		}
	}
	if (resolution_down_.contains(mouse_pos))
	{
		int height = t_setting.resolution.height, width = t_setting.resolution.width;
		switch (width)
		{
		case 800:  //600
			t_setting.resolution = sf::VideoMode(1920,800);
			break;
		case 1024: //768
			t_setting.resolution = sf::VideoMode(800,600);
			break;		
		case 1152: //864
			t_setting.resolution = sf::VideoMode(1024,768);
			break;		
		case 1280: //720 800 960 1024
			switch (height)
			{
			case 720:
				t_setting.resolution = sf::VideoMode(1152,864); 
				break;
			case 800:
				t_setting.resolution = sf::VideoMode(1280,720); 
				break;
			case 960:
				t_setting.resolution = sf::VideoMode(1280,800); 
				break;
			case 1024:
				t_setting.resolution = sf::VideoMode(1280,960); 
				break;
			}
			break;
		case 1360: //768
			t_setting.resolution = sf::VideoMode(1280,1024); 
			break;
		case 1366: //768
			t_setting.resolution = sf::VideoMode(1360,768); 
			break;
		case 1400: //1050
			t_setting.resolution = sf::VideoMode(1366,768); 
			break;
		case 1440: //900
			t_setting.resolution = sf::VideoMode(1400,1050); 
			break;
		case 1600: //900 1200
			switch (height)
			{
			case 900:
				t_setting.resolution = sf::VideoMode(1440,900); 
				break;
			case 1200:
				t_setting.resolution = sf::VideoMode(1600,900); 
				break;
			}
			break;
		case 1680: //1050
			t_setting.resolution = sf::VideoMode(1600,1200); 
			break;
		case 1920: //1080 1200
			switch (height)
			{
			case 1080:
				t_setting.resolution = sf::VideoMode(1680,1050); 
				break;
			case 1200:
				t_setting.resolution = sf::VideoMode(1920,1080); 
				break;
			}
			break;
		}
		changed = false;
	}
	if (accept_.contains(mouse_pos))
	{
		*setting_p = t_setting;
		if (!changed)
		{
			window_p->create(setting_p->resolution, setting_p->window_name, setting_p->style);
		}
		changed = false;
		return loc;
	}
	if (cancel_.contains(mouse_pos))
	{
		if (changed)
		{
			window_p->create(setting_p->resolution, setting_p->window_name, setting_p->style);
		}
		changed = false;
		return loc;
	}
	if (apply_.contains(mouse_pos))
	{
		changed = true;
		window_p->create(t_setting.resolution, t_setting.window_name, t_setting.style);
	}

	return OPTIONS_MENU;
}
location OptionsMenu::mouseMoved(sf::Vector2i mouse_pos, location loc)
{
	menu_option = OPTION_NO_CHOICE;
	if (!fullScreenToggle_.contains(mouse_pos))
		fullScreenToggle_.removeHighlight();
	if (!volume_.contains(mouse_pos))
		volume_.removeHighlight();
	if (!resolution_up_.contains(mouse_pos))
		resolution_up_.removeHighlight();
	if (!resolution_down_.contains(mouse_pos))
		resolution_down_.removeHighlight();
	if (!accept_.contains(mouse_pos))
		accept_.removeHighlight();
	if (!cancel_.contains(mouse_pos))
		cancel_.removeHighlight();
	if (!apply_.contains(mouse_pos))
		apply_.removeHighlight();

	if (fullScreenToggle_.contains(mouse_pos))
		fullScreenToggle_.highlight(COLOR_MOUSE_OVER);
	if (volume_.contains(mouse_pos))
		volume_.highlight(COLOR_MOUSE_OVER);
	if (resolution_up_.contains(mouse_pos))
		resolution_up_.highlight(COLOR_MOUSE_OVER);
	if (resolution_down_.contains(mouse_pos))
		resolution_down_.highlight(COLOR_MOUSE_OVER);
	if (accept_.contains(mouse_pos))
		accept_.highlight(COLOR_MOUSE_OVER);
	if (cancel_.contains(mouse_pos))
		cancel_.highlight(COLOR_MOUSE_OVER);
	if (apply_.contains(mouse_pos))
		apply_.highlight(COLOR_MOUSE_OVER);

	return OPTIONS_MENU;
}
location OptionsMenu::keyPressed(sf::Keyboard::Key key, location loc) //TODO: add highlights
{
	fullScreenToggle_.removeHighlight();
	volume_.removeHighlight();
	resolution_up_.removeHighlight();
	resolution_down_.removeHighlight();
	accept_.removeHighlight();
	cancel_.removeHighlight();
	apply_.removeHighlight();

	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
	{
		switch (menu_option)
		{
		case FULL_SCREEN_TOGGLE:
			menu_option = RESOLUTION_BUTTON;
		case VOLUME:
			menu_option = FULL_SCREEN_TOGGLE;
		case RESOLUTION_BUTTON:
			menu_option = VOLUME;
		case OPTION_NO_CHOICE:
			menu_option = RESOLUTION_BUTTON;
		}
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
	{
		switch (menu_option)
		{
		case OPTION_NO_CHOICE:
			menu_option = FULL_SCREEN_TOGGLE;
		case FULL_SCREEN_TOGGLE:
			menu_option = VOLUME;
		case VOLUME:
			menu_option = RESOLUTION_BUTTON;
		case RESOLUTION_BUTTON:
			menu_option = FULL_SCREEN_TOGGLE;
		}
	}
	else if (key == sf::Keyboard::Return)
	{
		switch (menu_option)
		{
		case OPTION_NO_CHOICE:
		case FULL_SCREEN_TOGGLE:
		case VOLUME:
		case RESOLUTION_BUTTON:
		}
	}
	else if (key == sf::Keyboard::Escape)
	{

	}
	else if (key == sf::Keyboard::Space)
	{

	}

	return OPTIONS_MENU;
}

void OptionsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;

#pragma endregion

#pragma region PauseMenu
	
PauseMenu::PauseMenu();
	
location PauseMenu::mousePressed(sf::Vector2i mouse_pos, location loc)
{
	if (resumegame_.contains(mouse_pos))
		return GAME;
	if (options_.contains(mouse_pos))
		return OPTIONS_MENU;
	if (exitToMenu_.contains(mouse_pos))
		return NO_LOCATION;
}
location PauseMenu::mouseMoved(sf::Vector2i mouse_pos, location loc)
{
	menu_option = PAUSE_NO_CHOICE;
	if (!resumegame_.contains(mouse_pos))
		resumegame_.removeHighlight();
	if (!options_.contains(mouse_pos))
		options_.removeHighlight();
	if (!exitToMenu_.contains(mouse_pos))
		exitToMenu_.removeHighlight();

	if (resumegame_.contains(mouse_pos))
		resumegame_.highlight(COLOR_MOUSE_OVER);
	if (options_.contains(mouse_pos))
		options_.highlight(COLOR_MOUSE_OVER);
	if (exitToMenu_.contains(mouse_pos))
		exitToMenu_.highlight(COLOR_MOUSE_OVER);

	return loc;
}
location PauseMenu::keyPressed(sf::Keyboard::Key key, location loc)//TODO: fix this to format
{
	fullScreenToggle_.removeHighlight();
	volume_.removeHighlight();
	resolution_up_.removeHighlight();
	resolution_down_.removeHighlight();
	accept_.removeHighlight();
	cancel_.removeHighlight();
	apply_.removeHighlight();

	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
	{
		switch (menu_option)
		{
		case FULL_SCREEN_TOGGLE:
			menu_option = VOLUME;
		case VOLUME:
		case RESOLUTION_BUTTON:
		case OPTION_NO_CHOICE:
		}
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
	{
		switch (menu_option)
		{
		case OPTION_NO_CHOICE:
		case FULL_SCREEN_TOGGLE:
		case VOLUME:
		case RESOLUTION_BUTTON:
		}
	}
	else if (key == sf::Keyboard::Return)
	{
		switch (menu_option)
		{
		case OPTION_NO_CHOICE:
		case FULL_SCREEN_TOGGLE:
		case VOLUME:
		case RESOLUTION_BUTTON:
		}
	}
	else if (key == sf::Keyboard::Escape)
	{

	}
	else if (key == sf::Keyboard::Space)
	{

	}

	return OPTIONS_MENU;
}
void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;

#pragma endregion


//50*400