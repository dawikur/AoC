// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <dku/file.hpp>

int main ()
{
	auto const input = dku::read_input (__FILE__);

	int paper  = 0;
	int ribbon = 0;
	for (auto const& line: input) {
		int l;
		int w;
		int h;

		std::sscanf (line.c_str (), "%dx%dx%d", &l, &w, &h);

		{
			auto const lw = l * w;
			auto const wh = w * h;
			auto const hl = h * l;

			paper += 2 * lw + 2 * wh + 2 * hl;

			if (lw < wh && lw < hl) {
				paper += lw;
			} else if (wh < hl) {
				paper += wh;
			} else {
				paper += hl;
			}
		}
		{
			auto const lw = l + w;
			auto const wh = w + h;
			auto const hl = h + l;

			if (lw < wh && lw < hl) {
				ribbon += 2 * lw;
			} else if (wh < hl) {
				ribbon += 2 * wh;
			} else {
				ribbon += 2 * hl;
			}

			ribbon += l * w * h;
		}
	}

	std::cout << "Paper: " << paper << std::endl;
	std::cout << "Ribbon: " << ribbon << std::endl;

	return 0;
}
