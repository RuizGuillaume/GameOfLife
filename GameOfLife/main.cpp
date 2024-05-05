#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grille.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1800, 1100), "Game Of Life");
	window.setFramerateLimit(20);
	sf::View view(sf::Vector2f(900, 550), sf::Vector2f(1800, 1100));

	Grille grille;
	bool gameStarted = 0;
	bool firstTurn = 1;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseWheelMoved)
			{
				std::cout << event.mouseWheel.delta << std::endl;
				grille.zoom(view, event.mouseWheel.delta);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				gameStarted = 1;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				gameStarted = 0;
		}

		window.clear();

		window.setView(view);
		grille.move(view);

		grille.afficherUnivers(window);

		grille.clickEtatCellule(window);

		if (gameStarted == 1)
			grille.startGame(firstTurn);
		
		grille.draw(window);


		window.display();
	}

	return 0;
}