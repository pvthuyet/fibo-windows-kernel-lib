#pragma once

namespace fibo::kernel
{
	constexpr size_t kMinMemoryBlock		= 0x00000008; // in bytes
	constexpr size_t kMaxStrLengthInBytes	= 0x7FFFFFFE; // NTSTRSAFE_MAX_LENGTH
	constexpr size_t npos = static_cast<size_t>(-1);
}