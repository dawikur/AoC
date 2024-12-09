// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"MMMSXXMASM",
	"MSAMXMSMSA",
	"AMXSXMAAMM",
	"MSAMASMSMX",
	"XMASAMXAMM",
	"XXAMMXXAMA",
	"SMSMSASXSS",
	"SAXAMASAAA",
	"MAMMMXMMMM",
	"MXMXAXMASX",
};

// ////////////////////////////////////////////////////////////////////////////

bool search (qrd::Input const& input,
			 int       x,
			 int       y,
			 int       dx,
			 int       dy,
			 std::string_view  word)
{
	if (word.empty ()) return true;

	if (y < 0 || x < 0) return false;

	auto y_size = static_cast<std::size_t> (y);
	auto x_size = static_cast<std::size_t> (x);

	if (input.size () <= y_size || input [y_size].size () <= x_size) return false;

	if (input [y_size][x_size] != word [0]) return false;

	return search (input, x + dx, y + dy, dx, dy, word.substr (1));
}

int part_one (qrd::Input const& input)
{
	int count{};

    for (std::size_t y{}; y < input.size (); ++y) {
		for (std::size_t x{}; x < input[y].size (); ++x) {
			auto x_int = static_cast<int> (x);
			auto y_int = static_cast<int> (y);

			if (search (input, x_int, y_int, -1, 0, "XMAS")) ++count;
			if (search (input, x_int, y_int, 0, -1, "XMAS")) ++count;
			if (search (input, x_int, y_int, 0, 1, "XMAS")) ++count;
			if (search (input, x_int, y_int, 1, 0, "XMAS")) ++count;

			if (search (input, x_int, y_int, -1, -1, "XMAS")) ++count;
			if (search (input, x_int, y_int, -1, 1, "XMAS")) ++count;
			if (search (input, x_int, y_int, 1, -1, "XMAS")) ++count;
			if (search (input, x_int, y_int, 1, 1, "XMAS")) ++count;
		}
	}

	std::cout << count << std::endl;

    return 0;
}

// ////////////////////////////////////////////////////////////////////////////

int add (qrd::Input const& input, int const x, int const y, int const dy)
{
	return input[static_cast<std::size_t>(y)][static_cast<std::size_t>(x)]
		+ (input[static_cast<std::size_t>(y+dy)][static_cast<std::size_t>(x+1)] *2)
		+  input[static_cast<std::size_t>(y+dy*2)][static_cast<std::size_t>(x+2)];
}

int part_two (qrd::Input const& input)
{
	int count{};

	int const MAS = 'M' + ('A' * 2) + 'S';
	for (std::size_t y{0}; y < input.size ()-2; ++y) {
		auto y_int = static_cast<int> (y);
		for (std::size_t x{0}; x < input[y].size ()-2; ++x) {
			auto x_int = static_cast<int> (x);

			if (add (input, x_int, y_int, 1) == MAS
				&& add (input, x_int, y_int + 2, -1) == MAS) {
				++count;
			}
		}
	}

	std::cout << count << std::endl;

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
                         ? qrd::read_file (__FILE__)
                         : test_input;

    return ((args->part == qrd::Args::Part::One) ? part_one : part_two) (input);
}
