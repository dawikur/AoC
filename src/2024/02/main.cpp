// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"7 6 4 2 1",
	"1 2 7 8 9",
	"9 7 6 2 1",
	"1 3 2 4 5",
	"8 6 4 4 1",
	"1 3 6 7 9",
};

struct Analysis {
	bool is_safe;
	std::size_t idx{};
};

Analysis analyse(std::vector<int> const& levels) {
	bool const is_increasing {levels [0] < levels [1]};

	for (std::size_t idx{1}; idx < levels.size(); ++idx) {
		auto const lhs = levels[idx-1];
		auto const rhs = levels[idx];

		if (is_increasing) {
			if (lhs > rhs) {
				std::cout << "    [" << idx << "] " << lhs << " > " << rhs << std::endl;
				return {false, idx};
			}
		} else {
			if (lhs < rhs) {
				std::cout << "    [" << idx << "] " << lhs << " < " << rhs << std::endl;
				return {false, idx};
			}
		}

		auto const diff = lhs - rhs;
		auto const abs = std::abs(diff);
		if (abs < 1 || 3 < abs) {
			std::cout << "    [" << idx << "] " << abs << " is not in (1, 3)" << std::endl;
			return {false, idx};
		}
	}

	return {true};
}

// ////////////////////////////////////////////////////////////////////////////

int part_one (qrd::Input const& input)
{
	int num_of_safe_reports{0};
	for (auto const& line: input) {
		auto const levels = qrd::split_as<int>(line, ' ');

		if (analyse(levels).is_safe) {
			++num_of_safe_reports;
		}
	}

	std::cout << num_of_safe_reports << std::endl;

    return 0;
}

// ////////////////////////////////////////////////////////////////////////////

int part_two (qrd::Input const& input)
{
	int num_of_safe_reports{0};
	for (auto const& line: input) {
		auto const levels = qrd::split_as<int>(line, ' ');
		std::cout << levels << std::endl;

		Analysis analysis{};

		if (analysis = analyse (levels);
			analysis.is_safe) {
			std::cout << "    SAFE" << std::endl;
			++num_of_safe_reports;
			continue;
		}

		for (std::size_t idx: {0UL, analysis.idx-1, analysis.idx}) {
			auto levels_cpy = levels;
			levels_cpy.erase(levels_cpy.begin() + static_cast<int>(idx));
			std::cout << "    " << levels_cpy << std::endl;
			if (auto const analysis_cpy = analyse (levels_cpy);
				analysis_cpy.is_safe) {
				std::cout << "    SAFE" << std::endl;
				++num_of_safe_reports;
				break;
			}
		}
	}

	std::cout << num_of_safe_reports << std::endl;

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
