#define ex_intro 1
#define ex_triangle 0
#define ex_semi 0
#define ex_fonts 0
#define ex_arrows 0
#define ex_time 0
#define ex_ball 0
#define ex_file_click 0
#define ex_mouse_pos 0


#if ex_intro 
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f, 3);
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
		//window.display();
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
	
	/*
	sf::Vertex triangle[] =
	{ sf::Vertex(sf::Vector2f(window_width / 2, padding)),
	sf::Vertex(sf::Vector2f(padding, padding + height)),
	sf::Vertex(sf::Vector2f(padding + base, padding + height))
	};*/

	sf::Vertex triangle[] = { sf::Vertex(sf::Vector2f(window_width / 2, padding),
	sf::Color::Red),
	sf::Vertex(sf::Vector2f(padding, padding + height), sf::Color::Green),
	sf::Vertex(sf::Vector2f(padding + base, padding + height), sf::Color::Blue)
	};

	
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
		
		window.draw(triangle, 3, sf::Triangles);		
		window.display();
	}
	return 0;
}

#elif ex_semi

#include <SFML/Graphics.hpp>

class semi_circle : public sf::Shape {
private:
	sf::Vector2f left;  // left part
	float rad; // radius
	constexpr static size_t num_pts = 20;
	constexpr static size_t half_pts = 10;
	constexpr static float pi = 3.14159265358979f;
public:
	semi_circle(sf::Vector2f _left, float _rad) :
		left(std::move(_left)), rad(_rad) {
		update();
	}

	size_t getPointCount() const override {
		return num_pts;
	}

	sf::Vector2f getPoint(size_t i) const override {
		if (i < half_pts) { // bottom? 
			const sf::Vector2f right = left + sf::Vector2f{ 2 * rad,0.f };
			float f = static_cast<float>(i) / half_pts; // fraction from left to right
			return (1 - f) * left + f * right;
		}
		else {
			const sf::Vector2f centre = left + sf::Vector2f{ rad,0.f };
			float f = static_cast<float>(i-half_pts) / half_pts; // fraction of pi radians
			return centre + rad * sf::Vector2f{ std::cos(pi * f), -std::sin(pi * f) };
		}
	}
};

int main() {

	semi_circle c{ {0.f,200.f},50.f };

	
	sf::RenderWindow window(sf::VideoMode(400,
		400), "Triangle!");

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
					msg.move(0.f, -dy);
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
		}
		window.clear();
		window.draw(circ);
		window.draw(msg);
		window.display();
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
		
		float total_time = timer.getElapsedTime().asSeconds();
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

#elif ex_file_click

#include <SFML/Graphics.hpp>
#include<filesystem>
#include<fstream>
#include<iostream>
#include<numeric>
#include<vector>

class text_image {
private:
	sf::RectangleShape rect; // boundary
	sf::Text text; // text content 
	sf::Color back_colour, text_colour; // background and text colours
public:
	/**
	makes a text_image object to store text in a rectangle
	@param _pos the position of the top-left
	@param _dims the dimensions at the boundary
	@param _content the text content
	@param _font the font style
	@param _back_colour the background colour
	@param _text_colour the text colour
	*/
	text_image(sf::Vector2f _pos, sf::Vector2f _dims, std::string _content, sf::Font& _font,
		sf::Color _back_colour, sf::Color _text_colour) : rect(std::move(_dims)),
		back_colour(std::move(_back_colour)), text_colour(std::move(_text_colour))
	{
		rect.setPosition(_pos);
		rect.setFillColor(back_colour);

		text.setFont(_font);
		text.setString(std::move(_content));
		text.setPosition(std::move(_pos));
		text.setFillColor(text_colour);
	}

	/**
	draw the object in a window
	@param w the object in which to be drawn
	*/
	void get_drawn_by(sf::RenderWindow& w) const {
		w.draw(rect);
		w.draw(text);
	}

	/**
	determines if a position falls within the boundary
	@param pos the position to test
	@return whether it falls within the boundary
	*/
	bool in(const sf::Vector2i& pos) const {
		const sf::Vector2f rect_pos = rect.getPosition();
		const sf::Vector2f rect_size = rect.getSize();
		const float left_x = rect_pos.x;
		const float right_x = rect_pos.x + rect_size.x;
		const float top_y = rect_pos.y;
		const float bottom_y = rect_pos.y + rect_size.y;
		return (left_x <= pos.x) && (pos.x <= right_x) &&
			(top_y <= pos.y) && (pos.y <= bottom_y);
	}

	/**
	returns the text content
	@return content as an std::string
	*/
	std::string get_text() const {
		return text.getString().toAnsiString();
	}

	/**
	assigns the text content
	@param _text the text content to set
	*/
	void set_text(std::string _text) {
		text.setString(std::move(_text));
	}
};

/**
reads from a file with a certain width to "wrap around"
@param fname the file to read from
@param max_width the maximum width before wrapping
@return a string that wraps as prescribed not exceeding max_lines
*/
std::string read_file(std::string fname, const size_t max_width) {
	std::ifstream fin(std::move(fname));
	if (!fin) {
		return "file not found\n";
	}
	std::string res;
	char c;
	size_t col = 0;
	while (fin.peek() != EOF) {
		c = fin.get();
		if (c == '\n') {
			col = 0;
		}
		else if (++col % max_width == 0) {
			res += '\n';
		}
		res += c;
	}
	fin.close();
	return res;
}


int main() {

	constexpr size_t txt_len = 4; // length of ".txt"

	constexpr float window_width = 700.f;
	constexpr float window_height = 500.f;

	constexpr size_t max_char_per_line = 50;

	const sf::Color list_back_colour = sf::Color::Blue;
	const sf::Color list_text_colour = sf::Color::White;

	const sf::Color file_back_colour = sf::Color::Magenta;
	const sf::Color file_text_colour = sf::Color::Black;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "File Explorer");
	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(100);

	constexpr float entry_height = 50.f;

	sf::Font sans;
	if (!sans.loadFromFile("sansation.ttf")) { // cannot load
		throw std::runtime_error("Font Loading Failed");
	}

	std::vector<text_image> files;

	float pos = 0.f; // y position of content

	std::filesystem::directory_iterator curr(std::filesystem::current_path());

	// loop through current directory 
	for (const auto& p : curr) {
		if (p.is_regular_file()) { // regular file
			std::string name = p.path().filename().string();
			// name could end in ".txt" and does
			if (name.size() > txt_len&& name.substr(name.size() - txt_len) == ".txt") {
				// add this file to the listing
				files.emplace_back(sf::Vector2f{ 0.f, pos }, sf::Vector2f{ window_width, entry_height },
					std::move(name), sans, list_back_colour, list_text_colour);
				pos += entry_height;
			}
		}
	}

	// content height is rest of space
	const float content_height = window_height - pos;



	text_image content{ sf::Vector2f{ 0.f, pos }, sf::Vector2f{ window_width, content_height },
		"", sans, file_back_colour, file_text_colour };

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed) { // closed
				window.close();
			}
			// pressed a mouse button
			else if (e.type == sf::Event::MouseButtonPressed) {
				// extract the coordinates
				const sf::Vector2i coords = { e.mouseButton.x, e.mouseButton.y };

				for (const auto& file : files) { // look over all files
					if (file.in(coords)) { // if click in a file's boundary, read file and display
						std::string fname = file.get_text();
						std::string words = read_file(std::move(fname), max_char_per_line);
						content.set_text(words);
					}
				}
			}
		}

		window.clear();

		for (const auto& f : files) { // display the list            
			f.get_drawn_by(window);
		}
		content.get_drawn_by(window); // display the file contents
		window.display();
	}

	return 0;
}


#elif ex_mouse_pos

#include<SFML/Graphics.hpp>
#include<string>

int main() {
	sf::RenderWindow w(sf::VideoMode(400, 400), "Mouse Pos");

	sf::Font f;
	if (!f.loadFromFile("sansation.ttf")) {
		return -1;
	}

	sf::Text t;
	t.setFont(f);
	t.setFillColor(sf::Color(100, 100, 100));


	while (w.isOpen()) {
		sf::Event e;
		while (w.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				w.close();
			}
		}

		auto pos = sf::Mouse::getPosition(w);

		t.setString(std::to_string(pos.x) + ", " + std::to_string(pos.y));

		w.clear();
		w.draw(t);
		w.display();

	}

	return 0;

}

#endif
