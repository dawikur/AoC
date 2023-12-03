// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <chrono>

#include "dku/file.hpp"
#include "dku/std.hpp"

int solve_naive (std::vector<std::string> const& lines)
{
	std::array<std::string_view, 10> digits = {"zero",
											   "one",
											   "two",
											   "three",
											   "four",
											   "five",
											   "six",
											   "seven",
											   "eight",
											   "nine"};
	int                              result = 0;

	for (auto const& line: lines) {
		{
			int pos   = std::numeric_limits<int>::max ();
			int digit = 0;

			for (std::size_t i = 1; i < digits.size (); ++i) {
				auto const pos_str = line.find (digits [i]);
				if (pos_str != std::string_view::npos
					&& static_cast<int> (pos_str) < pos) {
					pos   = static_cast<int> (pos_str);
					digit = static_cast<int> (i);
				}
			}

			if (auto const pos_digit = line.find_first_of ("0123456789");
				pos_digit != std::string_view::npos
				&& static_cast<int> (pos_digit) < pos) {
				pos   = static_cast<int> (pos_digit);
				digit = static_cast<std::size_t> (line [pos_digit] - '0');
			}

			result += digit * 10;
		}

		{
			auto pos   = std::numeric_limits<int>::min ();
			auto digit = 0;

			for (std::size_t i = 1; i < digits.size (); ++i) {
				auto const pos_str = line.rfind (digits [i]);
				if (pos_str != std::string_view::npos
					&& static_cast<int> (pos_str) > pos) {
					pos   = static_cast<int> (pos_str);
					digit = static_cast<int> (i);
				}
			}

			if (auto const pos_digit = line.find_last_of ("0123456789");
				pos_digit != std::string_view::npos
				&& static_cast<int> (pos_digit) > pos) {
				pos   = static_cast<int> (pos_digit);
				digit = static_cast<std::size_t> (line [pos_digit] - '0');
			}

			result += digit;
		}
	}

	return result;
}

int main ()
{
	auto const lines = dku::read_input (__FILE__);

	{
		auto const begin    = std::chrono::steady_clock::now ();
		int const  solution = solve_naive (lines);
		auto const end      = std::chrono::steady_clock::now ();

		std::cout << "[Naive]\nElapsed time: "
				  << std::chrono::duration_cast<std::chrono::microseconds> (
						 end - begin)
						 .count ()
				  << "µs" << std::endl;
		std::cout << "      Answer: " << solution << std::endl;
	}

	return 0;
}
