// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#pragma once

#include <cstdint>

#include "config.hpp"

namespace dku {

///////////////////////////////////////////////////////////////////////////////
// Helpers

struct Ignore
{
	template <class... Args>
	explicit inline constexpr Ignore (Args&&...) noexcept
	{}

	template <class... Args>
	inline constexpr Ignore const& operator= (Args&&...) const noexcept
	{
		return *this;
	}

	template <class... Args>
	inline constexpr void operator() (Args&&...) const noexcept
	{}
};
static inline constexpr auto const ignore = Ignore {};

struct None
{};
static inline constexpr auto const none = None {};

template <class...>
using False = std::false_type;

template <class...>
using True = std::true_type;

template <class...>
static inline constexpr bool const false_v = false;
static_assert (!false_v<>);

template <class...>
static inline constexpr bool const true_v = true;
static_assert (true_v<>);

///////////////////////////////////////////////////////////////////////////////
// Types

static_assert (sizeof (bool) == 1);

static_assert (sizeof (std::byte) == 1);

using byte = std::byte;

static_assert (sizeof (float) == 4);
static_assert (sizeof (double) == 8);

using f32 = float;
using f64 = double;

static_assert (sizeof (char) == 1);

using c8  = char;
using c16 = char16_t;
using c32 = char32_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

#ifdef IS_WINDOWS
using BYTE  = u8;
using WORD  = u16;
using DWORD = u32;

using SHORT = i16;
using LONG  = i32;
#endif

///////////////////////////////////////////////////////////////////////////////
// Variables

template <class Type>
inline constexpr Type const Pi = Type (3.1415926535897932385L);

template <class Type>
inline constexpr Type const Tau = Pi<Type>* Type {2};

///////////////////////////////////////////////////////////////////////////////
// user literals

inline namespace literals {

// floats

[[nodiscard]] inline constexpr auto operator""_f32 (
	unsigned long long const value) noexcept
{
	return static_cast<f32> (value);
}

[[nodiscard]] inline constexpr auto operator""_f32 (
	long double const value) noexcept
{
	return static_cast<f32> (value);
}

[[nodiscard]] inline constexpr auto operator""_f64 (
	unsigned long long const value) noexcept
{
	return static_cast<f64> (value);
}

[[nodiscard]] inline constexpr auto operator""_f64 (
	long double const value) noexcept
{
	return static_cast<f64> (value);
}

// unsigned

[[nodiscard]] inline constexpr auto operator""_u8 (
	unsigned long long const value) noexcept
{
	return static_cast<u8> (value);
}

[[nodiscard]] inline constexpr auto operator""_u16 (
	unsigned long long const value) noexcept
{
	return static_cast<u16> (value);
}

[[nodiscard]] inline constexpr auto operator""_u32 (
	unsigned long long const value) noexcept
{
	return static_cast<u32> (value);
}

[[nodiscard]] inline constexpr auto operator""_u64 (
	unsigned long long const value) noexcept
{
	return static_cast<u64> (value);
}

// signed

[[nodiscard]] inline constexpr auto operator""_i8 (
	unsigned long long const value) noexcept
{
	return static_cast<i8> (value);
}

[[nodiscard]] inline constexpr auto operator""_i16 (
	unsigned long long const value) noexcept
{
	return static_cast<i16> (value);
}

[[nodiscard]] inline constexpr auto operator""_i32 (
	unsigned long long const value) noexcept
{
	return static_cast<i32> (value);
}

[[nodiscard]] inline constexpr auto operator""_i64 (
	unsigned long long const value) noexcept
{
	return static_cast<i64> (value);
}

///////////////////////////////////////////////////////////////////////////////
// Multiplies

// kilo

[[nodiscard]] inline constexpr auto operator""_KB (
	unsigned long long const value) noexcept
{
	return static_cast<u32> (value) * 1000;
}

[[nodiscard]] inline constexpr auto operator""_KB (
	long double const value) noexcept
{
	return static_cast<u32> (value) * 1000;
}

[[nodiscard]] inline constexpr auto operator""_KiB (
	unsigned long long const value) noexcept
{
	return static_cast<u32> (value) * 1024;
}

[[nodiscard]] inline constexpr auto operator""_KiB (
	long double const value) noexcept
{
	return static_cast<u32> (value) * 1024;
}

// mega

[[nodiscard]] inline constexpr auto operator""_MB (
	unsigned long long const value) noexcept
{
	return static_cast<u32> (value) * 1000_KB;
}

[[nodiscard]] inline constexpr auto operator""_MB (
	long double const value) noexcept
{
	return static_cast<u32> (value) * 1000_KB;
}

[[nodiscard]] inline constexpr auto operator""_MiB (
	unsigned long long const value) noexcept
{
	return static_cast<u32> (value) * 1024_KiB;
}

[[nodiscard]] inline constexpr auto operator""_MiB (
	long double const value) noexcept
{
	return static_cast<u32> (value) * 1024_KiB;
}

// giga

[[nodiscard]] inline constexpr auto operator""_GB (
	unsigned long long const value) noexcept
{
	return static_cast<u32> (value) * 1000_MB;
}

[[nodiscard]] inline constexpr auto operator""_GB (
	long double const value) noexcept
{
	return static_cast<u32> (value) * 1000_MB;
}

[[nodiscard]] inline constexpr auto operator""_GiB (
	unsigned long long const value) noexcept
{
	return static_cast<u32> (value) * 1024_MiB;
}

[[nodiscard]] inline constexpr auto operator""_GiB (
	long double const value) noexcept
{
	return static_cast<u32> (value) * 1024_MiB;
}

} // namespace literals

} // namespace dku
