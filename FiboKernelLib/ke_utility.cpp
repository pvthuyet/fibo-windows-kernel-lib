#include "ke_utility.h"
#include "ke_algorithm.h"
#include "ke_constant.h"

namespace fibo::kernel::Utility
{
	_NODISCARD size_t minUpper(size_t x, size_t factor) noexcept
	{
		factor = Algorithm::max(factor, kMinMemoryBlock);
		return (((x + factor) / factor) * factor);
	}
}