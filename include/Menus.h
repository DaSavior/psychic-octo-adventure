#ifndef MENUS_H
#define MENUS_H

#include "Common.h"
#include "ClassUtilities.h"
#include "UIUtilities.h"
#include "GodMode.h"

class MainMenu: public Inputable, public sf::Drawable
{
private:
	
	Button newGame_;
	Button continue_;
	Button options_;
	Button close_;

	bool canContinue_;

public:	
	friend GodMode;
	MainMenu();

	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);
	/*
		if (.contain new game
			clear save
			loc = GAME
		else if (stuff migiger
		return loc
	*/
	//	new game putton also clears save file

	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class OptionsMenu: public Inputable, public sf::Drawable
{
private:
	Button fullScreenToggle_;
	Button volume_;
	Button accept_;
	Button cancel_;
	//resolution up/down buttons?
	//TODO: how does optionsMenu know the settings and change them? should it use a pointer to the settings?

	SettingsInfo *setting_p;
public:
	OptionsMenu(SettingsInfo *t_setting_p);
	~OptionsMenu();
	
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);	//loc is the menu that entered options menu
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class PauseMenu: public Inputable, public sf::Drawable
{
private:
	Button resumegame_;
	Button options_;
	Button exitGame_;


public:
	PauseMenu();
	
	virtual location mousePressed(sf::Vector2i mouse_pos, location loc);
	virtual location mouseMoved(sf::Vector2i mouse_pos, location loc);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif