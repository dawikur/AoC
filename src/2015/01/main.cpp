// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <aod/file.hpp>
#include <aod/std.hpp>

int main ()
{
	auto const input = aod::read_input (__FILE__) [0];

	int part1 {};
	int part2 {};

	for (std::size_t i = 0; i < input.size (); ++i) {
		if (input [i] == '(') {
			++part1;
		} else {
			--part1;
		}

		if (part1 == -1 && part2 == 0) { part2 = static_cast<int> (i) + 1; }
	}

	std::cout << "                Last floor: " << part1 << std::endl;
	std::cout << "Position entering gasement: " << part2 << std::endl;
}
