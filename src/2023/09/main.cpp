// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

std::vector<std::string> test_input {
	"0 3 6 9 12 15",
	"1 3 6 10 15 21",
	"10 13 16 21 30 45",
};

std::vector<std::int64_t> derivate (std::vector<std::int64_t> const& sequence)
{
	std::vector<std::int64_t> result;
	result.reserve (sequence.size () - 1);

	for (std::size_t i = 1; i < sequence.size (); ++i) {
		result.push_back (sequence [i] - sequence [i - 1]);
	}

	return result;
}

bool are_all_zeros (std::vector<std::int64_t> const& sequence)
{
	for (auto const& val: sequence) {
		if (val != 0) { return false; }
	}

	return true;
}

void extrapolate (std::vector<std::int64_t>& sequence)
{
	auto der = derivate (sequence);

	if (are_all_zeros (der)) {
		der.push_back (0);
		return;
	} else {
		extrapolate (der);
	}

	sequence.push_back (sequence.back () + der.back ());
}

int main ()
{
	// auto const input = test_input;
	auto const input = qrd::read_file (__FILE__);

	std::int64_t sum {};
	for (auto const& line: input) {
		std::stringstream ss (line);

		std::vector<std::int64_t> sequence;
		sequence.reserve (line.size () / 2 + 1);

		{
			std::int64_t val;
			while (ss >> val) { sequence.push_back (val); }

			std::reverse (sequence.begin (), sequence.end ());
		}

		for (auto const& val: sequence) { std::cout << val << " "; }
		extrapolate (sequence);

		std::cout << "[" << sequence.back () << "]" << std::endl;

		sum += sequence.back ();
	}

	std::cout << "Sum: " << sum << std::endl;

	return 0;
}
