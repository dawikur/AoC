// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <dku/file.hpp>
#include <dku/std.hpp>

int main ()
{
	int sum {};
	int sum2 {};

	for (auto const& line: dku::read_input (__FILE__)) {
		std::stringstream ss {line};

		int min = std::numeric_limits<int>::max ();
		int max = std::numeric_limits<int>::min ();

		int              val {};
		std::vector<int> values;
		while (ss >> val) {
			if (val < min) { min = val; }
			if (max < val) { max = val; }

			for (auto const& v: values) {
				if (val % v == 0) {
					sum2 += val / v;
				} else if (v % val == 0) {
					sum2 += v / val;
				}
			}

			values.emplace_back (val);
		}

		sum += max - min;
	}

	std::cout << "     Checksum: " << sum << std::endl;
	std::cout << "Even Checksum: " << sum2 << std::endl;

	return 0;
}
