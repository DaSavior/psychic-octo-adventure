
#include <SFML\Graphics.hpp>

int main()
{
	sf::Sprite test_sprite;
	sf::Texture test1;
	sf::Texture test2;
	bool draw_test = false;

	test1.loadFromFile("..\\..\\..\\..\\..\\Pictures\\tibet_lake_wallpaper_by_feliskachu-d5qy6qv.jpg");
	test_sprite.setTexture(test1);
	
	sf::RenderWindow window (sf::VideoMode(800,600), "test");
	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
				draw_test = true;
		}

		window.clear();

		
		if(draw_test)
		{
			test2.loadFromImage(test1.copyToImage(), sf::IntRect(100, 100, 200, 200));
			test2.setRepeated(true);
			test_sprite.setTexture(test2, false);
		}
		
		window.draw(test_sprite);
		window.display();
	}

	return 0;
}