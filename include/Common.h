#ifndef COMMON_H
#define COMMON_H

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <sstream>


#pragma region enums

enum interactType
{
	NO_OBJECT =-1,
	STORY_OBJECT,
	CLOSED_DOOR,
	OPEN_DOOR,
	LEVER,
	COUNT
};

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
	WEST
};
enum leverState 
{
	NO_LEVER =-1, 
	NEGATIVE, 
	NEUTRAL, 
	POSITIVE
};
enum plugState 
{
	NO_PLUG =-1, 
	PLAYER_TO_CIRCUIT, 
	CIRCUIT_TO_CIRCUIT
};
enum propType 
{
	NO_OBJECT =-1, 

	BED, 
	WARDROBE,
	WINDOW,

	CHILD_MALE,
	CHILD_FEMALE,
	JANITOR,
	COUNT
}; 
enum doorType
{
	NO_DOOR =-1,
	WOODEN,
	MAHOGANY,
	BATHROOM,
	METAL,
	VAULT,
	COUNT
};
enum wallType
{
	NO_WALL = -1,
	STRIPED,
	WOODEN,
	UTILITY_CLOSET,
	MAINTENCE_TUNNEL,
	COUNT
};
enum floorType
{
	NO_FLOOR,
	TILE,
	WOODEN,
	COUNT
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

#define NEXT_ACT 999

#define ID_SETTINGS "#settings"
#define ID_PROPS "#props"
#define ID_PUZZLE "#puzzle"
#define ID_STORY "#story"
#define ID_CHARACTER "#character"

#define LINE_THICKNESS 5

#pragma endregion

#pragma region functions

bool progressFileExists();

#pragma region rectangles
sf::Font fontFromFile(std::string fileName);

sf::Vector2i getCenter(sf::IntRect rect);
sf::Vector2f getCenter(sf::FloatRect rect);

sf::IntRect rectMake_Center(sf::Vector2i center, sf::Vector2i size);
sf::IntRect rectMake_Corners(sf::Vector2i TLCorner, sf::Vector2i BRCorner);
sf::IntRect rectMake_Corners(int top, int left, int bottom, int right);
sf::IntRect rectMake_Containing(sf::IntRect one, sf::IntRect two);

sf::IntRect rectMove(sf::IntRect rect, direction d, int distance);

int rect_Bottom(sf::IntRect rect);
int rect_Right(sf::IntRect rect);
#pragma endregion


#pragma region translate
direction keyToDirection(sf::Keyboard::Key key);
direction stringToDirection(std::string translate);
leverState stringToLeverState(std::string translate);
plugState stringToPlugState(std::string translate);
propType stringToPropType(std::string translate); 
doorType stringToDoorType(std::string translate);
wallType stringToWallType(std::string translate);
floorType stringToFloorType(std::string translate);


std::string directionToString(direction translate);
std::string leverStateToString(leverState translate);
std::string plugStateToString(plugState translate);
std::string propTypeToString(propType translate); 
std::string doorTypeToString(doorType translate);
std::string wallTypeToString(wallType translate);
std::string floorTypeToString(floorType translate);
#pragma endregion

#pragma endregion

#pragma region structs

struct IFeelLonely{
bool alone = true;
};

#pragma endregion



#endif