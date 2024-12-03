// Copyright (c) 2023-${DATE_YEAR} Dawid Kurek <dawikur@gmail.com>

#pragma once

#include <cstdint>

#include <string_view>

namespace qrd {

// static inline constexpr auto const () const noexcept

struct version {
	static constexpr std::int32_t const major = ${${PROJECT_NAME}_VERSION_MAJOR};
	static constexpr std::int32_t const minor = ${${PROJECT_NAME}_VERSION_MINOR};
	static constexpr std::int32_t const patch = 0;
	static constexpr std::string_view const hash = "${GIT_HASH}";

	static constexpr bool const is_dirty = ${GIT_DIRTY} != 0;
};

struct config {
	static constexpr std::string_view const name = "${PROJECT_NAME}";

	static constexpr std::string_view const system_name = "${CMAKE_SYSTEM_NAME}";
	static constexpr std::string_view const build_name  = "${CMAKE_BUILD_TYPE}";
	static constexpr std::string_view const compiler_id = "${CMAKE_CXX_COMPILER_ID}";

#if defined(IS_RELEASE)
	static constexpr bool const is_release = true;
	static constexpr bool const is_debug = false;
#elif defined(IS_DEBUG)
	static constexpr bool const is_release = false;
	static constexpr bool const is_debug = true;
#else
#	error "Unknown build type"
#endif

#if defined(IS_UNIX)
	static constexpr bool const is_unix = true;
	static constexpr bool const is_win32 = false;
	static constexpr bool const is_macos = false;
#elif defined(IS_WINDOWS)
	static constexpr bool const is_unix = false;
	static constexpr bool const is_win32 = true;
	static constexpr bool const is_macos = false;
#elif defined(IS_MACOS)
	static constexpr bool const is_unix = false;
	static constexpr bool const is_win32 = false;
	static constexpr bool const is_macos = true;
#else
#   error "Unknown platform"
#endif

#if defined(IS_CLANG)
	static constexpr bool const is_clang = true;
	static constexpr bool const is_gnu = false;
	static constexpr bool const is_msvc = false;
#elif defined(IS_GNU)
	static constexpr bool const is_clang = false;
	static constexpr bool const is_gnu = true;
	static constexpr bool const is_msvc = false;
#elif defined(IS_MSVC)
	static constexpr bool const is_clang = false;
	static constexpr bool const is_gnu = false;
	static constexpr bool const is_msvc = true;
#else
#	error "Unknown compiler"
#endif

};

} // namespace qrd
