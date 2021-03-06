#include "..\include\ClassUtilities.h"

location Inputable::input(sf::Event event, location loc)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		loc = keyPressed(event.key.code, loc);
		break;
	case sf::Event::KeyReleased:
		loc = keyReleased(event.key.code, loc);
		break;
	case sf::Event::MouseButtonPressed:
		loc = mousePressed(sf::Mouse::getPosition(), loc);
		break;
	case sf::Event::MouseMoved:
		loc = mouseMoved(sf::Mouse::getPosition(), loc);
		break;
	}
	return loc;
}

#pragma region SpritePlus

SpritePlus::SpritePlus(const sf::IntRect &collision = sf::IntRect()) : sf::Sprite() 
{
	collisionRectangle_ = collision;
};
SpritePlus::SpritePlus(const sf::Sprite &sprite, const sf::IntRect &collision = sf::IntRect()) : sf::Sprite (sprite)
{
	collisionRectangle_ = collision;
}
SpritePlus::SpritePlus(const sf::Texture &texture, const sf::IntRect &collision = sf::IntRect()) : sf::Sprite(texture)
{
	collisionRectangle_ = collision;
}
SpritePlus::SpritePlus(const sf::Texture &texture, const sf::IntRect &rectangle, const sf::IntRect &collision = sf::IntRect()) : sf::Sprite(texture, rectangle)
{
	collisionRectangle_ = collision;
}
	
sf::IntRect SpritePlus::getCollisionRectangle() const
{
	return collisionRectangle_;
}
sf::IntRect SpritePlus::getGlobalCollisionRectangle() const
{
	sf::IntRect r = collisionRectangle_;
	r.left += getPosition().x;
	r.top += getPosition().y;

	return r;
}
sf::Vector2f SpritePlus::getFrame() const
{
	sf::IntRect r = getTextureRect();

	sf::Vector2f v(r.left, r.top);

	if (r.height > 0)
		v.x /= r.height;
	else
		v.x = 0;

	if (r.width > 0)
		v.y /= r.width;
	else
		v.y = 0;

	return v;
}
sf::Vector2f SpritePlus::getFrameFit() const
{
	float x = getTexture()->getSize().x / getTextureRect().width,
		y = getTexture()->getSize().y / getTextureRect().height;

	return sf::Vector2f(x, y);
}

void SpritePlus::setCollisionRectangle(sf::IntRect collisionRectangle)
{
	collisionRectangle_ = collisionRectangle;
}
void SpritePlus::setFrame(float x, float y)
{
	float width = (float)getTextureRect().width;
	float height = (float)getTextureRect().height;
	x *= width;
	y *= height;
	setTextureRect(sf::IntRect((int)x, (int)y, (int)width, (int)height));
	return;
}
void SpritePlus::setFrame(sf::Vector2f framePosition)
{
	setFrame(framePosition.x, framePosition.y);
}

bool SpritePlus::collides(sf::IntRect globalRect) const
{
	return getGlobalCollisionRectangle().intersects(globalRect);
}
bool SpritePlus::collides(sf::Vector2i globalPoint) const
{
	return getGlobalCollisionRectangle().contains(globalPoint);
}
bool SpritePlus::frameAt(direction position) const
{
	switch (position)
	{
	case NORTH:
		return (getFrame().y == 0);
	case EAST:
		return (getFrame().x == getFrameFit().x);
	case SOUTH:
		return (getFrame().y == getFrameFit().y);
	case WEST:
		return (getFrame().x == 0);
	}
	return false;
}

void SpritePlus::moveFrame(float x, float y)
{
	x += getFrame().x;
	y += getFrame().y;
	setFrame(x, y);
	return;
}
void SpritePlus::moveFrame(sf::Vector2f move)
{
	moveFrame(move.x, move.y);
}
void SpritePlus::moveFrameTo(direction position)
{
	switch (position)
	{
	case NORTH:
		setFrame(getFrame().x, 0);
		break;
	case EAST:
		setFrame(getFrameFit().x, getFrame().y);
		break;
	case SOUTH:
		setFrame(getFrame().x, getFrameFit().y);
		break;
	case WEST:
		setFrame(0, getFrame().y);
		break;
	}
}

#pragma endregion

#pragma region AllTextures

AllTextures::AllTextures()
{

}

