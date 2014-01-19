#ifndef COMMON_H
#define COMMON_H

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>

#pragma region enums

enum location {GAME, MAIN_MENU, PAUSE_MENU, OPTIONS_MENU};
enum direction {NONE = -1, NORTH, EAST, SOUTH, WEST};
enum leverState {NO_LEVER, NEGATIVE, NEUTRAL, POSITIVE};
enum plugState {NO_PLUG, PLAYER_TO_CIRCUIT, CIRCUIT_TO_CIRCUIT};

#pragma endregion

#pragma region defines

#define UNCOLIDABLE_BOX sf::IntRect()
#define CHAR_COL_BOX sf::IntRect(100,100,100,100)

#pragma endregion

#pragma region functions

direction convertKeyToDirection(sf::Keyboard::Key key)
{
    direction dir;
    switch(key)
    {
	case sf::Keyboard::Up:
    case sf::Keyboard::W:
        dir = NORTH;
        break;
    case sf::Keyboard::Right:
    case sf::Keyboard::D:
        dir = EAST;
        break;
    case sf::Keyboard::Down:
    case sf::Keyboard::S:
        dir = SOUTH;
        break;
    case sf::Keyboard::Left:
    case sf::Keyboard::A:
        dir = WEST;
        break;
    default:
        dir = NONE;
        break;
    }
    return dir;
}
sf::Font fontFromFile(std::ifstream &file);

sf::Vector2i getCenter(sf::IntRect rect);
sf::Vector2f getCenter(sf::FloatRect rect);

sf::IntRect makeRect_Center(sf::Vector2i center, sf::Vector2i size);
sf::IntRect makeRect_Corners(sf::Vector2i TLCorner, sf::Vector2i BRCorner);
sf::IntRect makeRect_Corners(int top, int left, int bottom, int right);
sf::IntRect makeRect_Containing(sf::IntRect one, sf::IntRect two);

int rect_Bottom(sf::IntRect rect);
int rect_Right(sf::IntRect rect);

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
struct AllTextures
{
	std::vector<sf::Texture> textures_;

	void loadAll();
	std::vector<sf::Texture*> forGame() const;
	sf::Texture* basicProps() const;
	//TODO: list all textures needed
}
struct AllFonts
{
	std::vector<sf::Font> fonts_;

	void loadAll();
	sf::Font* arial() const;
	//TODO: list all fonts needed
}
#pragma endregion



#endif