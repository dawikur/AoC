// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

namespace dku {

template <class Type>
struct Point
{
	Type x {};
	Type y {};

	bool operator== (Point const& p) const { return x == p.x && y == p.y; }
};

template <class Type>
using Points = std::vector<Point<Type>>;

template <class Type>
std::ostream& operator<< (std::ostream& os, Point<Type> const& point)
{
	return os << '(' << point.x << ", " << point.y << ')';
}

} // namespace dku

namespace std {

template <class Type>
struct hash<dku::Point<Type>>
{
	std::size_t operator() (dku::Point<Type> const& p) const
	{
		return std::hash<Type> {}(p.x) ^ (std::hash<Type> {}(p.y) << 1);
	}
};

} // namespace std
