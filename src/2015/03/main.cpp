// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <cassert>

#include <dku/file.hpp>
#include <dku/point.hpp>
#include <dku/std.hpp>

int main ()
{
	std::unordered_set<dku::Point<int>> houses;

	dku::Point<int> p;
	dku::Point<int> p1;

	houses.insert ({});

	std::string const input = dku::read_input (__FILE__) [0];
	for (auto const& c: input) {
		switch (c) {
			case '^': ++p.y; break;
			case 'v': --p.y; break;
			case '<': --p.x; break;
			case '>': ++p.x; break;
			default: assert (false); break;
		}

		houses.insert (p);

		std::swap (p, p1);
	}

	std::cout << "Houses visided: " << houses.size () << std::endl;

	return 0;
}
