#pragma once

namespace fibo::kernel
{
	constexpr size_t kMinMemoryBlock		= 0x00000008; // in bytes
	constexpr size_t kMaxStrLengthInBytes	= 0xFFFFFFFE; // NTSTRSAFE_MAX_CCH * sizof(wchar_t)
	constexpr size_t npos = static_cast<size_t>(-1);
}