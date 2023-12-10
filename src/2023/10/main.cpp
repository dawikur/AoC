// Copyright (c) 2023 Dawid Kurek <dawiku

#include <dku/file.hpp>
#include <dku/point.hpp>
#include <dku/rgb.hpp>
#include <dku/std.hpp>
#include <dku/string.hpp>

using Map = std::vector<std::string>;
using Pos = dku::Point<std::size_t>;

Map test_input {
	".F----7F7F7F7F-7....",
	".|F--7||||||||FJ....",
	".||.FJ||||||||L7....",
	"FJL7L7LJLJ||LJ.L-7..",
	"L--J.L7...LJS7F-7L7.",
	"....F-J..F7FJ|L7L7L7",
	"....L7.F7||L7|.L7L7|",
	".....|FJLJ|FJ|F7|.LJ",
	"....FJL-7.||.||||...",
	"....L---J.LJ.LJLJ...",
};

Map test_input2 {
	"FF7FSF7F7F7F7F7F---7",
	"L|LJ||||||||||||F--J",
	"FL-7LJLJ||||||LJL-77",
	"F--JF--7||LJLJ7F7FJ-",
	"L---JF-JLJ.||-FJLJJ7",
	"|F|F-JF---7F7-L7L|7|",
	"|FFJF7L7F-JF7|JL---7",
	"7-L-JL7||F7|L7F-7F7|",
	"L.L7LFJ|||||FJL7||LJ",
	"L7JLJL-JLJLJL--JLJ.L",
};

enum class Dir
{
	Any,
	Up,
	Down,
	Left,
	Right,
};

std::ostream& operator<< (std::ostream& os, Dir const& dir)
{
	switch (dir) {
		case Dir::Any: return os << "Any";
		case Dir::Up: return os << "Up";
		case Dir::Down: return os << "Down";
		case Dir::Left: return os << "Left";
		case Dir::Right: return os << "Right";
	}

	return os << "Unknown";
}

void flood (Map& map, Pos const& pos, std::size_t* inside)
{
	if (inside) {
		if (map [pos.y][pos.x] == '.') {
			map [pos.y][pos.x] = ',';
			++*inside;

			flood (map, {pos.x + 1, pos.y}, inside);
			flood (map, {pos.x - 1, pos.y}, inside);
			flood (map, {pos.x, pos.y + 1}, inside);
			flood (map, {pos.x, pos.y - 1}, inside);
		}
	}
}

void update (Map& map, Pos& pos, Dir& dir, std::size_t* inside)
{
	switch (dir) {
		case Dir::Any: assert (false);
		case Dir::Up:
			--pos.y;
			switch (map [pos.y][pos.x]) {
				case '|': flood (map, {pos.x - 1, pos.y}, inside); break;
				case 'F':
					dir = Dir::Right;
					flood (map, {pos.x - 1, pos.y}, inside);
					flood (map, {pos.x, pos.y - 1}, inside);
					break;
				case '7': dir = Dir::Left; break;
				case 'S': dir = Dir::Down; break;
				default: assert (false);
			}
			break;
		case Dir::Down:
			++pos.y;
			switch (map [pos.y][pos.x]) {
				case '|': flood (map, {pos.x + 1, pos.y}, inside); break;
				case 'L': dir = Dir::Right; break;
				case 'J':
					dir = Dir::Left;
					flood (map, {pos.x + 1, pos.y}, inside);
					flood (map, {pos.x, pos.y + 1}, inside);
					break;
				case 'S': dir = Dir::Up; break;
				default: assert (false);
			}
			break;
		case Dir::Left:
			--pos.x;
			switch (map [pos.y][pos.x]) {
				case '-': flood (map, {pos.x, pos.y + 1}, inside); break;
				case 'L':
					dir = Dir::Up;
					flood (map, {pos.x - 1, pos.y}, inside);
					flood (map, {pos.x, pos.y + 1}, inside);
					break;
				case 'F': dir = Dir::Down; break;
				case 'S': dir = Dir::Right; break;
				default: assert (false);
			}
			break;
		case Dir::Right:
			++pos.x;
			switch (map [pos.y][pos.x]) {
				case '-': flood (map, {pos.x, pos.y - 1}, inside); break;
				case 'J': dir = Dir::Up; break;
				case '7':
					dir = Dir::Down;
					flood (map, {pos.x + 1, pos.y}, inside);
					flood (map, {pos.x, pos.y - 1}, inside);
					break;
				case 'S': dir = Dir::Left; break;
				default: assert (false);
			}
			break;
	}
}

