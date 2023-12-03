// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <cmath>

#include <iostream>

#include <dku/file.hpp>
#include <dku/std.hpp>

auto const INPUT = 361527;

int main ()
{
	double input = INPUT;
	std::cout << "    INPUT: " << input << std::endl << std::endl;

	{
		std::cout << "     PART: 1" << std::endl;

		auto shell = std::floor (std::ceil (std::sqrt (input)) / 2);
		std::cout << "    shell: " << shell << std::endl;

		auto prev_max = std::pow (2 * shell - 1, 2.0);

		std::cout << " prev max: " << prev_max << std::endl;

		auto side_size = shell * 2;

		std::cout << "side size: " << side_size << std::endl;

		auto to_center
			= std::abs (shell - (int (input - prev_max) % int (side_size)));

		std::cout << "to center: " << to_center << std::endl;

		auto to_middle = to_center + shell;

		std::cout << "to middle: " << to_middle << std::endl;
	}

	{
		std::cout << "     PART: 2" << std::endl;

		std::size_t                   size = 11;
		std::vector<std::vector<int>> grid (size, std::vector<int> (size, 0));

		auto sum = [&] (size_t x, size_t y) {
			int v {};

			v += grid [x - 1][y - 1];
			v += grid [x - 1][y];
			v += grid [x - 1][y + 1];

			v += grid [x + 1][y - 1];
			v += grid [x + 1][y];
			v += grid [x + 1][y + 1];

			v += grid [x][y - 1];
			v += grid [x][y + 1];

			return v;
		};

		std::size_t x = size / 2;
		std::size_t y = size / 2;

		grid [x][y] = 1;

		for (std::size_t shell = 1; shell < size / 2; ++shell) {
			std::cout << "shell: " << shell << std::endl;
			++x;
			++y;

			std::size_t side_size = 2 * shell;

			for (size_t d = 0; d < side_size; ++d) {
				--y;
				grid [x][y] = sum (x, y);

				if (INPUT < grid [x][y]) {
					std::cout << "First larger: " << grid [x][y] << std::endl;
					return 0;
				}
			}
			for (size_t d = 0; d < side_size; ++d) {
				--x;
				grid [x][y] = sum (x, y);

				if (INPUT < grid [x][y]) {
					std::cout << "First larger: " << grid [x][y] << std::endl;
					return 0;
				}
			}
			for (size_t d = 0; d < side_size; ++d) {
				++y;
				grid [x][y] = sum (x, y);

				if (INPUT < grid [x][y]) {
					std::cout << "First larger: " << grid [x][y] << std::endl;
					return 0;
				}
			}
			for (size_t d = 0; d < side_size; ++d) {
				++x;
				grid [x][y] = sum (x, y);

				if (INPUT < grid [x][y]) {
					std::cout << "First larger: " << grid [x][y] << std::endl;
					return 0;
				}
			}
		}

		for (std::size_t i = 0; i < size; ++i) {
			for (std::size_t j = 0; j < size; j++) {
				std::cout << grid [j][i] << "\t";
			}
			std::cout << std::endl;
		}
	}
}
