// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"5 10 25",
};

// ////////////////////////////////////////////////////////////////////////////

bool is_valid(int a, int b, int c) {
	return (a + b > c) && (a + c > b) && (b + c > a);
}

int part_one (qrd::Input const& input)
{
	int count{};

	for (auto const& line : input) {
		auto const sides = qrd::split_as<int> (line, ' ');

		if (is_valid(sides[0], sides[1], sides[2])) {
			++count;
		}
	}

	std::cout << count << std::endl;

    return 0;
}

// ////////////////////////////////////////////////////////////////////////////

int part_two (qrd::Input const& input)
{
	int count{};

	for (std::size_t i{}; i < input.size(); i += 3) {
		auto const a = qrd::split_as<int> (input[i], ' ');
		auto const b = qrd::split_as<int> (input[i + 1], ' ');
		auto const c = qrd::split_as<int> (input[i + 2], ' ');

		if (is_valid(a[0], b[0], c[0])) {
			++count;
		}
		if (is_valid(a[1], b[1], c[1])) {
			++count;
		}
		if (is_valid(a[2], b[2], c[2])) {
			++count;
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
                         ? qrd::read_input (__FILE__)
                         : test_input;

    return ((args->part == qrd::Args::Part::One) ? part_one : part_two) (input);
}
