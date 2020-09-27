#include "Utility.h"
#include "algorithm.h"

namespace fibo::kernel::Utility
{
	_NODISCARD size_t minUpper(size_t x, size_t factor) noexcept
	{
		factor = Algorithm::max(factor, 4u);
		return (((x + factor) / factor) * factor);
	}
}