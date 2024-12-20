// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input_one {
	"RRRRIICCFF",
	"RRRRIICCCF",
	"VVRRRCCFFF",
	"VVRCCCJFFF",
	"VVVVCJJCFE",
	"VVIVCCJJEE",
	"VVIIICJJEE",
	"MIIIIIJJEE",
	"MIIISIJEEE",
	"MMMISSJEEE",
};

qrd::Input test_input_two = test_input_one;

// ////////////////////////////////////////////////////////////////////////////

struct Result {
	std::size_t area;
	std::size_t perimeter;
};

Result count (qrd::Input& garden, char ch, qrd::Point<int> p) {
	p.get_from(garden) = 0;

	Result result {1, 0};

	for (auto d_p: qrd::Point<int>::cardinals()) {
		auto n_p= p+ d_p;
		auto nn_p= n_p+ d_p;

		if (n_p.is_in(garden)) {
			auto n_ch = n_p.get_from(garden);

			if (nn_p.is_in(garden)) {
				auto nn_ch = nn_p.get_from(garden);

				if (n_ch == ' ') {
					if (nn_ch == ch) {
						auto next_result = count(garden, ch, nn_p);
						result.area += next_result.area;
						result.perimeter += next_result.perimeter;
					}
				} else {
					++result.perimeter;
				}
			} else {
				++result.perimeter;
			}
		}
	}

	return result;
}

void print (std::vector<std::string> const& input)
{
	std::cout << "┍";
	for (std::size_t i = 0; i < input[0].size(); ++i) {
		std::cout << "━";
	}
	std::cout << "┑" << std::endl;

	for (auto const& row: input) {
		std::cout << "│" << row << "│" << std::endl;
	}

	std::cout << "┕";
	for (std::size_t i = 0; i < input[0].size(); ++i) {
		std::cout << "━";
	}
	std::cout << "┙" << std::endl;
}

void part_one (qrd::Input const& input)
{
	std::vector<std::string> garden {};
	garden.reserve (input.size () * 2 + 1);

	// top
	garden.emplace_back("+");
	for (std::size_t i = 0; i < input[0].size (); ++i) {
		garden.back() += '-';
		garden.back() += '+';
	}

	// middle
	for (auto const & line : input) {
		garden.emplace_back ("|");

		for (auto c: line) {
			garden.back ().push_back (c);
			garden.back ().push_back (' ');
		}
		garden.back ().back () = '|';

		garden.emplace_back (std::string(input[0].size () * 2 + 1, ' '));
		garden.back().front() = '+';
		garden.back().back() = '+';
	}

	// bottom
	garden.back() = "+";
	for (std::size_t i = 0; i < input[0].size (); ++i) {
		garden.back() += '-';
		garden.back() += '+';
	}

	for (std::size_t y{1}; y < garden.size(); y+=2) {
		for (std::size_t x{1}; x < garden[y].size(); x+=2) {
			if (x > 1) {
				if (garden[y][x] != garden[y][x-2]) {
					garden[y][x-1] = '|';
				}
			}

			if (y > 1) {
				if (garden[y][x] != garden[y-2][x]) {
					garden[y-1][x] = '-';
				}
			}
		}
	}

	for (std::size_t y{0}; y < garden.size()-1; ++y) {
		for (std::size_t x{0}; x < garden[y].size()-1; ++x) {
			if (garden[y][x] == '|') {
				garden[y+1][x] = '+';
			}

			if (garden[y][x] == '-') {
				garden[y][x+1] = '+';
			}
		}
	}

	print(garden);

	std::size_t price{};

	for (std::size_t y{1}; y < garden.size(); y+=2) {
		for (std::size_t x{1}; x < garden[y].size(); x+=2) {
			if (garden[y][x] == 0) {
				continue;
			}

			auto result
				= count (garden, garden [y][x], qrd::Point {x, y}.as<int> ());
			std::cout << input [y / 2][x / 2] << " - Area: " << result.area
					  << " Perimeter: " << result.perimeter << std::endl;

			price += result.area * result.perimeter;
		}
	}

	std::cout << "Price: " << price << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

void part_two (qrd::Input const& input)
{
    (void) input;
}

// ////////////////////////////////////////////////////////////////////////////

int main (int const argc, char const* const argv[])
{
    auto const args = qrd::parse_args (argc, argv);

    if (!args) {
        return 1;
    }

    auto input = (args->input == qrd::Args::Input::File)
                   ? qrd::read_file (__FILE__)
                   : ((args->part == qrd::Args::Part::One) ? test_input_one
                                                           : test_input_two);

    if (args->part == qrd::Args::Part::One){
        part_one(input);
    } else {
        part_two(input);
    }

    return 0;
}
