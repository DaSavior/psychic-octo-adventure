#include "..\include\UIUtilities.h"


Textbox::Textbox() :sf::RectangleShape(), sf::Text()
{
	scroll_ ="";
	line_ ="";
}
	
std::string Textbox::getScroll() const
{
	return scroll_;
}
sf::IntRect Textbox::getRectangle() const
{
	sf::FloatRect r = sf::RectangleShape::getGlobalBounds();
	return sf::IntRect (r.left, r.top, r.width, r.height);
}

void Textbox::setScroll(std::string scroll)
{
	scroll = scroll;
}
void Textbox::setRectangle(sf::IntRect rect)
{
	sf::RectangleShape::setPosition(rect.left, rect.top);
	sf::RectangleShape::setSize(rect.width, rect.height);
	fit();
}

bool Textbox::isOpen() const
{
	return !(getString() == "" && line_ == "")
}

void Textbox::fit();
void Textbox::appendScroll(std::string scroll)
{
	scroll_ += scroll;
}
void Textbox::close()
{
	setString("");
	scroll_ = "";
	line_ = "";
}
void Textbox::scrollText()
{
	setString("");
	line_ = "";

	if (scroll_.empty())
		return;

	std::size_t endOfLine = scroll_.find('\n');
	line_ = scroll_.substr(0, endOfLine);
	scroll_ = scroll_.substr(endOfLine, (scroll_.length() - endOfLine));
}

void Textbox::animate()
{
	if (line_.empty())
		return;

	setString(getString() + line_.front());
	line_ = line_.substr(1, line_.size() -1);

	fit();
}
void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const;


Button::Button() :Textbox::Textbox()
{
	fit();
}
void Button::fit();

void Button::highlight(sf::Color color)
{
	highlight_.setFillColor(color);
	fit();
}
void Button::addEffect(sf::Sprite sprite)
{
	effect_ = sprite;
	fit();
}
void Button::removeHighlight()
{
	highlight(sf::Color::Transparent);
}
void Button::removeEffect()
{
	effect_.setTexture(sf::Texture());
}

bool Button::contains(sf::Vector2i point)
{
	return getRectangle().contains(point);
}
bool Button::intersects(sf::IntRect rect)
{
	return getRectangle().intersects(rect);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{

}