#include <SFML/Graphics.hpp>
#include "FluidCube.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(256, 256), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Red);

	FluidCube fc(0.1, 0, 0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		fc.step();
		window.draw(shape);
		window.display();
	}

	return 0;
}

