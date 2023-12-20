// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <dku.hpp>

auto const test_input_1 = std::vector<std::string> {
	"RL",
	"",
	"AAA = (BBB, CCC)",
	"BBB = (DDD, EEE)",
	"CCC = (ZZZ, GGG)",
	"DDD = (DDD, DDD)",
	"EEE = (EEE, EEE)",
	"GGG = (GGG, GGG)",
	"ZZZ = (ZZZ, ZZZ)",
};

auto const test_input_2 = std::vector<std::string> {
	"LLR",
	"",
	"AAA = (BBB, BBB)",
	"BBB = (AAA, ZZZ)",
	"ZZZ = (ZZZ, ZZZ)",
};

auto const test_input_3 = std::vector<std::string> {
	"LR",
	"",
	"11A = (11B, XXX)",
	"11B = (XXX, 11Z)",
	"11Z = (11B, XXX)",
	"22A = (22B, XXX)",
	"22B = (22C, 22C)",
	"22C = (22Z, 22Z)",
	"22Z = (22B, 22B)",
	"XXX = (XXX, XXX)",
};

std::size_t encode_char (char const c)
{
	return static_cast<std::size_t> (c) - ' ';
}

std::size_t encode_node (std::string const& line, std::size_t i)
{
	return encode_char (line [i + 0]) * 10000U
		 + encode_char (line [i + 1]) * 100U + encode_char (line [i + 2]);
}

char decode_char (std::size_t const c)
{
	return static_cast<char> (c + ' ');
}

std::string decode_node (std::size_t node_id)
{
	return std::string {
		decode_char (node_id / 10000U),
		decode_char (node_id / 100U % 100U),
		decode_char (node_id % 100U),
	};
}

bool is_end_node (std::size_t node_id)
{
	return decode_char (node_id % 100U) == 'Z';
}

bool are_all_nodes_end (std::vector<std::size_t> const& nodes)
{
	for (auto const node: nodes) {
		if (!is_end_node (node)) { return false; }
	}

	return true;
}

std::size_t GCD (std::size_t a, std::size_t b)
{
	while (b != 0) {
		auto const t = b;
		b            = a % b;
		a            = t;
	}

	return a;
}

std::size_t LCM (std::size_t a, std::size_t b)
{
	return a * b / GCD (a, b);
}

int main ()
{
	// auto const input = test_input_3;
	auto const input = dku::read_input (__FILE__);

	std::vector<std::size_t> instructions;
	instructions.reserve (input [0].size ());
	for (auto const c: input [0]) {
		switch (c) {
			case 'L': instructions.push_back (0); break;
			case 'R': instructions.push_back (1); break;
		}
	}

	std::unordered_map<std::size_t, std::array<std::size_t, 2>> nodes;

	std::vector<std::size_t> current_nodes;

	for (std::size_t i {2}; i < input.size (); ++i) {
		auto const line = input [i];

		auto const node_id = encode_node (line, 0);
		auto const L_id    = encode_node (line, 7);
		auto const R_id    = encode_node (line, 7 + 5);

		if (line [2] == 'A') { current_nodes.push_back (node_id); }

		nodes [node_id] = {L_id, R_id};
	}

	std::size_t steps {1};
	for (auto& node: current_nodes) {
		std::size_t i {};

		while (!is_end_node (node)) {
			node = nodes [node][instructions [i % instructions.size ()]];

			++i;
		}

		steps = LCM (steps, i);
	}

	std::cout << steps << std::endl;

	return 0;
}
