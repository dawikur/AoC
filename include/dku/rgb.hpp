// Copyright (c) 2023 Dawid Kurek <dawikur@gmail.com>

#include <cassert>

namespace dku {

struct RGB
{
	float r;
	float g;
	float b;

	static RGB from_1D (float const f);
};

inline RGB RGB::from_1D (float const f)
{
	assert (0.F <= f && f <= 1.F);

	constexpr auto const _18 = 1.F / 8.F;
	constexpr auto const _28 = 2.F / 8.F;
	constexpr auto const _38 = 3.F / 8.F;
	constexpr auto const _48 = 4.F / 8.F;
	constexpr auto const _58 = 5.F / 8.F;
	constexpr auto const _68 = 6.F / 8.F;
	constexpr auto const _78 = 7.F / 8.F;

	if (f < _18) {
		// 00;00;00
		return {0.F, 0.F, f * 8.F};
		// 00;00;FF
	} else if (f < _28) {
		// 00;00;FF
		return {0.F, (f - _18) * 8.F, 1.F};
		// 00;FF;FF
	} else if (f < _38) {
		// 00;FF;FF
		return {0.F, 1.F, 1.F - (f - _28) * 8.F};
		// 00;FF;00
	} else if (f < _48) {
		// 00;FF;00
		return {(f - _38) * 8.F, 1.F, 0.F};
		// FF;FF;00
	} else if (f < _58) {
		// FF;FF;00
		return {1.F, 1.F, (f - _48) * 8.F};
		// FF;FF;FF
	} else if (f < _68) {
		// FF;FF;FF
		return {1.F, 1.F - (f - _58) * 8.F, 1.F};
		// FF;00;FF
	} else if (f < _78) {
		// FF;00;FF
		return {1.F, 0.F, 1.F - (f - _68) * 8.F};
		// FF;00;00
	} else {
		return {1.F, 0.F, 0.F};
		// FF;00;00
	}
}

} // namespace dku
