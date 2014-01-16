#include "..\include\UIUtilities.h"

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text::draw(target, states);
	sf::RectangleShape::draw(target, states);
}
