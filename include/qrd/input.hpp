// Copyright (c) 2023-2024 Dawid Kurek <dawikur@gmail.com>

#pragma once

namespace qrd {

using Input = std::vector<std::string>;

Input read_file (std::ifstream input)
{
	Input       lines;
	std::string line;
	while (std::getline (input, line)) { lines.push_back (line); }
	return lines;
}

Input read_file (std::string const& file)
{
	std::filesystem::path const path {file};
	auto const                  input = path.parent_path () / "input.txt";

	return read_file (std::ifstream {input.string ()});
}

} // namespace qrd
