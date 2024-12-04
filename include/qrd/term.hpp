// Copyright (c) 2023-2024 Dawid Kurek <dawikur@gmail.com>

#pragma once

#include <qrd/rgb.hpp>

namespace qrd {

enum class Csi
{
	Bold      = 1,
	Italic    = 2,
	Underline = 4,
	Blink     = 5,
	Reverse   = 7,
	Hidden    = 8,
	Strike    = 9,

	Red     = 31,
	Green   = 32,
	Yellow  = 33,
	Blue    = 34,
	Magenta = 35,
	Cyan    = 36,
	White   = 37,
};

std::string term ()
{
	return "\033[0m";
}

std::string term (Csi const ansi)
{
	return "\033[" + std::to_string (static_cast<int> (ansi)) + "m";
}

std::string term (Csi const ansi, char const msg)
{
	return term (ansi) + msg + term ();
}

std::string term (Csi const ansi, std::string const& msg)
{
	return term (ansi) + msg + term ();
}

std::string term (std::size_t const RR,
				  std::size_t const GG,
				  std::size_t const BB)
{
	return "\033[38;2;" + std::to_string (RR) + ";" + std::to_string (GG) + ";"
		 + std::to_string (BB) + "m";
}

std::string term (std::size_t const RR,
				  std::size_t const GG,
				  std::size_t const BB,
				  char const        msg)
{
	return term (RR, GG, BB) + msg + term ();
}

std::string term (std::size_t const  RR,
				  std::size_t const  GG,
				  std::size_t const  BB,
				  std::string const& msg)
{
	return term (RR, GG, BB) + msg + term ();
}

std::string term (RGB const& rgb)
{
	return term (rgb.r, rgb.g, rgb.b);
}

std::string term (RGB const& rgb, char const msg)
{
	return term (rgb) + msg + term ();
}

std::string term (RGB const& rgb, std::string const& msg)
{
	return term (rgb) + msg + term ();
}

} // namespace qrd