void pretty_print (std::vector<std::string> const&              map,
				   std::vector<std::vector<std::size_t>> const& distances,
				   std::size_t const                            max_distance,
				   bool                                         raw = false)
{
	for (std::size_t i = 0; i < map.size (); ++i) {
		for (std::size_t j = 0; j < map [i].size (); ++j) {
			auto const c = map [i][j];
			auto       d = distances [i][j];

			if (d == std::numeric_limits<std::size_t>::max ()) {
			} else if (d == 0U) {
				std::cout << "\033[38;2;255;255;255m";
			} else {
				if (d > max_distance) { d = 2 * max_distance - d; }

				auto const f = static_cast<float> (d)
							 / static_cast<float> (max_distance);

				auto const rgb = dku::RGB::from_1D (f);

				std::size_t const R = static_cast<std::size_t> (255 * rgb.r);
				std::size_t const G = static_cast<std::size_t> (255 * rgb.g);
				std::size_t const B = static_cast<std::size_t> (255 * rgb.b);
				std::cout << "\033[38;2;" << R << ";" << G << ";" << B << "m";

				if (d == max_distance) { std::cout << "\033[5m"; }
			}

			if (raw) {
				std::cout << c;
			} else {
				switch (c) {
					case '|': std::cout << "│"; break;
					case '-': std::cout << "─"; break;
					case 'L': std::cout << "╰"; break;
					case 'J': std::cout << "╯"; break;
					case '7': std::cout << "╮"; break;
					case 'F': std::cout << "╭"; break;
					case '.': std::cout << " "; break;
					case ',': std::cout << "⣿"; break;
					case 'S': std::cout << "\033[5m▒"; break;
				}
			}

			std::cout << "\033[m";
		}
		std::cout << std::endl;
	}
}

int main ()
{
	auto map = dku::read_input (__FILE__);
	// auto map = test_input;

	for (auto& line: map) {
		line.insert (line.begin (), '.');
		line.insert (line.end (), '.');
	}
	map.insert (map.begin (), std::string (map [0].size (), '.'));
	map.insert (map.end (), std::string (map [0].size (), '.'));

	std::vector<std::vector<std::size_t>> distances {
		map.size (),
		std::vector<std::size_t> (map [0].size (),
								  std::numeric_limits<std::size_t>::max ())};

	dku::Point<std::size_t> start {};
	for (std::size_t i = 0; i < map.size (); ++i) {
		for (std::size_t j = 0; j < map [i].size (); ++j) {
			if (map [i][j] == 'S') {
				start = {j, i};
				break;
			}
		}
	}

	auto pos = start;
	auto dir = [&] () {
		if (map [pos.y][pos.x + 1] == '-') return Dir::Right;
		if (map [pos.y][pos.x + 1] == 'J') return Dir::Right; // ┘
		if (map [pos.y][pos.x + 1] == '7') return Dir::Right; // ┐

		if (map [pos.y + 1][pos.x] == '|') return Dir::Down;
		if (map [pos.y + 1][pos.x] == 'L') return Dir::Down; // ┐
		if (map [pos.y + 1][pos.x] == 'J') return Dir::Down; // ┌

		if (map [pos.y][pos.x - 1] == '-') return Dir::Left;
		if (map [pos.y][pos.x - 1] == 'L') return Dir::Left; // └
		if (map [pos.y][pos.x - 1] == 'F') return Dir::Left; // ┌

		if (map [pos.y - 1][pos.x] == '|') return Dir::Up;
		if (map [pos.y - 1][pos.x] == '7') return Dir::Up; // └
		if (map [pos.y - 1][pos.x] == 'F') return Dir::Up; // ┘

		assert (false);
	}();

	std::size_t pipe_length = 0;
	do {
		distances [pos.y][pos.x] = pipe_length;

		update (map, pos, dir, nullptr);

		++pipe_length;
	} while (pos != start);

	for (std::size_t i = 0; i < map.size (); ++i) {
		for (std::size_t j = 0; j < map [i].size (); ++j) {
			if (distances [i][j] == std::numeric_limits<std::size_t>::max ()) {
				map [i][j] = '.';
			}
		}
	}

	dir = [&] () {
		if (map [pos.y][pos.x + 1] == '-') return Dir::Right;
		if (map [pos.y][pos.x + 1] == 'J') return Dir::Right; // ┘
		if (map [pos.y][pos.x + 1] == '7') return Dir::Right; // ┐

		if (map [pos.y + 1][pos.x] == '|') return Dir::Down;
		if (map [pos.y + 1][pos.x] == 'L') return Dir::Down; // ┐
		if (map [pos.y + 1][pos.x] == 'J') return Dir::Down; // ┌

		if (map [pos.y][pos.x - 1] == '-') return Dir::Left;
		if (map [pos.y][pos.x - 1] == 'L') return Dir::Left; // └
		if (map [pos.y][pos.x - 1] == 'F') return Dir::Left; // ┌

		if (map [pos.y - 1][pos.x] == '|') return Dir::Up;
		if (map [pos.y - 1][pos.x] == '7') return Dir::Up; // └
		if (map [pos.y - 1][pos.x] == 'F') return Dir::Up; // ┘

		assert (false);
	}();
	std::size_t inside = 0;
	do {
		update (map, pos, dir, &inside);
	} while (pos != start);

	auto const max_distance = (pipe_length + 1) / 2;
	pretty_print (map, distances, max_distance);

	std::cout << "Pipe length: " << pipe_length << std::endl;
	std::cout << "Max distance: " << max_distance << std::endl;
	std::cout << "Inside: " << inside << std::endl;

	return 0;
}
