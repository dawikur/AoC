//
// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

std::vector<std::string> const test_input {"467..114..",
										   "...*......",
										   "..35..633.",
										   "......#...",
										   "617*......",
										   ".....+.58.",
										   "..592.....",
										   "......755.",
										   "...$.*....",
										   ".664.598.."};

bool is_symbol (char const token)
{
	if (token == '.') { return false; }
	if (std::isdigit (static_cast<unsigned char> (token))) { return false; }
	return true;
}

int main ()
{
	auto input = qrd::read_file (__FILE__);
	// auto input = test_input;

	std::unordered_map<std::size_t,
					   std::unordered_map<std::size_t, std::vector<int>>>
		gears {};

	std::string prev_line {};
	std::string curr_line {};

	input.emplace_back (input.front ().size (), '.');

	for (std::size_t xj {}; xj < input.size (); ++xj) {
		auto& next_line = input [xj];

		std::cout << std::endl;
		next_line = '.' + next_line + '.';

		if (curr_line.empty ()) {
			prev_line = std::string (next_line.size (), '.');
			curr_line = next_line;

			continue;
		}

		int         number {};
		std::size_t x {};
		std::size_t y {};
		bool        is_gear {};

		for (size_t i {1U}; i < curr_line.size () - 1U; ++i) {
			auto const token = curr_line [i];

			if (std::isdigit (static_cast<unsigned char> (token))) {
				number *= 10;
				number += token - '0';

				for (auto const& xi: {i - 1, i, i + 1}) {
					auto J = xj - 1;
					for (auto const& line: {prev_line, curr_line, next_line}) {
						if (line [xi] == '*') {
							x       = xi;
							y       = J;
							is_gear = true;
						}

						++J;
					}
				}
			} else {
				if (number != 0) {
					if (is_gear) {
						gears [x][y].emplace_back (number);
						std::cout << "\033[31m" << number << "\033[0m";
					} else {
						std::cout << number;
					}
				}
				number  = {};
				x       = {};
				y       = {};
				is_gear = {};

				if (token == '*') {
					std::cout << "\033[33m" << token << "\033[0m";
				} else {
					std::cout << token;
				}
			}
		}

		if (number != 0) {
			if (is_gear) {
				gears [x][y].emplace_back (number);
				std::cout << "\033[31m" << number << "\033[0m";
			} else {
				std::cout << number;
			}
		}
		number  = {};
		x       = {};
		y       = {};
		is_gear = {};

		prev_line = curr_line;
		curr_line = next_line;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	int sum {};
	for (auto const& [x, ys]: gears) {
		for (auto const& [y, numbers]: ys) {
			if (numbers.size () == 2) { sum += numbers [0] * numbers [1]; }
		}
	}

	std::cout << sum << std::endl;

	return 0;
}
