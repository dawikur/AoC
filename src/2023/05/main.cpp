// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

std::vector<std::string> const test_input = {
	"seeds: 79 14 55 13",
	"",
	"seed-to-soil map:",
	"50 98 2",
	"52 50 48",
	"",
	"soil-to-fertilizer map:",
	"0 15 37",
	"37 52 2",
	"39 0 15",
	"",
	"fertilizer-to-water map:",
	"49 53 8",
	"0 11 42",
	"42 0 7",
	"57 7 4",
	"",
	"water-to-light map:",
	"88 18 7",
	"18 25 70",
	"",
	"light-to-temperature map:",
	"45 77 23",
	"81 45 19",
	"68 64 13",
	"",
	"temperature-to-humidity map:",
	"0 69 1",
	"1 0 69",
	"",
	"humidity-to-location map:",
	"60 56 37",
	"56 93 4",
};

enum class State
{
	Seeds,
	Header,
	Mapping,
};

struct Range
{
	long long begin {};
	long long end {};
};

struct Mapping
{
	long long begin;
	long long end;
	long long offset {};

	bool operator() (long long& value) const
	{
		if (begin <= value && value < end) {
			value += offset;
			return true;
		}
		return false;
	}
};

struct Step
{
	std::string_view     name;
	std::vector<Mapping> mappings {};
};

int main ()
{
	auto const input = qrd::read_file (__FILE__);
	// auto const input = test_input;

	State              state {State::Seeds};
	std::vector<Range> ranges {};

	std::vector<Step> steps {};

	for (auto const& line: input) {
		if (line.empty ()) {
			state = State::Header;
			continue;
		}

		auto const tokens = qrd::split (line, ' ');

		switch (state) {
			case State::Seeds: {
				for (std::size_t i {1}; i < tokens.size (); i += 2) {
					auto const begin = std::stoll (std::string (tokens [i]));
					auto const len = std::stoll (std::string (tokens [i + 1]));

					ranges.emplace_back (Range {
						.begin = begin,
						.end   = begin + len,
					});
				}
			} break;

			case State::Header: {
				steps.emplace_back (tokens [0]);
				state = State::Mapping;
			} break;

			case State::Mapping: {
				auto const dest_start   = std::stoll (std::string (tokens [0]));
				auto const source_start = std::stoll (std::string (tokens [1]));
				auto const range_len    = std::stoll (std::string (tokens [2]));

				steps.back ().mappings.emplace_back (Mapping {
					.begin  = source_start,
					.end    = source_start + range_len,
					.offset = dest_start - source_start,
				});

			} break;
		}
	}

	auto min = std::numeric_limits<long long>::max ();

	for (auto const& range: ranges) {
		std::cout << range.begin << " " << range.end << std::endl;
		for (long long seed {range.begin}; seed < range.end; ++seed) {
			auto value = seed;

			for (auto const& step: steps) {
				for (auto const& mapping: step.mappings) {
					if (mapping (value)) { break; }
				}
			}

			min = std::min (min, value);
		}
	}

	std::cout << min << std::endl;

	return 0;
}
