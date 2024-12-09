// Copyright (c) 2023-2024 Dawid Kurek <dawikur@gmail.com>

#pragma once

template <class Key, class Type>
std::ostream& operator<< (std::ostream& os, std::unordered_map<Key, Type> const& map)
{
	bool first{true};

	os << '{';
	for (auto const& [key, value]: map) {
		os << (first ? "" : ", ") << key << ": " << value;
		first = false;
	}
	os << '}';

	return os;
}

template <class Type>
std::ostream& operator<< (std::ostream& os, std::unordered_set<Type> const& set)
{
	bool first{true};

	os << '{';
	for (auto const& value: set) {
		os << (first ? "" : ", ") << value;
		first = false;
	}
	os << '}';

	return os;
}
