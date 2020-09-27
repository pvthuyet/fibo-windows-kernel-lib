#pragma once
#include "define.h"

namespace fibo::kernel::Utility
{
	_NODISCARD inline size_t minUpper(size_t x, size_t factor = 8) noexcept
	{
		return (((x + factor) / factor) * factor);
	}
}
