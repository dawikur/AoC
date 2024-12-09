// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input {
	"3   4",
	"4   3",
	"2   5",
	"1   3",
	"3   9",
	"3   3",
};

// ////////////////////////////////////////////////////////////////////////////

int part_one (qrd::Input const& input)
{
	std::vector<int> numbers[2];
	numbers[0].reserve(input.size());
	numbers[1].reserve(input.size());

	for (auto const& line: input) {
		auto const tokens = qrd::split_as<int> (line, ' ', false);

		numbers[0].push_back(tokens[0]);
		numbers[1].push_back(tokens[1]);
	}

	std::sort(numbers[0].begin(), numbers[0].end());
	std::sort(numbers[1].begin(), numbers[1].end());

	int sum{0};
	for (std::size_t i{0}; i < numbers[0].size(); ++i) {
		auto const diff = numbers[0][i] - numbers[1][i];

		if (diff < 0) {
			sum -= diff;
		} else {
			sum += diff;
		}
	}

	std::cout << sum << std::endl;

	return 0;
}

// ////////////////////////////////////////////////////////////////////////////

int part_two (qrd::Input const& input)
{
	std::unordered_map<int, int> numbers[2];

	for (auto const& line: input) {
		auto const tokens = qrd::split_as<int> (line, ' ', false);

		for (auto const idx: {0U, 1U}) {
			if (numbers[idx].contains(tokens[idx])) {
				++numbers[idx][tokens[idx]];
			} else {
				numbers[idx][tokens[idx]] = 1;
			}
		}
	}

	int similarity{};
	for (auto const& lhs: numbers[0]) {
		if (numbers[1].contains(lhs.first)) {
			auto const sim = lhs.first * lhs.second * numbers[1][lhs.first];

			if (sim < 0) {
				similarity -= sim;
			} else {
				similarity += sim;
			}
		}
	}

	std::cout << similarity << std::endl;

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
