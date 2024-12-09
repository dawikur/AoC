// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

std::vector<std::string> const test_input {
	"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53",
	"Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19",
	"Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1",
	"Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83",
	"Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36",
	"Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11",
};

std::size_t check_card (std::string const& card)
{
	std::stringstream ss (card);

	std::string token;
	ss >> token >> token;

	std::unordered_set<int> numbers;

	while (ss >> token) {
		if (token == "|") { break; }

		numbers.insert (std::stoi (token));
	}

	std::size_t count = 0U;
	while (ss >> token) {
		if (numbers.contains (std::stoi (token))) { ++count; }
	}

	return count;
}

int main ()
{
	// auto input = test_input;
	auto const input = qrd::read_file (__FILE__);

	auto const begin = std::chrono::steady_clock::now ();
	std::unordered_map<std::size_t, std::size_t> cache {};

	for (std::size_t id = input.size (); 0 < id; --id) {
		assert (!cache.contains (id));

		auto const result = check_card (input [id - 1]);

		cache [id] = result;
		for (std::size_t i = 1; i <= result; ++i) {
			cache [id] += cache [id + i];
		}
	}

	std::size_t sum {input.size ()};
	for (auto const& [i, value]: cache) { sum += value; }
	auto const end = std::chrono::steady_clock::now ();

	std::cout << "[Naive]\nElapsed time: "
			  << std::chrono::duration_cast<std::chrono::microseconds> (end
																		- begin)
					 .count ()
			  << "µs" << std::endl;
	std::cout << "      Answer: " << sum << std::endl;

	return 0;
}
