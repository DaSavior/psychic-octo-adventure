#include "..\include\Common.h"


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
        dir = NO_DIRECTION;
        break;
    }
    return dir;
}
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

bool progressFileExists()
{
	bool exists = true;

	std::ifstream progress_file(FILE_PROGRESS);
	std::string buffer = "";

	std::getline(progress_file, buffer);

	if (buffer == "")
	{
		exists = false;
	}

	return exists;
}

