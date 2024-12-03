// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#pragma once

namespace qrd {

std::vector<std::string_view> split (std::string_view const string,
									 char const             delimiter,
									 bool const             keep_empty = false)
{
	std::vector<std::string_view> result {};

	std::size_t begin = 0U;
	std::size_t end   = string.find (delimiter);

	while (end != std::string::npos) {
		auto const substr = string.substr (begin, end - begin);

		if (!substr.empty () || keep_empty) { result.emplace_back (substr); }

		begin = end + 1U;
		end   = string.find (delimiter, begin);
	}

	{
		auto const substr = string.substr (begin);
		if (!substr.empty () || keep_empty) { result.emplace_back (substr); }
	}

	return result;
}

template <class Type>
std::vector<Type> split_as (std::string_view const string,
							char const             delimiter,
							bool const             keep_empty = false)
{
	auto const tokens = split (string, delimiter, keep_empty);

	std::vector<Type> result {};
	result.reserve (tokens.size ());

	for (auto const& token: tokens) {
		Type value {};
		std::from_chars (token.data (), token.data () + token.size (), value);

		result.emplace_back (value);
	}

	return result;
}

std::string join (std::vector<std::string> const& strings,
				  std::string const&              delimiter)
{
	std::string result;

	if (strings.empty ()) { return result; }

	result += strings [0];
	for (std::size_t i = 1U; i < strings.size (); ++i) {
		result += delimiter;
		result += strings [i];
	}

	return result;
}

} // namespace qrd
