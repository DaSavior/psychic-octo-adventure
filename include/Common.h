#ifndef COMMON_H
#define COMMON_H

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>

#pragma region enums

enum mainMenuOptions
{
	MAIN_NO_CHOICE = 0,
	NEW_GAME,
	CONTINUE,
	MAIN_OPTIONS,
	CLOSE
};
enum optionMenuOptions
{
	OPTION_NO_CHOICE = 0,
	FULL_SCREEN_TOGGLE,
	VOLUME,
	RESOLUTION_BUTTON
};
enum pauseMenuOptions
{
	PAUSE_NO_CHOICE = 0,
	RESUME_GAME,
	PAUSE_OPTIONS,
	EXIT_TO_MENU
};



enum location 
{
	NO_LOCATION =-1, 
	GAME, 
	MAIN_MENU, 
	PAUSE_MENU, 
	OPTIONS_MENU,
	EXIT_GAME
};
enum direction {
	NO_DIRECTION = -1, 
	NORTH, 
	EAST, 
	SOUTH,
	WEST};
enum leverState {
	NO_LEVER =-1, 
	NEGATIVE, 
	NEUTRAL, 
	POSITIVE};
enum plugState {
	NO_PLUG =-1, 
	PLAYER_TO_CIRCUIT, 
	CIRCUIT_TO_CIRCUIT};
enum propType {
	NO_OBJECT =-1, 
	BED, 
	WARDROBE,
	WINDOW,

	CHILD_MALE,
	CHILD_FEMALE,
	JANITOR,
}; 
enum doorType
{
	NO_DOOR =-1,
	WOODEN,
	MAHOGANY,
	BATHROOM,
	METAL,
	VAULT
};

#pragma endregion

#pragma region defines

#define UNCOLIDABLE_BOX sf::IntRect()
#define CHAR_COL_BOX sf::IntRect(100,100,100,100)
#define COLOR_MOUSE_OVER sf::Color::Color(200,150,50,100)
#define COLOR_GRAY sf::Color::Color(150,150,150,150)

#define ARM_UP 20
#define ARM_DOWN 30

#define FILE_PROGRESS "Resources/save.txt"	//TODO: change to .dat once everything works

#define ID_SETTINGS "#settings"
#define ID_PROPS "#props"
#define ID_PUZZLE "#puzzle"
#define ID_STORY "#story"
#define ID_CHARACTER "#character"

#pragma endregion

#pragma region functions

direction convertKeyToDirection(sf::Keyboard::Key key);
sf::Font fontFromFile(std::string fileName);

sf::Vector2i getCenter(sf::IntRect rect);
sf::Vector2f getCenter(sf::FloatRect rect);

sf::IntRect makeRect_Center(sf::Vector2i center, sf::Vector2i size);
sf::IntRect makeRect_Corners(sf::Vector2i TLCorner, sf::Vector2i BRCorner);
sf::IntRect makeRect_Corners(int top, int left, int bottom, int right);
sf::IntRect makeRect_Containing(sf::IntRect one, sf::IntRect two);

int rect_Bottom(sf::IntRect rect);
int rect_Right(sf::IntRect rect);

bool progressFileExists();

#pragma endregion

#pragma region structs

struct SettingsInfo
{
	SettingsInfo(sf::VideoMode win_res = sf::VideoMode(800, 600), unsigned short vol = 50, 
				 sf::Uint32 t_style = sf::Style::Fullscreen, std::string window_title = "Psychosis");
	void loadFromFile(std::string file_name);

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
};
struct AllFonts
{
	std::vector<sf::Font> fonts_;

	void loadAll();
	sf::Font* arial() const;
	//TODO: list all fonts needed
};
#pragma endregion



#endif