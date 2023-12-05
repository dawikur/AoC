// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace dku {

std::vector<std::string_view> split (std::string_view const string,
									 char const             delimiter)
{
	std::vector<std::string_view> result {};

	std::size_t begin = 0U;
	std::size_t end   = string.find (delimiter);

	while (end != std::string::npos) {
		result.emplace_back (string.substr (begin, end - begin));

		begin = end + 1U;
		end   = string.find (delimiter, begin);
	}

	result.emplace_back (string.substr (begin));

	return result;
}

} // namespace dku
