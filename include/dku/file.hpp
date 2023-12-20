// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#pragma once

#include <dku/std.hpp>

namespace dku {

using Input = std::vector<std::string>;

Input read_file (std::ifstream input)
{
	Input       lines;
	std::string line;
	while (std::getline (input, line)) { lines.push_back (line); }
	return lines;
}

Input read_input (std::string const& file)
{
	std::filesystem::path const path {file};
	auto const                  input = path.parent_path () / "input.txt";

	return read_file (std::ifstream {input.string ()});
}

} // namespace dku
