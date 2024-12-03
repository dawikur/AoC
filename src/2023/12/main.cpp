// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

qrd::Input test_input1 {
	"#.#.### 1,1,3",
	".#...#....###. 1,1,3",
	".#.###.#.###### 1,3,1,6",
	"####.#...#... 4,1,1",
	"#....######..#####. 1,6,5",
	".###.##....# 3,2,1",
};

qrd::Input test_input2 {
	"???.### 1,1,3",
	".??..??...?##. 1,1,3",
	"?#?#?#?#?#?#?#? 1,3,1,6",
	"????.#...#... 4,1,1",
	"????.######..#####. 1,6,5",
	"?###???????? 3,2,1",
};

int try_match (std::string_view const line, std::vector<int> const& summary)
{
	if (summary.empty ()) { return 0; }

	int result = line.empty () ? 1 : 0;

	return result;
}

std::string unfold (std::string const& line)
{
	std::string result;
	result.reserve (5 * line.size () + 4);
	result = line;

	for (std::size_t i = 0U; i < 4U; ++i) {
		result += "?";
		result += line;
	}

	return result;
}

std::vector<int> unfold (std::vector<int> const& summary)
{
	return summary * 5;
}

int main ()
{
	auto input = qrd::read_input (__FILE__);
	// auto input = test_input2;

	int total = 0;
	for (auto& line: input) {
		auto const split = qrd::split (line, ' ');

		auto map     = std::string (split [0]);
		auto summary = qrd::split_as<int> (split [1], ',');
		summary      = {summary.rbegin (), summary.rend ()};

		// map = unfold(map);
		// summary = unfold(summary);

		map = '.' + map + '.';

		std::cout << map << ":" << std::endl;
		std::cout << "\t" << summary << std::endl;

		auto const matches = try_match (map, summary);
		std::cout << "\t[" << matches << "]" << std::endl;

		total += matches;
	}

	std::cout << "Total: " << total << std::endl;

	return 0;
}
