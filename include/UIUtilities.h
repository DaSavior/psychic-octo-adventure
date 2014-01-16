#ifndef UIUTILITIES_H
#define UIUTILITIES_H

#include "Common.h"
#include "ClassUtilities.h"

//TODO: test if draw can call draw from rectngleshape and 
class Textbox: public sf::Text, public sf::RectangleShape, public Animateable
{
private:
	std::string scroll_;
	std::string line_;
	sf::RectangleShape box_;

	sf::Font font_;
	int charSize_;

	void fitText();

public:
	Textbox(): sf::Text() , sf::RectangleShape() {};
	
	//gets
	std::string getScroll() const;
	sf::IntRect getRectangle() const;

	//sets
	void setScroll(std::string scroll);
	void setRectangle(sf::IntRect rect);
	//void setLine();

	//checks
	bool isOpen() const;

	//changes
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

	void fitButton();
public:
	Button();

	void highLight(sf::Color color);
	void addEffect(sf::Sprite sprite);
	void removeHighlight();
	void removeEffect();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif