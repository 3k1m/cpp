#include<thread>
#include<mutex>
#include<chrono>
#include<random>
#include<future>
#include<numeric>
#include<atomic>
#include<iostream>

#include<SFML/Graphics.hpp>

class Pop {
private:
	int N;
	double delta, mu;
	mutable std::mutex m;
	const std::atomic<bool>& done;

	constexpr static std::chrono::seconds wait{ 2 };
	constexpr static double dT = 1;
	static inline unsigned num_avail = std::thread::hardware_concurrency();

	int diff(int M) const {
		thread_local std::random_device rd;
		thread_local std::exponential_distribution<> grow{ delta };
		thread_local std::exponential_distribution<> death{ mu };
		int change = 0; // net change

		for (int i = 0; i < M; ++i) { // outcome for M bacteria
			double g_time = grow(rd); // growth and death times
			double d_time = death(rd);
			if (g_time < d_time) { // would double before die
				if (g_time < dT) { // and divides in time step
					++change;
				}
			}
			else { // death time sooner
				if (d_time < dT) { // dies within time step
					--change;
				}
			}
		}
		return change;
	}

	void change_N(int diff) {
		std::lock_guard lock{ m };
		N += diff;
	}

	void callback() {
		do { // pause and run
			std::this_thread::sleep_for(wait);
			evolve();
		} while (!done); // until window closes
	}

	void evolve() {
		int Now = get_N(); // current population
		// number per thread
		int block = 1 + Now / num_avail;
		// how many bacteria are “running”, i.e., being simulated
		int running = 0;

		// calculates changes per group in thread
		std::vector<std::future<int> > changes;
		while (running + block < Now) { // would not yet exceed population
			changes.push_back(
				std::async(std::launch::async | std::launch::deferred,
					&Pop::diff, this, block));
			running += block; // block many more are being simulated
		}
		// handle the extras
		changes.push_back(
			std::async(std::launch::async | std::launch::deferred,
				&Pop::diff, this, Now - running)); // Now-running are the remainder

		// total difference
		int tot_diff = std::accumulate(changes.begin(),
			changes.end(), 0, [](int curr, auto& fut) {
				return curr + fut.get(); // get the int with get
			});
		change_N(tot_diff); // update N (will be thread-safe)

	}

public:
	int get_N() const {
		std::lock_guard lock{ m };
		return N;
	}

	Pop(int N0, double _delta, double _mu, const std::atomic<bool>& _done) : N(N0), delta(_delta),
		mu(_mu), done(_done) {
		std::thread(&Pop::callback, this).detach(); // start evolving
	}
};



int main() {
	constexpr int N0 = 100000; // initial population
	constexpr double delta = 0.1; // growth rate /hour
	constexpr double mu = 0.05; // death rate /hour
	constexpr float width = 500; // window width
	constexpr float height = 200; // window height
	constexpr float pop_init_width = 100; // width for initial population

	std::atomic<bool> done = false;

	sf::RenderWindow window(sf::VideoMode(width, height), "Population");
	Pop p{ N0, delta, mu, std::cref(done) }; // population initialization
  
	while (window.isOpen()) { // user not closed yet
		sf::Event e;

		// usual stay open till closed
		while (window.pollEvent(e)) { 
			if (e.type == sf::Event::Closed) {
				window.close();
			}
		}
		sf::RectangleShape rect{
		sf::Vector2f{ pop_init_width * p.get_N() / N0, height / 2} };
		rect.move(0, height / 4); // so centered
		rect.setFillColor(sf::Color::Green);
		window.clear();
		window.draw(rect);
		window.display();
	}
	done = false; // can stop evolving the population
	std::cout << "Simulation Terminated\n";
  
	return 0;
}
