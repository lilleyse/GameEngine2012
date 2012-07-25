#pragma once

namespace Utils
{
	/**
	*	/brief hacky way to get next power of 2
	*/

	int nextPowerOf2(int x)
	{
		--x;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return ++x;
	}
};