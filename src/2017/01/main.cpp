// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <aoc/file.hpp>
#include <aoc/std.hpp>

int main ()
{
	std::string const line = aoc::read_input (__FILE__) [0];
	auto const        dpos = line.size () / 2;

	int sum {};

	for (std::size_t i = 0; i < line.size (); ++i) {
		if (line [i] == line [(i + dpos) % line.size ()]) {
			sum += (line [i] - '0');
		}
	}

	std::cout << "Captcha: " << sum << std::endl;
}
