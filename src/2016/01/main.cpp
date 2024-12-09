// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	" R8, R4, R4, R8",
};

// ////////////////////////////////////////////////////////////////////////////

int part_one (qrd::Input const& input)
{
	qrd::Points<int> const units {
		{0, 1}, // N
		{1, 0}, // E
		{0, -1}, // S
		{-1, 0}, // W
	};

    for (auto const& line : input) {
		qrd::Point<int> pos {};
		std::size_t dir{};

		for (auto const& cmd: qrd::split (line, ',')) {
			auto const turn = cmd[1];
			auto const dist = std::stoi (std::string {cmd.substr (2)});

			switch (turn) {
				case 'R': dir = (dir + 1) % 4; break;
				case 'L': dir = (dir + 3) % 4; break;
			}

			pos += units[dir] * dist;
		}

		std::cout << pos << std::endl;

		std::cout << "Distance: " << qrd::manhattan_distance({}, pos) << std::endl;
	}

    return 0;
}

// ////////////////////////////////////////////////////////////////////////////

int part_two (qrd::Input const& input)
{
	qrd::Points<int> const units {
		{0, 1}, // N
		{1, 0}, // E
		{0, -1}, // S
		{-1, 0}, // W
	};

    for (auto const& line : input) {
		std::unordered_set<qrd::Point<int>> visited {};
		visited.emplace ();

		qrd::Point<int> pos {};
		std::size_t dir{};

		for (auto const& cmd: qrd::split (line, ',')) {
			auto const turn = cmd[1];
			auto const dist = std::stoi (std::string {cmd.substr (2)});

			switch (turn) {
				case 'R': dir = (dir + 1) % 4; break;
				case 'L': dir = (dir + 3) % 4; break;
			}

			for (int i{}; i < dist; ++i) {
				pos += units[dir];

				if (visited.contains (pos)) {
					std::cout << pos << std::endl;
					std::cout << "Distance: " << qrd::manhattan_distance({}, pos) << std::endl;

					return 0;
				}
				visited.emplace (pos);
			}
		}

		std::cout << pos << std::endl;
		std::cout << "Distance: " << qrd::manhattan_distance({}, pos) << std::endl;
	}

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
