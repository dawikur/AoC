// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <functional>

namespace dku {

struct Point
{
	std::int32_t x {};
	std::int32_t y {};

	bool operator== (Point const& p) const { return x == p.x && y == p.y; }
};

} // namespace dku

namespace std {

template <>
struct hash<dku::Point>
{
	std::size_t operator() (dku::Point const& p) const
	{
		return std::hash<int> {}(p.x) ^ (std::hash<int> {}(p.y) << 1);
	}
};

} // namespace std
