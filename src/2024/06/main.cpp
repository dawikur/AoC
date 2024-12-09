// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"....#.....",
	".........#",
	"..........",
	"..#.......",
	".......#..",
	"..........",
	".#..^.....",
	"........#.",
	"#.........",
	"......#...",
};

constexpr int const FREE    = 0;
constexpr int const LEFT    = (1 << 1);
constexpr int const RIGHT   = (1 << 2);
constexpr int const UP      = (1 << 3);
constexpr int const DOWN    = (1 << 4);
constexpr int const OBSTACLE = (1 << 8);
constexpr int const BLOCKED = (1 << 9);

qrd::Point<int> find_start(qrd::Input const& input) {
	for (std::size_t y = 0; y < input.size(); ++y) {
		for (std::size_t x = 0; x < input[y].size(); ++x) {
			if (input[y][x] == '^') {
				return {static_cast<int> (x), static_cast<int> (y)};
			}
		}
	}

	assert (false);
	return {0, 0};
}

int rotate(int direction) {
	switch (direction) {
		case UP: return RIGHT;
		case RIGHT: return DOWN;
		case DOWN: return LEFT;
		case LEFT: return UP;
		default: assert (false); return direction;
	}
}

qrd::Point<int> move(qrd::Point<int> const& p, int direction) {
	switch (direction) {
		case UP: return {p.x, p.y - 1};
		case DOWN: return {p.x, p.y + 1};
		case LEFT: return {p.x - 1, p.y};
		case RIGHT: return {p.x + 1, p.y};
		default: assert (false); return p;
	}
}

bool is_out_of_bounds(std::vector<std::vector<int>> const& input, qrd::Point<int> const& p) {
	if (p.y < 0 || p.x < 0) return true;

	auto const y_size = static_cast<std::size_t> (p.y);
	auto const x_size = static_cast<std::size_t> (p.x);

	if (input.size () <= y_size || input [y_size].size () <= x_size) return true;

	return false;
}

bool is_free (std::vector<std::vector<int>> const& input, qrd::Point<int> const& p) {
	if (is_out_of_bounds(input, p)) return false;

	auto const y_size = static_cast<std::size_t> (p.y);
	auto const x_size = static_cast<std::size_t> (p.x);

	return input [y_size][x_size] != BLOCKED;
}

void print (std::vector<std::vector<int>> const& input) {
	std::cout << "┍";
	for (std::size_t i = 0; i < input[0].size(); ++i) {
		std::cout << "━";
	}
	std::cout << "┑" << std::endl;

	for (auto const& line: input) {
		std::cout << "│";
		for (auto const& ch: line) {
			switch (ch) {
				case UP:
					std::cout << qrd::term(qrd::Csi::Green) << qrd::term(qrd::Csi::Bold) << "↑";
					break;
				case DOWN:
					std::cout << qrd::term(qrd::Csi::Green) << qrd::term(qrd::Csi::Bold) << "↓";
					break;
				case LEFT:
					std::cout << qrd::term(qrd::Csi::Green) << qrd::term(qrd::Csi::Bold) << "←";
					break;
				case RIGHT:
					std::cout << qrd::term(qrd::Csi::Green) << qrd::term(qrd::Csi::Bold) << "→";
					break;

				case FREE:
					std::cout << ".";
					break;
				case OBSTACLE:
					std::cout << qrd::term(qrd::Csi::Magenta) << "O";
					break;
				case BLOCKED:
					std::cout << qrd::term(qrd::Csi::Red) << "#";
					break;

				default:
					if (ch & UP && ch & RIGHT && ch & DOWN && ch & LEFT) {
						std::cout << "┼";
					} else

					if (ch & UP && ch & RIGHT && ch & DOWN) {
						std::cout << "├";
					} else
					if (ch & UP && ch & RIGHT && ch & LEFT) {
						std::cout << "┴";
					} else
					if (ch & UP && ch & DOWN && ch & LEFT) {
						std::cout << "┤";
					} else
					if (ch & RIGHT && ch & DOWN && ch & LEFT) {
						std::cout << "┬";
					} else

					if (ch & UP && ch & RIGHT) {
						std::cout << "└";
					} else
					if (ch & UP && ch & DOWN) {
						std::cout << "│";
					} else
					if (ch & UP && ch & LEFT) {
						std::cout << "┘";
					} else

					if (ch & RIGHT && ch & DOWN) {
						std::cout << "┌";
					} else
					if (ch & RIGHT && ch & LEFT) {
						std::cout << "─";
					} else
					if (ch & DOWN && ch & LEFT) {
						std::cout << "┐";
					} else

					assert (false);
					break;
			}

			std::cout << qrd::term();
		}
		std::cout << "│" << std::endl;
	}

	std::cout << "└";
	for (std::size_t i = 0; i < input[0].size(); ++i) {
		std::cout << "─";
	}
	std::cout << "┘" << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

bool run (std::vector<std::vector<int>> input, qrd::Point<int> pos, int direction)
{
	while (!is_out_of_bounds (input, pos)) {
		auto const next_pos = move(pos, direction);

		if (is_out_of_bounds(input, next_pos)) {
			return false;
		} else if (input[static_cast<std::size_t>(next_pos.y)][static_cast<std::size_t>(next_pos.x)] & direction) {
			return true;
		} else if (is_free(input, next_pos)) {
			pos = next_pos;
			input[static_cast<std::size_t>(pos.y)][static_cast<std::size_t>(pos.x)] += direction;
		} else {
			direction = rotate(direction);
		}
	}

	return false;
}

void part_one (qrd::Input input)
{
	std::cout << input.size() << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

void part_two (qrd::Input input2)
{
	auto pos = find_start(input2);
	input2[static_cast<std::size_t>(pos.y)][static_cast<std::size_t>(pos.x)] = '.';

	std::vector<std::vector<int>> input;
	for (auto const& line2: input2) {
		std::vector<int> line;
		for (auto const& ch: line2) {
			if (ch == '.') {
				line.push_back(FREE);
			} else {
				line.push_back(BLOCKED);
			}
		}

		input.push_back(line);
	}

	auto direction = UP;

	input[static_cast<std::size_t>(pos.y)][static_cast<std::size_t>(pos.x)] = direction;

	int count{};
	for (auto& line: input) {
		for (auto& ch: line) {
			if (ch == FREE) {
				ch = BLOCKED;

				if (run(input, pos, direction)) {
					ch = OBSTACLE;
					++count;
				}

				ch = FREE;
			}
		}
	}

	std::cout << count << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

int main (int const argc, char const* const argv[])
{
    auto const args = qrd::parse_args (argc, argv);

    if (!args) {
        return 1;
    }

    auto const input = (args->input == qrd::Args::Input::File)
                         ? qrd::read_file (__FILE__)
                         : test_input;

    ((args->part == qrd::Args::Part::One) ? part_one : part_two) (input);

    return 0;
}
