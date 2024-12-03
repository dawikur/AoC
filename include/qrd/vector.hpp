// Copyright (c) 2023-2024 Dawid Kurek <dawikur@gmail.com>

#pragma once

template <class Type>
std::ostream& operator<< (std::ostream& os, std::vector<Type> const& vector)
{
	os << '[';
	for (std::size_t i = 0U; i < vector.size (); ++i) {
		os << (i == 0U ? "" : ", ") << vector [i];
	}
	os << ']';

	return os;
}

template <class Type>
std::vector<Type> operator* (std::vector<Type> const& lhs,
							 std::size_t const        rhs)
{
	std::vector<Type> result;
	result.reserve (lhs.size () * rhs);

	result.insert (result.end (), lhs.begin (), lhs.end ());

	return result;
}
