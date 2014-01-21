#include "..\include\Menus.h"

MainMenu::MainMenu();

location MainMenu::mousePressed(sf::Vector2i mouse_pos, location loc)
{
	if (newGame_.contains(mouse_pos))
	{
		//TODO: Clear Save
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
	if (canContinue_)
		continue_.highLight(COLOR_GRAY);

	if (newGame_.contains(mouse_pos))
		newGame_.highLight(COLOR_MOUSE_OVER);
	if (continue_.contains(mouse_pos))
		continue_.highLight(COLOR_MOUSE_OVER);
	if (options_.contains(mouse_pos))
		options_.highLight(COLOR_MOUSE_OVER);
	if (close_.contains(mouse_pos))
		close_.highLight(COLOR_MOUSE_OVER);

	return loc;
}
void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(newGame_, states);
	target.draw(continue_, states);
	target.draw(options_, states);
	target.draw(close_, states);
}


	
OptionsMenu::OptionsMenu();
	
location OptionsMenu::mousePressed(sf::Vector2i mouse_pos, location loc)
{
}	//loc is the menu that entered options menu
location OptionsMenu::mouseMoved(sf::Vector2i mouse_pos, location loc);
void OptionsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;


	
PauseMenu::PauseMenu();
	
location PauseMenu::mousePressed(sf::Vector2i mouse_pos, location loc);
location PauseMenu::mouseMoved(sf::Vector2i mouse_pos, location loc);
void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;