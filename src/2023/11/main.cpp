// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <dku.hpp>

dku::Input test_input {
	"...#......",
	".......#..",
	"#.........",
	"..........",
	"......#...",
	".#........",
	".........#",
	"..........",
	".......#..",
	"#...#.....",
};

dku::Point<std::vector<std::size_t>> distance (dku::Input const& lines)
{
	dku::Point<std::vector<std::size_t>>
		result {std::vector<std::size_t> (lines.size (), 1U),
				std::vector<std::size_t> (lines [0].size (), 1U)};

	for (std::size_t i = 0; i < lines.size (); ++i) {
		bool is_empty = true;

		for (std::size_t j = 0; j < lines [i].size (); ++j) {
			if (lines [i][j] == '#') {
				is_empty = false;
				break;
			}
		}

		if (is_empty) { result.x [i] *= 1000000; }
	}

	for (std::size_t j = 0; j < lines [0].size (); ++j) {
		bool is_empty = true;

		for (std::size_t i = 0; i < lines.size (); ++i) {
			if (lines [i][j] == '#') {
				is_empty = false;
				break;
			}
		}

		if (is_empty) { result.y [j] *= 1000000; }
	}

	return result;
}

dku::Points<std::size_t> gather (std::vector<std::string> const& lines)
{
	dku::Points<std::size_t> result {};

	for (std::size_t i = 0; i < lines.size (); ++i) {
		for (std::size_t j = 0; j < lines [i].size (); ++j) {
			if (lines [i][j] == '#') { result.push_back ({i, j}); }
		}
	}

	return result;
}

int main ()
{
	auto const input = dku::read_input (__FILE__);
	// auto const input = test_input;

	auto distances = distance (input);
	auto galaxes   = gather (input);

	std::size_t total = 0;
	for (std::size_t i = 0; i < galaxes.size () - 1; ++i) {
		for (std::size_t j = i + 1; j < galaxes.size (); ++j) {
			auto const& gi = galaxes [i];
			auto const& gj = galaxes [j];

			auto const x_min = std::min (gi.x, gj.x);
			auto const x_max = std::max (gi.x, gj.x);
			auto const y_min = std::min (gi.y, gj.y);
			auto const y_max = std::max (gi.y, gj.y);

			std::size_t dist = 0U;

			for (auto x = x_min; x < x_max; ++x) { dist += distances.x [x]; }

			for (auto y = y_min; y < y_max; ++y) { dist += distances.y [y]; }

			// std::cout << i << ":" << j << " -> " << dist << std::endl;
			total += dist;
		}
	}

	std::cout << "Total distance: " << total << std::endl;

	return 0;
}
