#include "..\include\Menus.h"

#pragma region MainMenu

MainMenu::MainMenu(bool t_canContinue_)
{
	canContinue_ = t_canContinue_;

	menu_option = MAIN_NO_CHOICE;

	newGame_.setFont(*fonts_.arial());
	continue_.setFont(*fonts_.arial());
	options_.setFont(*fonts_.arial());
	close_.setFont(*fonts_.arial());

	newGame_.setString("New Game");
	continue_.setString("Continue");
	options_.setString("Options");
	close_.setString("Exit");

	sf::Vector2f start(100,100), distance(0,100);
	newGame_.setPosition(start);
	continue_.setPosition(start+distance);
	options_.setPosition(start+(2.0f*distance));
	close_.setPosition(start+(3.0f*distance));
}

location MainMenu::mousePressed(sf::Vector2i mouse_pos, location loc)
{
	if (newGame_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
	{
		std::ofstream file;
		file.open(FILE_PROGRESS);
		file.close();
		
		return GAME;
	}
	if (continue_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		return GAME;
	if (options_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		return OPTIONS_MENU;
	if (close_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		return EXIT_GAME;
}
location MainMenu::mouseMoved(sf::Vector2i mouse_pos, location loc)
{
	menu_option = MAIN_NO_CHOICE;
	if (!newGame_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		newGame_.removeHighlight();
	if (!continue_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y) && canContinue_)
		continue_.removeHighlight();
	if (!options_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		options_.removeHighlight();
	if (!close_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		close_.removeHighlight();

	if (!canContinue_)
		continue_.highlight(COLOR_GRAY);

	if (newGame_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		newGame_.highlight(COLOR_MOUSE_OVER);
	if (continue_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y) && canContinue_)
		continue_.highlight(COLOR_MOUSE_OVER);
	if (options_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		options_.highlight(COLOR_MOUSE_OVER);
	if (close_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
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

OptionsMenu::OptionsMenu(SettingsInfo *t_setting_p, sf::RenderWindow *t_window_p, sf::ContextSettings *t_c_settings_p) 
{
	changed = false;
	setting_p = t_setting_p;
	window_p = t_window_p;
	c_settings_p = t_c_settings_p;

	menu_option = OPTION_NO_CHOICE; 

	resolution.setBox(sf::IntRect(100,100,100,100));

	fullScreenToggle_.setFont(*fonts_.arial());
	volume_.setFont(*fonts_.arial());
	resolution_up_.setFont(*fonts_.arial());
	resolution_down_.setFont(*fonts_.arial());
	accept_.setFont(*fonts_.arial());
	cancel_.setFont(*fonts_.arial());
	apply_.setFont(*fonts_.arial());

	//////////////////////

	fullScreenToggle_.setString("Toggle Fullscreen");

	volume_.setString("Volume");

	resolution.setString(to_string(setting_p->resolution));
	resolution_up_.setString(char(175));
	resolution_down_.setString(char(174));

	accept_.setString("Continue");
	cancel_.setString("Options");
	apply_.setString("Exit");

	////////////////////

	sf::Vector2f start(100,100), distance(0,100);

	fullScreenToggle_.setPosition(start);

	volume_.setPosition(start+distance);

	resolution_down_.setPosition(start+(2.0f*distance));
	resolution.setPosition(start.x + resolution_down_.getGlobalBounds().width + 20, start.y+resolution_down_.getPosition().y);
	resolution_up_.setPosition(start.x + resolution.getGlobalBounds().width + 20, start.y+resolution_down_.getPosition().y);

	accept_.setPosition(start+(3.0f*distance));
	apply_.setPosition(start.x + accept_.getGlobalBounds().width + 20, start.y+accept_.getPosition().y);
	cancel_.setPosition(start.x + apply_.getGlobalBounds().width + 20, start.y+apply_.getPosition().y);
	

}
OptionsMenu::~OptionsMenu()
{
	if (setting_p == NULL)
	{
		delete setting_p;
		setting_p = NULL;
	}
	if (window_p == NULL)
	{
		delete window_p;
		window_p = NULL;
	}
	if (c_settings_p == NULL)
	{
		delete c_setting_p;
		c_setting_p = NULL;
	}
}

location OptionsMenu::mousePressed(sf::Vector2i mouse_pos, location loc)
{
	if (fullScreenToggle_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
	{
		if (t_setting.style == sf::Style::Fullscreen)
			t_setting.style = sf::Style::Close;
		else
			t_setting.style = sf::Style::Fullscreen;
	}
	if (volume_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
	{
		setting_p->volume = ((setting_p->volume+25) % 125);
	}
	if (resolution_up_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
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
		resolution.setString(to_string(t_setting.resolution));
	}
	if (resolution_down_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
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
		resolution.setString(to_string(t_setting.resolution));
	}
	if (accept_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
	{
		*setting_p = t_setting;
		if (!changed)
		{
			window_p->create(setting_p->resolution, setting_p->window_name, setting_p->style, *c_settings_p);
		}
		changed = false;
		return loc;
	}
	if (cancel_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
	{
		if (changed)
		{
			window_p->create(setting_p->resolution, setting_p->window_name, setting_p->style, *c_settings_p);
		}
		changed = false;
		return loc;
	}
	if (apply_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
	{
		changed = true;
		window_p->create(t_setting.resolution, t_setting.window_name, t_setting.style, *c_settings_p);
	}

	return OPTIONS_MENU;
}
location OptionsMenu::mouseMoved(sf::Vector2i mouse_pos, location loc)
{
	menu_option = OPTION_NO_CHOICE;
	if (!fullScreenToggle_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		fullScreenToggle_.removeHighlight();
	if (!volume_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		volume_.removeHighlight();
	if (!resolution_up_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		resolution_up_.removeHighlight();
	if (!resolution_down_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		resolution_down_.removeHighlight();
	if (!accept_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		accept_.removeHighlight();
	if (!cancel_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		cancel_.removeHighlight();
	if (!apply_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		apply_.removeHighlight();

	if (fullScreenToggle_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		fullScreenToggle_.highlight(COLOR_MOUSE_OVER);
	if (volume_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		volume_.highlight(COLOR_MOUSE_OVER);
	if (resolution_up_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		resolution_up_.highlight(COLOR_MOUSE_OVER);
	if (resolution_down_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		resolution_down_.highlight(COLOR_MOUSE_OVER);
	if (accept_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		accept_.highlight(COLOR_MOUSE_OVER);
	if (cancel_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		cancel_.highlight(COLOR_MOUSE_OVER);
	if (apply_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
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
			break;
		case VOLUME:
			menu_option = FULL_SCREEN_TOGGLE;
			break;
		case RESOLUTION_BUTTON:
			menu_option = VOLUME;
			break;
		case OPTION_NO_CHOICE:
			menu_option = RESOLUTION_BUTTON;
			break;
		}
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
	{
		switch (menu_option)
		{
		case OPTION_NO_CHOICE:
			menu_option = FULL_SCREEN_TOGGLE;
			break;
		case FULL_SCREEN_TOGGLE:
			menu_option = VOLUME;
			break;
		case VOLUME:
			menu_option = RESOLUTION_BUTTON;
			break;
		case RESOLUTION_BUTTON:
			menu_option = FULL_SCREEN_TOGGLE;
			break;
		}
	}
	else if (key == sf::Keyboard::Return) //TODO: fix
	{
		switch (menu_option)
		{
		case OPTION_NO_CHOICE:
		case FULL_SCREEN_TOGGLE:
		case VOLUME:
		case RESOLUTION_BUTTON:
		}
	}
	else if (key == sf::Keyboard::Escape) //TODO: fix
	{

	}
	else if (key == sf::Keyboard::Space) //TODO: fix
	{

	}

	return OPTIONS_MENU;
}

void OptionsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;

#pragma endregion

#pragma region PauseMenu
	
PauseMenu::PauseMenu()
{
	resumegame_.setFont(*fonts_.arial());
	options_.setFont(*fonts_.arial());
	exitToMenu_.setFont(*fonts_.arial());

	resumegame_.setString("Resume");
	options_.setString("Options");
	exitToMenu_.setString("Main Menu");

	sf::Vector2f start(100,100), distance(0,100);
	resumegame_.setPosition(start);
	options_.setPosition(start+distance);
	exitToMenu_.setPosition(start+(2.0f*distance));
}
	
location PauseMenu::mousePressed(sf::Vector2i mouse_pos, location loc)
{
	if (resumegame_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		return GAME;
	if (options_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		return OPTIONS_MENU;
	if (exitToMenu_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		return NO_LOCATION;
}
location PauseMenu::mouseMoved(sf::Vector2i mouse_pos, location loc)
{
	menu_option = PAUSE_NO_CHOICE;
	if (!resumegame_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		resumegame_.removeHighlight();
	if (!options_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		options_.removeHighlight();
	if (!exitToMenu_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		exitToMenu_.removeHighlight();

	if (resumegame_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		resumegame_.highlight(COLOR_MOUSE_OVER);
	if (options_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		options_.highlight(COLOR_MOUSE_OVER);
	if (exitToMenu_.getGlobalBounds().contains(mouse_pos.x , mouse_pos.y))
		exitToMenu_.highlight(COLOR_MOUSE_OVER);

	return loc;
}
location PauseMenu::keyPressed(sf::Keyboard::Key key, location loc)//TODO: fix this to format
{
	resumegame_.removeHighlight();
	options_.removeHighlight();
	exitToMenu_.removeHighlight();

	if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
	{
		switch (menu_option)
		{
		case RESUME_GAME:
			menu_option = EXIT_TO_MENU;
			break;
		case PAUSE_OPTIONS:
			menu_option = RESUME_GAME;
			break;
		case EXIT_TO_MENU:
			menu_option = PAUSE_OPTIONS;
			break;
		case PAUSE_NO_CHOICE:
			menu_option = EXIT_TO_MENU;
			break;
		}
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
	{
		switch (menu_option)
		{
		case PAUSE_NO_CHOICE:
			menu_option = RESUME_GAME;
			break;
		case RESUME_GAME:
			menu_option = PAUSE_OPTIONS;
			break;
		case PAUSE_OPTIONS:
			menu_option = EXIT_TO_MENU;
			break;
		case EXIT_TO_MENU:
			menu_option = RESUME_GAME;
			break;
		}
	}
	else if (key == sf::Keyboard::Return)
	{
		switch (menu_option)
		{
		case OPTION_NO_CHOICE:
			return PAUSE_MENU;
			break;
		case RESUME_GAME:
			return GAME;
			break;
		case PAUSE_OPTIONS:
			return OPTIONS_MENU;
			break;
		case EXIT_TO_MENU:
			return MAIN_MENU;
			break;
		}
	}
	else if (key == sf::Keyboard::Escape)
	{

	}
	else if (key == sf::Keyboard::Space)
	{

	}

	return PAUSE_MENU;
}
void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;

#pragma endregion


//50*400