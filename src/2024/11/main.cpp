// Copyright (c) 2024 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

// ////////////////////////////////////////////////////////////////////////////

qrd::Input test_input_one {
	"0 1 10 99 999",
};

qrd::Input test_input_two = test_input_one;

// ////////////////////////////////////////////////////////////////////////////

using Cache = std::unordered_map<std::size_t,
								 std::unordered_map<std::size_t, std::size_t>>;

std::size_t expand (Cache& cache, std::size_t stone, std::size_t steps_left)
{
	if (!cache.contains(stone) || !cache[stone].contains(steps_left)) {
		cache[stone][steps_left] = [&] {
			if (steps_left == 0) {
				return 1UL;
			}
			if (stone == 0) {
				return expand (cache, 1, steps_left - 1);
			}
			if (auto const stone_str = std::to_string(stone);
					stone_str.size() % 2 == 0) {
				auto const size_2 = stone_str.size() / 2;
				auto const lhs = std::stoull (stone_str.substr (0, size_2));
				auto const rhs = std::stoull (stone_str.substr (size_2));

				return expand (cache, lhs, steps_left - 1)
					   + expand (cache, rhs, steps_left - 1);
			}
			return expand (cache, stone * 2024, steps_left - 1);
		}();
	}

	return cache[stone][steps_left];
}

void part_one (qrd::Input const& input)
{
	Cache cache{};

	auto const stones = qrd::split_as<std::size_t>(input[0]);
	std::size_t result{};
	for (auto const stone: stones) {
		result += expand(cache, stone, 25U);
	}

	std::cout << result << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

void part_two (qrd::Input const& input)
{
	Cache cache{};

	auto const stones = qrd::split_as<std::size_t>(input[0]);
	std::size_t result{};
	for (auto const stone: stones) {
		result += expand(cache, stone, 75U);
	}

	std::cout << result << std::endl;
}

// ////////////////////////////////////////////////////////////////////////////

int main (int const argc, char const* const argv[])
{
    auto const args = qrd::parse_args (argc, argv);

    if (!args) {
        return 1;
    }

    auto input = (args->input == qrd::Args::Input::File)
                   ? qrd::read_file (__FILE__)
                   : ((args->part == qrd::Args::Part::One) ? test_input_one
                                                           : test_input_two);

    if (args->part == qrd::Args::Part::One){
        part_one(input);
    } else {
        part_two(input);
    }

    return 0;
}
