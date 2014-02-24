#include "..\include\Common.h"


bool progressFileExists()
{
	std::ifstream progress_file(FILE_PROGRESS);
	std::string buffer = "";

	std::getline(progress_file, buffer);

	return (buffer != "");
}

#pragma region rectangles

sf::Font fontFromFile(std::string fileName)
{
	sf::Font font;
	font.loadFromFile(fileName);
	return font;
}

sf::Vector2i getCenter(sf::IntRect rect)
{
	sf::Vector2i point(rect.left, rect.top);
	point.x += (rect.width /2);
	point.y += (rect.height /2);
	return point;
}
sf::Vector2f getCenter(sf::FloatRect rect)
{
	sf::Vector2f point(rect.left, rect.top);
	point.x += (rect.width /2);
	point.y += (rect.height /2);
	return point;
}

sf::IntRect rectMake_Center(sf::Vector2i center, sf::Vector2i size)
{
	sf::Vector2i position = (center - size/2);
	
	return sf::IntRect(position, size);
}
sf::IntRect rectMake_Corners(sf::Vector2i TLCorner, sf::Vector2i BRCorner)
{
	sf::Vector2i size = BRCorner - TLCorner;
	return sf::IntRect(TLCorner, size);
}
sf::IntRect rectMake_Corners(int top, int left, int bottom, int right)
{
	return rectMake_Corners(sf::Vector2i(top, left), sf::Vector2i(bottom, right));
}
sf::IntRect rectMake_Containing(sf::IntRect one, sf::IntRect two)
{
	int top =  one.top  < two.top   ?  one.top  : two.top,
		left = one.left < two.left  ?  one.left : two.left,
		bottom = rect_Bottom(one) > rect_Bottom(two)  ?  rect_Bottom(one) : rect_Bottom(two),
		right =  rect_Right(one)  > rect_Right(two)   ?  rect_Right(one)  : rect_Right(two);

	return rectMake_Corners(top, left, bottom, right);
}

sf::IntRect rectMove(sf::IntRect rect, direction d, int distance)
{
	switch (d)
	{
	case NO_DIRECTION:
		break;
	case NORTH:
		rect.top	-= distance;
		break;
	case EAST:
		rect.left	+= distance;
		break;
	case SOUTH:
		rect.top	+= distance;
		break;
	case WEST:
		rect.left	-= distance;
		break;
	}
	return rect;
}

int rect_Bottom(sf::IntRect rect)
{
	return (rect.top + rect.height);
}
int rect_Right(sf::IntRect rect)
{
	return (rect.left + rect.width);
}
#pragma endregion

//#pragma region translate

direction keyToDirection(sf::Keyboard::Key key)
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
        dir = NO_DIRECTION;
        break;
    }
    return dir;
}
///////////////////////////////////////////////////////////////////////;;;;;;;;;;;;;;
direction stringToDirection(std::string translate)
{
	if (translate == "NORTH")
		return NORTH;
	if (translate == "EAST")
		return EAST;
	if (translate == "SOUTH")
		return SOUTH;
	if (translate == "WEST")
		return WEST;

	return NO_DIRECTION;
}
leverState stringToLeverState(std::string translate)
{
	if (translate == "NEGATIVE")
		return NEGATIVE;
	if (translate == "NEUTRAL")
		return NEUTRAL;
	if (translate == "POSITIVE")
		return POSITIVE;

	return NO_LEVER;
}
plugState stringToPlugState(std::string translate)
{
	if (translate == "PLAYER_TO_CIRCUIT")
		return PLAYER_TO_CIRCUIT;
	if (translate == "CIRCUIT_TO_CIRCUIT")
		return CIRCUIT_TO_CIRCUIT;

	return NO_PLUG;
}
propType stringToPropType(std::string translate) 
{
	if (translate == "BED")
		return BED;
	if (translate == "WARDROBE")
		return WARDROBE;
	if (translate == "WINDOW")
		return WINDOW;
	if (translate == "CHILD_MALE")
		return CHILD_MALE;
	if (translate == "CHILD_FEMALE")
		return CHILD_FEMALE;
	if (translate == "JANITOR")
		return JANITOR;

	return NO_PROP;
}
doorType stringToDoorType(std::string translate) 
{
	if (translate == "WOOD")
		return WOOD;
	if (translate == "MAHOGANY")
		return MAHOGANY;
	if (translate == "BATHROOM")
		return BATHROOM;
	if (translate == "METAL")
		return METAL;
	if (translate == "VAULT")
		return VAULT;

	return NO_DOOR;
}
wallType stringToWallType(std::string translate) 
{
	if (translate == "STRIPED")
		return STRIPED;
	if (translate == "WOODEN_WALL")
		return WOODEN_WALL;
	if (translate == "UTILITY_CLOSET")
		return UTILITY_CLOSET;
	if (translate == "MAINTENCE_TUNNEL")
		return MAINTENCE_TUNNEL;

	return NO_WALL;
}
floorType stringToFloorType(std::string translate) 
{
	if (translate == "WOODEN_FLOOR")
		return WOODEN_FLOOR;
	if (translate == "TILE")
		return TILE;

	return NO_FLOOR;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string to_string(direction translate)
{
    if (translate == NORTH)
		return "NORTH";
	if (translate == EAST)
		return "EAST";
	if (translate == SOUTH)
		return "SOUTH";
	if (translate == WEST)
		return "WEST";

	return "NO_DIRECTION";
}
std::string to_string(leverState translate)
{
	if (translate == NEGATIVE)
		return "NEGATIVE";
	if (translate == NEUTRAL)
		return "NEUTRAL";
	if (translate == POSITIVE)
		return "POSITIVE";

	return "NO_LEVER";
}
std::string to_string(plugState translate)
{
	if (translate == PLAYER_TO_CIRCUIT)
		return "PLAYER_TO_CIRCUIT";
	if (translate == CIRCUIT_TO_CIRCUIT)
		return "CIRCUIT_TO_CIRCUIT";

	return "NO_PLUG";
}
std::string to_string(propType translate)
{
	if (translate == BED)
		return "BED";
	if (translate == WARDROBE)
		return "WARDROBE";
	if (translate == WINDOW)
		return "WINDOW";
	if (translate == CHILD_MALE)
		return "CHILD_MALE";
	if (translate == CHILD_FEMALE)
		return "CHILD_FEMALE";
	if (translate == JANITOR)
		return "JANITOR";

	return "NO_OBJECT";
}
std::string to_string(doorType translate)
{
	if (translate == WOOD)
		return "WOOD";
	if (translate == MAHOGANY)
		return "MAHOGANY";
	if (translate == BATHROOM)
		return "BATHROOM";
	if (translate == METAL)
		return "METAL";
	if (translate == VAULT)
		return "VAULT";

	return "NO_DOOR";
}
std::string to_string(wallType translate)
{
	if (translate == STRIPED)
		return "STRIPED";
	if (translate == WOODEN_WALL)
		return "WOODEN_WALL";
	if (translate == UTILITY_CLOSET)
		return "UTILITY_CLOSET";
	if (translate == MAINTENCE_TUNNEL)
		return "MAINTENCE_TUNNEL";

	return "NO_WALL";
}
std::string to_string(floorType translate) 
{
	if (translate == WOODEN_FLOOR)
		return "WOODEN_FLOOR";
	if (translate == TILE)
		return "TILE";

	return "NO_FLOOR";
}
std::string to_string(sf::VideoMode translate)
{
	return std::to_string(translate.width) + "x" + std::to_string(translate.height);
}
//#pragma endregion
