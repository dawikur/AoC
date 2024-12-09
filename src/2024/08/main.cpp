// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"............",
	"........0...",
	".....0......",
	".......0....",
	"....0.......",
	"......A.....",
	"............",
	"............",
	"........A...",
	".........A..",
	"............",
	"............",
};

// ////////////////////////////////////////////////////////////////////////////

void cursor_left(qrd::Point<int>& cursor, int n = 1)
{
	std::cout << qrd::term_left(n);
	cursor.x -= n;
}

void cursor_right(qrd::Point<int>& cursor, int n = 1)
{
	std::cout << qrd::term_right(n);
	cursor.x += n;
}

void cursor_up(qrd::Point<int>& cursor, int n = 1)
{
	std::cout << qrd::term_up(n);
	cursor.y -= n;
}

void cursor_down(qrd::Point<int>& cursor, int n = 1)
{
	std::cout << qrd::term_down(n);
	cursor.y += n;
}

void move_to(qrd::Point<int>& cursor, qrd::Point<int> const& target)
{
	if (cursor.x < target.x) {
		cursor_right(cursor, target.x - cursor.x);
	} else if (cursor.x > target.x) {
		cursor_left(cursor, cursor.x - target.x);
	}

	if (cursor.y < target.y) {
		cursor_down(cursor, target.y - cursor.y);
	} else if (cursor.y > target.y) {
		cursor_up(cursor, cursor.y - target.y);
	}
}

void antinodes (auto& input, auto points)
{
	if (points.empty()) {
		return;
	}

	auto first = *points.begin();
	points.erase(points.begin());

	for (auto point: points) {
		auto diff = first - point;

		auto p = first;
		while (true) {
			if (p.x < static_cast<int>(input[0].size()) &&
				p.y < static_cast<int>(input.size()) &&
				0 <= p.x && 0 <= p.y) {
				input [static_cast<std::size_t> (p.y)]
					  [static_cast<std::size_t> (p.x)]
					= '#';
			} else {
				break;
			}

			p += diff;
		};

		p = first;
		while (true) {
			if (p.x < static_cast<int>(input[0].size()) &&
				p.y < static_cast<int>(input.size()) &&
				0 <= p.x && 0 <= p.y) {
				input [static_cast<std::size_t> (p.y)]
					  [static_cast<std::size_t> (p.x)]
					= '#';
			} else {
				break;
			}

			p -= diff;
		};

	}

	antinodes(input, points);
}

void part_one (qrd::Input& input)
{
	std::unordered_map<char, std::unordered_set<qrd::Point<int>>>
		antenas;

	for (std::size_t i = 0; i < input.size(); ++i) {
		for (std::size_t j = 0; j < input[i].size(); ++j) {
			if (input[i][j] != '.') {
				antenas[input[i][j]].insert({static_cast<int>(j), static_cast<int>(i)});
			}
		}
	}

	for (auto [freq, points]: antenas) {
		antinodes(input, points);
	}

	int count{};
    for (auto const& line: input) {
		for (auto const& c: line) {
			if (c == '#') {
				++count;
			}
			std::cout << qrd::term(qrd::RGB::from_1D(c / 127.f));
			std::cout << c;
		}
		std::cout << std::endl;
	}
	std::cout << qrd::term() << std::endl;


	std::cout << count << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

void part_two (qrd::Input & input)
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
                         : test_input;

    ((args->part == qrd::Args::Part::One) ? part_one : part_two) (input);

    return 0;
}
