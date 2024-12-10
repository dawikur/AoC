// Copyright (c) 2023-2024 Dawid Kurek <dawikur@gmail.com>

namespace qrd {

template <class Type>
struct Point
{
	Type x {};
	Type y {};

	bool operator== (Point const& p) const { return x == p.x && y == p.y; }
	bool operator!= (Point const& p) const { return x != p.x || y != p.y; }

	Point& operator+= (Point const& p) { x += p.x; y += p.y; return *this; }
	Point& operator-= (Point const& p) { x -= p.x; y -= p.y; return *this; }

	Point& operator*= (Type const s) { x *= s; y *= s; return *this; }
	Point& operator/= (Type const s) { x /= s; y /= s; return *this; }

	Point operator+ (Point const& p) const { return {x + p.x, y + p.y}; }
	Point operator- (Point const& p) const { return {x - p.x, y - p.y}; }

	Point operator* (Type const s) const { return {x * s, y * s}; }
	Point operator/ (Type const s) const { return {x / s, y / s}; }

	template <class NewType>
	auto as() const
	{
		return Point<NewType> {static_cast<NewType> (x),
							   static_cast<NewType> (y)};
	}

	template <class Data>
	auto const& get_from (std::vector<Data> const& data) const
	{
		auto const p_size = as<std::size_t>();

		return data[p_size.y][p_size.x];
	}

	// clang-format off
	template <class Data>
	bool is_in (std::vector<Data> const& data) const
	{
		auto const p_size = as<std::size_t>();

		return !data.empty() &&
			   0 <= x && p_size.x < data[0].size() &&
			   0 <= y && p_size.y < data.size();
	}

	static std::vector<Point> cardinals ()
	{
		return {
			          {0, -1},
			{-1,  0},          {1,  0},
			          {0,  1},
		};
	}

	static std::vector<Point> diagonals ()
	{
		return {
			{-1, -1},           {1, -1},

			{-1,  1},           {1,  1},
		};
	}

	static std::vector<Point> all ()
	{
		return {
			{-1, -1}, {0, -1}, {1, -1},
			{-1,  0},          {1,  0},
			{-1,  1}, {0,  1}, {1,  1},
		};
	}
	// clang-format on
};

template <class Type>
using Points = std::vector<Point<Type>>;

template <class Type>
Type manhattan_distance (Point<Type> const& a, Point<Type> const& b)
{
	return std::abs (a.x - b.x) + std::abs (a.y - b.y);
}

template <class Type>
std::ostream& operator<< (std::ostream& os, Point<Type> const& point)
{
	return os << '(' << point.x << ", " << point.y << ')';
}

} // namespace qrd

namespace std {

template <class Type>
struct hash<qrd::Point<Type>>
{
	std::size_t operator() (qrd::Point<Type> const& p) const
	{
		std::size_t h1 = std::hash<Type> {}(p.x);
		std::size_t h2 = std::hash<Type> {}(p.y);

		return h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
	}
};

} // namespace std
