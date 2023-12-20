// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <dku.hpp>

auto const test_input = std::vector<std::string> {
	"Time:      7  15   30",
	"Distance:  9  40  200",
};

auto const test_input_part2 = std::vector<std::string> {
	"Time:      71530",
	"Distance:  940200",
};

auto const input_part2 = std::vector<std::string> {
	"Time:       44826981",
	"Distance:   202107611381458",
};

int main ()
{
	// auto const input = dku::read_input(__FILE__);
	auto const input = input_part2;

	std::string dummy;

	std::stringstream stream_time {input [0]};
	std::stringstream stream_distance {input [1]};

	stream_time >> dummy;
	stream_distance >> dummy;

	float time;
	float distance;

	int sum {1};
	while (stream_time >> time && stream_distance >> distance) {
		std::cout << time << ": " << distance << std::endl;
		float const a = 1;
		float const b = -time;
		float const c = distance;

		float const delta = b * b - 4 * a * c;
		float       x1    = (-b - std::sqrt (delta)) / (2 * a);
		float       x2    = (-b + std::sqrt (delta)) / (2 * a);

		std::cout << "\t" << x2 << " - " << x1 << std::endl;
		if (float (int (x1)) == x1) { ++x1; }
		if (float (int (x2)) == x2) { --x2; }

		std::cout << "\t" << std::floor (x2) << " - " << std::ceil (x1)
				  << std::endl;
		auto result = int (std::floor (x2) - std::ceil (x1) + 1);
		std::cout << "\t" << result << std::endl;
		sum *= result;
	}

	std::cout << sum << std::endl;

	return 0;
}
