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
	//std::string getLine() const;
	
	//sets
	void setScroll(std::string scroll);
	//void setLine();

	//checks
	bool isOpen() const;

	//changes
	void appendScroll(std::string scroll);
	void close();

	//virtuals
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sf::RectangleShape(getSize()), sf::RectangleShape::getTransform());
		target.draw(sf::Text(getString(), *getFont(), getCharacterSize()), sf::Text::getTransform());
	};

};

class Button: public Textbox
{
private:

public:
	Button();
};

#endif