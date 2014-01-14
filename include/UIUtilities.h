#ifndef UIUTILITIES_H
#define UIUTILITIES_H

#include "Common.h"

class Textbox: public sf::Text
{
private:
	
public:
	Textbox();
};

class Button: public Textbox
{
private:

public:
	Button();
};

#endif