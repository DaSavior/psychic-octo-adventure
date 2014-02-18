#ifndef UIUTILITIES_H
#define UIUTILITIES_H

class Textbox;
class Button;

#include "Common.h"
#include "ClassUtilities.h"

class Textbox: public sf::Text, public Animateable
{
private:
	sf::RectangleShape box_;
	std::string scroll_;
	std::string line_;

	bool autoFit_;
	textStyle style_;
public:
	Textbox();
	
	//gets
	std::string getScroll() const;
	sf::IntRect getTextBounds() const;
	sf::IntRect getBoxBounds() const;
	textStyle getTextStyle() const;

	//sets
	void setScroll(std::string scroll);
	void setBox(sf::IntRect rect);
	void setAutoFit(bool autoFit);
	void setTextStyle(textStyle style);

	//checks
	bool isOpen() const;
	bool hasScroll() const;
	bool hasNextLine() const;

	//changes
	void fitBox(); //fits box around text (will be called automatically if autoFit_ is true)
	void styleText();	//will move text around to match selected style (mostly called automatically)
	void appendScroll(std::string scroll);
	void close();
	void scrollText();
	void finishLine();

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
	void fitEffects(); //fits highlight and sprite onto box

	void highlight(sf::Color color);
	void addEffect(sf::Sprite sprite);
	void removeHighlight();
	void removeEffect();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif