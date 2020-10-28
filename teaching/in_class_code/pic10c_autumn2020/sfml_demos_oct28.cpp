#define ex_intro 0
#define ex_triangle 0
#define ex_fonts 0
#define ex_arrows 0
#define ex_time 1
#define ex_ball 0
#define ex_other 0

#if ex_intro 
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

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

#elif ex_triangle

#include <SFML/Graphics.hpp>

int main() {
	const float ht_to_base = std::sqrt(3.f) / 2;
	constexpr float padding = 10.f;
	constexpr float base = 300.f;
	const float height = ht_to_base * base;
	const float window_width = 2 * padding + base;
	const float window_height = 2 * padding + height;

	/*sf::Vertex triangle[] =
	{ sf::Vertex(sf::Vector2f(window_width / 2, padding)),
	sf::Vertex(sf::Vector2f(padding, padding + height)),
	sf::Vertex(sf::Vector2f(padding + base, padding + height))
	};*/

	sf::Vertex triangle[] = { sf::Vertex(sf::Vector2f(window_width / 2, padding),
	sf::Color::Red),
	sf::Vertex(sf::Vector2f(padding, padding + height), sf::Color::Green),
	sf::Vertex(sf::Vector2f(padding + base, padding + height), sf::Color::Blue)
	};

	sf::CircleShape c(window_width / 2.f, 3);
	c.setPosition(window_width / 2.f, window_width / 2.f);

	sf::RenderWindow window(sf::VideoMode(window_width,
		window_height), "Triangle!");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		window.draw(c);
		//window.draw(triangle, 3, sf::Triangles);		
		window.display();
	}
	return 0;
}

#elif ex_fonts

#include <SFML/Graphics.hpp>

int main() {

	constexpr int width = 200, height = 200;

	sf::RenderWindow window(sf::VideoMode(width, height), "Fonts!");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		sf::Font sans;
		if (!sans.loadFromFile("sansation.ttf")) { // cannot load
			throw std::runtime_error("Font Loading Failed");
		}
		sf::Text msg;
		msg.setFont(sans);
		msg.setStyle(sf::Text::Italic | sf::Text::StrikeThrough);
		msg.setFillColor(sf::Color::Green);
		msg.setCharacterSize(70);
		msg.setString("ABC");
		window.clear();
		window.draw(msg); // needs to be drawn like anything else!
		window.display();
	}
	return 0;
}


#elif ex_arrows

#include <SFML/Graphics.hpp>

int main() {
	constexpr float window_width = 300;
	constexpr float window_height = 150;
	constexpr float circle_rad = 20.f;
	constexpr float text_x = 50.f;
	constexpr float text_y = 75.f;
	sf::RenderWindow window(sf::VideoMode(window_width,
		window_height), "Demo");
	sf::CircleShape circ{ circle_rad };
	circ.setFillColor(sf::Color::Red);
	constexpr float dx = 1.f;
	constexpr float dy = 1.f;
	sf::Font sans;
	if (!sans.loadFromFile("sansation.ttf")) { // cannot load

		throw std::runtime_error("Font Loading Failed");
	}
	sf::Text msg;
	msg.setFont(sans);
	msg.setPosition(text_x, text_y);
	msg.setFillColor(sf::Color::White);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) {
					circ.move(0, -dy); // smaller y means up!
					msg.setString("Pressed Up");
				}
				else if (event.key.code == sf::Keyboard::Right) {
					circ.move(dx, 0);
					msg.setString("Pressed Right");
				}
				else if (event.key.code == sf::Keyboard::Down) {
					circ.move(0, dy);
					msg.setString("Pressed Down");
				}
				else if (event.key.code == sf::Keyboard::Left) {
					circ.move(-dx, 0);
					msg.setString("Pressed Left");
				}
				else if (event.key.code == sf::Keyboard::R) {
					circ.setFillColor(sf::Color::Red);
					msg.setString("Pressed R");
				}
				else if (event.key.code == sf::Keyboard::G) {
					circ.setFillColor(sf::Color::Green);
					msg.setString("Pressed G");
				}
				else if (event.key.code == sf::Keyboard::B) {
					circ.setFillColor(sf::Color::Blue);
					msg.setString("Pressed B");
				}
			}
			else if (event.type == sf::Event::Closed) {
				window.close();
			}
			window.clear();
			window.draw(circ);
			window.draw(msg);
			window.display();
		}
	}
	return 0;
}

#elif ex_time

#include <SFML/Graphics.hpp>

int main() {

	constexpr int width = 200, height = 200;

	sf::Font sans;
	if (!sans.loadFromFile("sansation.ttf")) { // cannot load
		throw std::runtime_error("Font Loading Failed");
	}
	sf::Text elapsed;
	elapsed.setFont(sans);
	elapsed.setFillColor(sf::Color::White);
	elapsed.setCharacterSize(20);
	elapsed.setString("Elapsed Time: 0:0:0");

	sf::Clock timer;
	static constexpr int sec_per_hr = 3600;
	static constexpr int sec_per_min = 60;

	sf::RenderWindow window(sf::VideoMode(width, height), "Timer!");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		int total_time = timer.getElapsedTime().asSeconds();
		int total_elapsed = static_cast<int>(total_time);
		int hrs = total_elapsed / sec_per_hr;
		total_elapsed %= sec_per_hr;
		int min = total_elapsed / sec_per_min;
		total_elapsed %= sec_per_min;
		int sec = total_elapsed;
		elapsed.setString("Elapsed Time: " + std::to_string(hrs) + ":" +
			std::to_string(min) + ":" + std::to_string(sec));

		window.clear();
		window.draw(elapsed);
		window.display();
	}
	return 0;
}


#elif ex_ball

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ball {
private:
	sf::CircleShape circ;
public:
	ball(float rad, float x, float y) : circ(rad) {
		circ.setOrigin(rad, rad);
		circ.setPosition(x, y);
	}
	void move_x(float dx) {
		circ.move(dx, 0);
	}
	float get_left() const {
		return circ.getPosition().x - circ.getRadius();
	}
	float get_right() const {
		return circ.getPosition().x + circ.getRadius();
	}
	operator const sf::Shape& () const {
		return circ;
	}
};

int main() {
	constexpr float window_width = 300;
	constexpr float window_height = 100;
	constexpr float rect_widths = 25;

	constexpr float left_barrier = rect_widths;
	constexpr float right_barrier = window_width - rect_widths;
	constexpr float ball_rad = 10;
	constexpr float dx = 0.05;

	sf::RectangleShape left_rect{ {rect_widths, window_height} };
	left_rect.setFillColor(sf::Color::Green);
	sf::RectangleShape right_rect{ {rect_widths, window_height} };
	right_rect.setPosition(window_width - rect_widths, 0.f);
	right_rect.setFillColor(sf::Color::Green);
	ball moving_ball{ ball_rad, rect_widths + ball_rad, window_height / 2 };
	bool right = true;

	sf::SoundBuffer buff;
	if (!buff.loadFromFile("ball.wav")) {
		return -1;
	}
	sf::Sound bounce(buff);
	sf::RenderWindow window(sf::VideoMode(window_width,
		window_height), "Exercise");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (right) { // going right
			if (moving_ball.get_right() + dx < right_barrier) { // still room
				moving_ball.move_x(dx); // step
			}
			else { // no room so start left and sound
				right = false;
				bounce.play();
			}
		}
		else { // going left
			if (moving_ball.get_left() - dx > left_barrier) { // still room
				moving_ball.move_x(-dx); // step
			}
			else { // start right and sound
				right = true;
				bounce.play();
			}
		}
		window.clear();
		window.draw(left_rect);
		window.draw(moving_ball);
		window.draw(right_rect);
		window.display();
	}
	return 0;
}

#endif
