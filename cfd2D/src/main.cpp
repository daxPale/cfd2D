#include <SFML/Graphics.hpp>
#include "FluidCube.h"

#define N 256
int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Red);

	FluidCube fc(N, 0.1, 0, 0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}

