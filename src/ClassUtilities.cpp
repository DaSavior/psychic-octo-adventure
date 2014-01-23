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

void AllTextures::cutTextures()
{
	/*
	for (int c = 0, c <= num_of_textures, c++)
	{
		sf::textures
	}


	*/
}
