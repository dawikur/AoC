// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <qrd.hpp>

auto const test_input = std::vector<std::string> {
	"32T3K 765",
	"T55J5 684",
	"KK677 28",
	"KTJJT 220",
	"QQQJA 483",
};

int to_int (char c)
{
	switch (c) {
		case 'J': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'T': return 10;
		case 'Q': return 12;
		case 'K': return 13;
		case 'A': return 14;
		default: assert (false);
	}

	return 0;
}

char from_int (int i)
{
	switch (i) {
		case 1: return 'J';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return 'T';
		case 12: return 'Q';
		case 13: return 'K';
		case 14: return 'A';
		default: assert (false);
	}

	return '?';
}

class Hand
{
public:
	Hand (std::string_view const _str, std::size_t const _bid)
		: str {_str}, bid {_bid}
	{
		assert (str.size () == 5);

		int              wild_cards {0};
		std::vector<int> cards;
		for (auto const c: str) {
			if (c == 'J') {
				++wild_cards;
			} else {
				cards.emplace_back (to_int (c));
			}
		}

		std::sort (cards.begin (), cards.end ());

		if (cards.empty ()) {
			buckets.emplace_back ();
		} else {
			buckets.emplace_back (1);

			for (std::size_t i = 1; i < cards.size (); ++i) {
				if (cards [i] != 1) {
					if (cards [i - 1] == cards [i]) {
						++buckets.back ();
					} else {
						buckets.emplace_back (1);
					}
				}
			}
		}

		std::sort (buckets.begin (),
				   buckets.end (),
				   [] (auto const& a, auto const& b) { return a > b; });
		buckets.front () += wild_cards;

		// if (wild_cards > 2) {
		//	std::cout << str << std::endl;
		//	std::cout << "\twild: " << wild_cards << std::endl;
		//	std::cout << "\tcards: " ;
		//	for (auto const c : cards) {
		//		std::cout << c << " ";
		//	}
		//	std::cout << std::endl;

		//	std::cout << "\tbuckets: ";
		//	for (auto const& b: buckets) {
		//		std::cout << b << " ";
		//	}
		//	std::cout << std::endl;
		//}

		cards.resize (str.size ());
		for (size_t i = 0; i < str.size (); ++i) {
			cards [i] = to_int (str [i]);
		}
	}

	bool operator< (Hand const& other) const
	{
		for (std::size_t i = 0;
			 i < std::min (buckets.size (), other.buckets.size ());
			 ++i) {
			if (buckets [i] < other.buckets [i]) { return true; }
			if (buckets [i] > other.buckets [i]) { return false; }
		}
		for (std::size_t i = 0; i < str.size (); ++i) {
			if (to_int (str [i]) < to_int (other.str [i])) { return true; }
			if (to_int (str [i]) > to_int (other.str [i])) { return false; }
		}

		return false;
	}

	std::string      str;
	std::size_t      bid;
	std::vector<int> buckets;
};

int main ()
{
	// auto const input = test_input;
	auto const input = qrd::read_input (__FILE__);

	std::vector<Hand> hands;
	hands.reserve (input.size ());

	for (auto const& line: input) {
		auto const tokens = qrd::split (line, ' ');
		hands.emplace_back (tokens [0], std::stoull (std::string (tokens [1])));
	}

	std::sort (hands.begin (), hands.end ());

	std::size_t sum {};
	for (std::size_t i = 0; i < hands.size (); ++i) {
		auto const& hand  = hands [i];
		auto const  value = (i + 1) * hand.bid;

		std::cout << "[" << hand.str << "] " << (i + 1) << " * " << hand.bid
				  << " == " << value << '\n';

		for (auto const& bucket: hand.buckets) { std::cout << " " << bucket; }
		std::cout << std::endl;

		sum += value;
	}

	std::cout << "Sum: " << sum << std::endl;

	return 0;
}
