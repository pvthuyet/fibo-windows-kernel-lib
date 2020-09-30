#include "ke_utility.h"
#include "ke_algorithm.h"
#include "ke_constant.h"

namespace fibo::kernel::Utility
{
	KE_NODISCARD size_t aligned(size_t operand, size_t alignment) KE_NOEXCEPT
	{
		alignment = Algorithm::max(alignment, kMinMemoryBlock);
		return ((operand + alignment) & ~(alignment - 1));
	}
}