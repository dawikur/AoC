// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <aod/file.hpp>
#include <aod/std.hpp>

int main ()
{
	int possible_games {};
	int power_games {};
	for (auto const& line: aod::read_input (__FILE__)) {
		int min_red {};
		int min_green {};
		int min_blue {};

		std::stringstream ss {line};

		std::string val;
		std::getline (ss, val, ':');

		int id;
		std::sscanf (val.c_str (), "Game %d", &id);

		bool possible = true;

		while (std::getline (ss, val, ';')) {
			std::stringstream ss2 {val};

			while (std::getline (ss2, val, ',')) {
				char color [10];
				int  count;

				std::sscanf (val.c_str (), "%d %s", &count, color);

				if (color [0] == 'r') {
					if (count > 12) { possible = false; }
					if (min_red < count) { min_red = count; }
				} else if (color [0] == 'g') {
					if (count > 13) { possible = false; }
					if (min_green < count) { min_green = count; }
				} else if (color [0] == 'b') {
					if (count > 14) { possible = false; }
					if (min_blue < count) { min_blue = count; }
				}
			}
		}

		if (possible) { possible_games += id; }

		power_games += min_red * min_green * min_blue;
	}

	std::cout << "Sum of possible games: " << possible_games << std::endl;
	std::cout << "  Sum of games' power: " << power_games << std::endl;
}