void AllTextures::loadSheets()
{
	props_.clear();
	floors_.clear();
	walls_.clear();
	doors_.clear();

	sf::Texture sheet;

	sf::Vector2i size; 
	sf::Vector2i position;

	//prop sheet
	size = sf::Vector2i(100, 100);
	sheet.loadFromFile("Resources/props.png");

	for (int c = 0; c < propType::COUNT_PROPTYPE; c++)
	{
		for (int d = 0; d < 4; d++)
		{
			position.x = size.x * c;	position.y = size.y * d;
			props_[c][d].loadFromImage(sheet.copyToImage(), sf::IntRect(position, size));
		}
	}


	//floors
	size = sf::Vector2i(100, 100);
	sheet.loadFromFile("Resources/floors.png");
	for (int c = 0; c < floorType::COUNT_FLOORTYPE; c++)
		floors_[c].loadFromImage(sheet.copyToImage(), sf::IntRect(size.x*c, 0, size.x, size.y));


	//walls
	size = sf::Vector2i(100, 160); //if 160 will be the height of the wall
	sheet.loadFromFile("Resources/walls.png");

	for (int c = 0; c < wallType::COUNT_WALLTYPE; c++)
		for (int d = 0; d < 4; d++)
			props_[c][d].loadFromImage(sheet.copyToImage(), sf::IntRect(size.x*c, size.x*d, size.x, size.y));


	//doors
	size = sf::Vector2i(200, 100);	//size of open and closed door in one texture
	sheet.loadFromFile("Resources/doors.png");

	for (int c = 0; c < doorType::COUNT_DOORTYPE; c++)
		for (int d = 0; d < 4; d++)
			props_[c][d].loadFromImage(sheet.copyToImage(), sf::IntRect(size.x*c, size.x*d, size.x, size.y));
}

void AllTextures::loadAll()
{
	lever_.loadFromFile("Resources/lever.png");
	plug_.loadFromFile("Resources/plug.png");
	bulb_.loadFromFile("Resources/bulb.png");
	loadSheets();
}

sf::Texture* AllTextures::prop(propType type, direction facing) const
{
	return &props_[(int)type][(int)facing];
}
sf::Texture* AllTextures::floor(floorType type) const
{
	return &floors_[type];
}
sf::Texture* AllTextures::walls(wallType type, direction facing) const
{
	return &walls_[(int)type][(int)facing];
}
sf::Texture* AllTextures::door(doorType type, direction facing) const
{
	return &doors_[(int)type][(int)facing];
}
sf::Texture* AllTextures::lever() const
{
	return &lever_;
}
sf::Texture* AllTextures::bulb() const
{
	return &bulb_;
}
sf::Texture* AllTextures::plug() const
{
	return &plug_;
}

#pragma endregion

#pragma region LineShape

LineShape::LineShape(sf::Vector2i t_start, sf::Vector2i t_end, sf::Color color)
{
	start = t_start;
	end = t_end;

	theta = std::atan((end.y-start.y)/(end.x-start.x));

	distance = std::sqrt(std::pow(end.x-start.x,2) + std::pow(end.y-start.y,2));

	setPosition(start.x, start.y);
	setSize(sf::Vector2f(distance, LINE_THICKNESS));
	setRotation(theta);
	setColor(color);
}

sf::Vector2i LineShape::getStart()
{
	return start;
}
sf::Vector2i LineShape::getEnd()
{
	return end;
}
int LineShape::getThickness()
{
	return getSize().y;
}

//sets
void LineShape::setStart(sf::Vector2i point)
{
	start = point;
}
void LineShape::setEnd(sf::Vector2i point)
{
	end = point;
}
void LineShape::setThickness(int thickness)
{
	setSize(sf::Vector2f(distance, thickness));
}
void LineShape::setColor(sf::Color color)
{
	setColor(color);
}

//checks
bool LineShape::intersects(LineShape other)
{
	return getGlobalBounds().intersects(other.getGlobalBounds());
}
bool LineShape::intersects(sf::RectangleShape other)
{
	return getGlobalBounds().intersects(other.getGlobalBounds());
}

#pragma endregion

#pragma region CurveShape

CurveShape::CurveShape(std::vector<sf::Vector2i> points, sf::Color color = sf::Color::Green)
{
	for (int index = 0; index < points.size()-1; index++)
	{
		LineShape temp_line(points[index], points[index+1], color);
		lines.push_back(temp_line);
	}
}

void CurveShape::recreate(std::vector<sf::Vector2i> points, sf::Color color = sf::Color::Green)
{
	lines.clear();
	for (int index = 0; index < points.size()-1; index++)
	{
		LineShape temp_line(points[index], points[index+1], color);
		lines.push_back(temp_line);
	}
}

void CurveShape::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (const auto &temp : lines)
		target.draw(temp, states);
}

#pragma endregion

#pragma region SettingsInfo

SettingsInfo::SettingsInfo(sf::VideoMode win_res = sf::VideoMode(800, 600), unsigned short vol = 50, 
						   sf::Uint32 t_style = sf::Style::Fullscreen, std::string window_title = "Psychosis")
{
	window_name = window_title;
	resolution = win_res;
	style = t_style;
	if (vol >= 100)
		volume = 100;
	else
		volume = vol;
}

bool SettingsInfo::load(int file);
void SettingsInfo::save(int file);

#pragma endregion