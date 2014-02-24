#ifndef MENUS_H
#define MENUS_H

class MainMenu;
class OptionsMenu;
class PauseMenu;

#include "Common.h"
#include "ClassUtilities.h"
#include "UIUtilities.h"
#include "GodMode.h"

class MainMenu: public Inputable, public sf::Drawable
{
private:
	mainMenuOptions menu_option;

	Button newGame_;
	Button continue_;
	Button options_;
	Button close_;
	AllFonts fonts_;

	bool canContinue_;

public:	
	friend GodMode;
	MainMenu(bool t_canContinue_);

	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual location keyPressed(sf::Keyboard::Key key, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class OptionsMenu: public Inputable, public sf::Drawable
{
private:
	optionMenuOptions menu_option;

	Button fullScreenToggle_;
	Button volume_;
	Button accept_;
	Button cancel_;
	Textbox resolution;
	Button resolution_up_;
	Button resolution_down_;
	Button apply_;

	bool changed;

	SettingsInfo *setting_p;
	//TODO: need to define t_setting
	sf::RenderWindow *window_p;
	sf::ContextSettings *c_settings_p;

	
	AllFonts fonts_;
public:
	OptionsMenu(SettingsInfo *t_setting_p, sf::RenderWindow *t_window_p, sf::ContextSettings *t_c_settings_p);
	~OptionsMenu();
	
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);	//loc is the menu that entered options menu
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual location keyPressed(sf::Keyboard::Key key, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class PauseMenu: public Inputable, public sf::Drawable
{
private:
	pauseMenuOptions menu_option;

	Button resumegame_;
	Button options_;
	Button exitToMenu_;

	AllFonts fonts_;


public:
	PauseMenu();
	
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual location keyPressed(sf::Keyboard::Key key, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif