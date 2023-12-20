// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#pragma once

#include <dku/std.hpp>

namespace dku {

enum class Ansi
{
	Red     = 31,
	Green   = 32,
	Yellow  = 33,
	Blue    = 34,
	Magenta = 35,
	Cyan    = 36,
	White   = 37,
};

std::string reset ()
{
	return "\033[0m";
}

std::string color (Ansi const ansi)
{
	return "\033[" + std::to_string (static_cast<int> (ansi)) + "m";
}

std::string color (Ansi const ansi, char const msg)
{
	return color (ansi) + msg + reset ();
}

std::string color (Ansi const ansi, std::string const& msg)
{
	return color (ansi) + msg + reset ();
}

std::string color (std::size_t const RR,
				   std::size_t const GG,
				   std::size_t const BB)
{
	return "\033[38;2;" + std::to_string (RR) + ";" + std::to_string (GG) + ";"
		 + std::to_string (BB) + "m";
}

std::string color (std::size_t const RR,
				   std::size_t const GG,
				   std::size_t const BB,
				   char const        msg)
{
	return color (RR, GG, BB) + msg + reset ();
}

std::string color (std::size_t const  RR,
				   std::size_t const  GG,
				   std::size_t const  BB,
				   std::string const& msg)
{
	return color (RR, GG, BB) + msg + reset ();
}

} // namespace dku
