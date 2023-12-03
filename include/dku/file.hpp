// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace dku {

std::vector<std::string> read_file (std::ifstream input)
{
	std::vector<std::string> lines;
	std::string              line;
	while (std::getline (input, line)) { lines.push_back (line); }
	return lines;
}

std::vector<std::string> read_input (std::string const& file)
{
	std::filesystem::path const path {file};
	auto const                  input = path.parent_path () / "input.txt";

	return read_file (std::ifstream {input.string ()});
}

} // namespace dku
