// do not worry about this just yet...

#include "Accumulator.h"

Accumulator::Accumulator() : total(0) {}

Accumulator::Accumulator(int _offset) :
	total(_offset) {}

void Accumulator::add(int _to_add) {
	total += _to_add;
}

int Accumulator::get_total() const {
	return total;
}
