// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input_one {
	//"...0...",
	//"...1...",
	//"...2...",
	//"6543456",
	//"7.....7",
	//"8.....8",
	//"9.....9"

	//"..90..9",
	//"...1.98",
	//"...2..7",
	//"6543456",
	//"765.987",
	//"876....",
	//"987....",

	//"10..9..",
	//"2...8..",
	//"3...7..",
	//"4567654",
	//"...8..3",
	//"...9..2",
	//".....01",

	"89010123",
	"78121874",
	"87430965",
	"96549874",
	"45678903",
	"32019012",
	"01329801",
	"10456732",
};

qrd::Input test_input_two = test_input_one;

// ////////////////////////////////////////////////////////////////////////////

void print (qrd::Input const& input) {
	for (auto const& line: input) {
		for (auto const c: line) {
			if (c != '.') {
				auto ratio = (c-'0') / 9.F;
				std::cout << qrd::term(qrd::RGB::from_1D(ratio));
			}
			std::cout << c;
			std::cout << qrd::term();
		}
		std::cout << "\n";
	}
}

std::vector<qrd::Point<int>> find(qrd::Input const& input, char const c)
{
	std::vector<qrd::Point<int>> result;

	for (std::size_t y = 0; y < input.size(); ++y) {
		for (std::size_t x = 0; x < input[y].size(); ++x) {
			if (input[y][x] == c) {
				result.emplace_back(x, y);
			}
		}
	}

	return result;
}

using Trail = std::unordered_set<qrd::Point<int>>;
using Trails = std::unordered_set<Trail>;

Trails hike(qrd::Input const& input, qrd::Point<int> pos)
{
	auto const height = pos.get_from(input);

	if (height == '9') {
		return {{pos}};
	}

	Trails trails_from_pos;

	for (auto dp: qrd::Point<int>::cardinals()) {
		auto const next_pos = pos + dp;

		if (next_pos.is_in(input) && next_pos.get_from(input) == height + 1) {
			for (auto const& trail_from_next: hike(input, next_pos)) {
				Trail trail_from_pos;
				trail_from_pos.insert(pos);
				trail_from_pos.insert(trail_from_next.begin(), trail_from_next.end());

				trails_from_pos.insert(std::move(trail_from_pos));
			}
		}
	}

	return trails_from_pos;
}

void part_one (qrd::Input const& input)
{
	print (input);

	std::size_t score{};
	for (auto pos: find(input, '0')) {
		auto result = hike(input, pos);
		score += result.size();
	}

	std::cout << score << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

void part_two (qrd::Input const& input)
{
	(void)input;
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
