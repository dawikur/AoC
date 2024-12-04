// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"ULL",
	"RRDDD",
	"LURDL",
	"UUUUD",
};

// ////////////////////////////////////////////////////////////////////////////

int part_one (qrd::Input const& input)
{
	std::vector<std::vector<int>> const keypad {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	qrd::Point pos {1, 1};
    for (auto const& line : input) {
		for (auto const ch: line) {
			switch (ch) {
				case 'U':
					if (0 < pos.y) {
						--pos.y;
					}
					break;
				case 'D':
					if (pos.y < 2) {
						++pos.y;
					}
					break;
				case 'L':
					if (0 < pos.x) {
						--pos.x;
					}
					break;
				case 'R':
					if (pos.x < 2) {
						++pos.x;
					}
					break;
			}
		}

		std::cout << keypad [static_cast<std::size_t> (pos.y)]
							[static_cast<std::size_t> (pos.x)];
	}
	std::cout << std::endl;

    return 0;
}

// ////////////////////////////////////////////////////////////////////////////

int part_two (qrd::Input const& input)
{
	std::vector<std::vector<char>> const keypad {
		{ 0 ,  0 , '1',  0 ,  0 },
		{ 0 , '2', '3', '4',  0 },
		{'5', '6', '7', '8', '9'},
		{ 0 , 'A', 'B', 'C',  0 },
		{ 0 ,  0 , 'D',  0 ,  0 },
	};

	qrd::Point pos {0, 2};
    for (auto const& line : input) {
		for (auto const ch: line) {
			switch (ch) {
				case 'U':
					if (0 < pos.y) {
						if (keypad [static_cast<std::size_t> (pos.y - 1)]
								   [static_cast<std::size_t> (pos.x)] != 0) {
							--pos.y;
						}
					}
					break;
				case 'D':
					if (pos.y < 4) {
						if (keypad [static_cast<std::size_t> (pos.y + 1)]
								   [static_cast<std::size_t> (pos.x)] != 0) {
							++pos.y;
						}
					}
					break;
				case 'L':
					if (0 < pos.x) {
						if (keypad [static_cast<std::size_t> (pos.y)]
								   [static_cast<std::size_t> (pos.x - 1)] != 0) {
							--pos.x;
						}
					}
					break;
				case 'R':
					if (pos.x < 4) {
						if (keypad [static_cast<std::size_t> (pos.y)]
								   [static_cast<std::size_t> (pos.x + 1)] != 0) {
							++pos.x;
						}
					}
					break;
			}
		}

		std::cout << keypad [static_cast<std::size_t> (pos.y)]
							[static_cast<std::size_t> (pos.x)];
	}
	std::cout << std::endl;

    return 0;
}

// ////////////////////////////////////////////////////////////////////////////

int main (int const argc, char const* const argv[])
{
    auto const args = qrd::parse_args (argc, argv);

    if (!args) {
        return 1;
    }

    auto const input = (args->input == qrd::Args::Input::File)
                         ? qrd::read_input (__FILE__)
                         : test_input;

    return ((args->part == qrd::Args::Part::One) ? part_one : part_two) (input);
}
