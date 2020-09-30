#pragma once
#include "ke_define.h"

namespace fibo::kernel::Utility
{
	KE_NODISCARD size_t aligned(size_t operand, size_t alignment = 8) KE_NOEXCEPT;
}
