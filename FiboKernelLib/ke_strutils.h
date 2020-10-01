#pragma once

#include "ke_define.h"
#include "ke_constant.h"

namespace fibo::kernel::StrUtils
{
	KE_NODISCARD size_t length(const wchar_t* str, size_t maxSizeInBytes = kMaxStrLengthInBytes);
	KE_NODISCARD size_t lengthInbytes(const wchar_t* str, size_t maxSizeInBytes = kMaxStrLengthInBytes);

	bool ncopy(wchar_t* dest, size_t sizeDestInBytes, const wchar_t* src, size_t numOfBytesToCopy);
	bool ncat(wchar_t* dest, size_t sizeDestInBytes, const wchar_t* src, size_t numOfBytesToAppend);

	bool equal(const wchar_t* str1, const wchar_t* str2, size_t count);
	bool iequal(const wchar_t* str1, const wchar_t* str2, size_t count);

	bool toLower(wchar_t* str, size_t numberOfElements);

	const wchar_t* substr(const wchar_t* str, const wchar_t* strSearch);
}