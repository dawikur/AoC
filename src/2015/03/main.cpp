// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

int main ()
{
	std::unordered_set<qrd::Point<int>> houses;

	qrd::Point<int> p;
	qrd::Point<int> p1;

	houses.insert ({});

	std::string const input = qrd::read_input (__FILE__) [0];
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
