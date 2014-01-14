#ifndef UIUTILITY_H
#define UIUTILITY_H

#include "Common.h"

class Textbox: public sf::Sprite
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