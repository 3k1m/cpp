#include<SFML/Graphics.hpp>

int main() {

	sf::RenderWindow window(sf::VideoMode(500, 600),
			"Title");

	sf::CircleShape circ{ 100. };
	circ.setFillColor(sf::Color::Blue);

	while (window.isOpen()) {

		sf::Event e;
		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed) {
				window.close();
			}

		}


		window.clear();// sf::Color::Green);
		window.draw(circ);
		window.display();


	}







	return 0;
}
