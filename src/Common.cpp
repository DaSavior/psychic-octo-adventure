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
        dir = NONE;
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

sf::IntRect makeRect_Center(sf::Vector2i center, sf::Vector2i size)
{
	sf::Vector2i position = (center - size/2);
	
	return sf::IntRect(position, size);
}
sf::IntRect makeRect_Corners(sf::Vector2i TLCorner, sf::Vector2i BRCorner)
{
	sf::Vector2i size = BRCorner - TLCorner;
	return sf::IntRect(TLCorner, size);
}
sf::IntRect makeRect_Corners(int top, int left, int bottom, int right)
{
	return makeRect_Corners(sf::Vector2i(top, left), sf::Vector2i(bottom, right));
}
sf::IntRect makeRect_Containing(sf::IntRect one, sf::IntRect two)
{
	int top =  one.top  < two.top   ?  one.top  : two.top,
		left = one.left < two.left  ?  one.left : two.left,
		bottom = rect_Bottom(one) > rect_Bottom(two)  ?  rect_Bottom(one) : rect_Bottom(two),
		right =  rect_Right(one)  > rect_Right(two)   ?  rect_Right(one)  : rect_Right(two);

	return makeRect_Corners(top, left, bottom, right);
}

int rect_Bottom(sf::IntRect rect)
{
	return (rect.top + rect.height);
}
int rect_Right(sf::IntRect rect)
{
	return (rect.left + rect.width);
}