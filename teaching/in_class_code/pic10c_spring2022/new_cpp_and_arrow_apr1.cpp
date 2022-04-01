#include<iostream>
#include<string>

struct bah {
	int i, j;

	// c++ 20
	constexpr auto operator<=>(const bah&) const = default;
};

struct Foo {
	struct Bar {
		std::string s = "hello";

		const std::string* operator->() const { return &s; }
	};

	Bar b{};

	const Bar& operator->() const { return b; }
};

int main() {
	bah b{ 2,3 };
	bah b2{ 7, 8 };

	// c++17
	auto& [x, y] = b; // structured bindings
	std::cout << x << y << '\n';

	b < b2;
	b == b2;

	Foo f;
	std::cout << f->size();

	return 0;


}
