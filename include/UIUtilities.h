#ifndef UIUTILITIES_H
#define UIUTILITIES_H

#include "Common.h"
#include "ClassUtilities.h"


class Textbox: public sf::Text, public Animateable
{
private:
	sf::RectangleShape box;
	std::string scroll_;
	std::string line_;

	bool fixedsize_aka_ithinkitsaysfitwillnotchangeitbasicallywhatwouldthatbeifitwastrueofifitwasfalsefitwouldnothappen;
public:
	Textbox();
	
	//gets
	std::string getScroll() const;
	sf::IntRect getRectangle() const;
	sf::Vector2i getBoxSize() const;

	//sets
	void setScroll(std::string scroll);
	void setRectangle(sf::IntRect rect);
	void setBoxSize(sf::Vector2i t_size);
	//void setLine();

	//checks
	bool isOpen() const;

	//changes
	void fit();
	void appendScroll(std::string scroll);
	void close();
	void scrollText();

	//virtuals
	virtual void animate();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Button: public Textbox
{
private:
	sf::RectangleShape highlight_;
	sf::Sprite effect_;

public:
	Button();
	void fit();

	bool Button::contains(sf::Vector2i point);
	bool Button::intersects(sf::IntRect rect);

	void highlight(sf::Color color);
	void addEffect(sf::Sprite sprite);
	void removeHighlight();
	void removeEffect();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif