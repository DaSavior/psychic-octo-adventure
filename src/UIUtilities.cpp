#include "..\include\UIUtilities.h"

#pragma region TextBox

Textbox::Textbox() : sf::Text()
{
	scroll_ ="";
	line_ ="";
}
	
std::string Textbox::getScroll() const
{
	return scroll_;
}
sf::IntRect Textbox::getTextBounds() const
{
	sf::FloatRect r = sf::Text::getGlobalBounds();
	return sf::IntRect (r.left, r.top, r.width, r.height);
}
sf::IntRect Textbox::getBoxBounds() const
{
	sf::FloatRect r = box_.getGlobalBounds();
	return sf::IntRect (r.left, r.top, r.width, r.height);
}
textStyle Textbox::getTextStyle() const
{
	return style_;
}

void Textbox::setScroll(std::string scroll)
{
	scroll = scroll;
}
void Textbox::setBox(sf::IntRect rect)
{
	box_.setPosition(rect.left, rect.top); //TODO: make this affect the box the text is in
	box_.setSize(sf::Vector2f(rect.width, rect.height));
	if (autoFit_)
		fit();
}
void Textbox::setAutoFit(bool autoFit)
{
	autoFit_ = autoFit;
}
void Textbox::setTextStyle(textStyle style)
{
	style_ = style;
}

bool Textbox::isOpen() const
{
	return !(getString() == "" && line_ == "")
}

void Textbox::fitBox();
void Textbox::styleText();
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

	if (autoFit_)
		fitBox();
	styleText();
}
void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const;

#pragma endregion

#pragma region Button

Button::Button() :Textbox::Textbox()
{
	fit();
}
void Button::fitEffects(); 

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

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const;

#pragma endregion