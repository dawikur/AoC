// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <cassert>

#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>

#include <aod/file.hpp>

struct Point
{
	int x {};
	int y {};

	bool operator== (Point const& p) const { return x == p.x && y == p.y; }
};

template <>
struct std::hash<Point>
{
	std::size_t operator() (Point const& p) const
	{
		return std::hash<int> {}(p.x) ^ (std::hash<int> {}(p.y) << 1);
	}
};

int main ()
{
	std::unordered_set<Point> houses;

	Point p;
	Point p1;

	houses.insert ({});

	std::string const input = aod::read_input (__FILE__) [0];
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
}
