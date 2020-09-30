#include <ntstatus.h>
#include <ntstrsafe.h>
#include "ke_strutils.h"

namespace fibo::kernel::StrUtils
{
	size_t length(const wchar_t* str, size_t maxSizeInBytes)
	{
		size_t szLen = 0; // value in bytes
		auto status = RtlStringCbLengthW(str, maxSizeInBytes, &szLen); // Not include null-terminated 
		if (NT_SUCCESS(status))
		{
			return szLen / sizeof(wchar_t);
		}
		return 0;
	}

	size_t lengthInbytes(const wchar_t* str, size_t maxSizeInBytes)
	{
		size_t szLenInBytes = 0; // value in bytes
		auto status = RtlStringCbLengthW(str, maxSizeInBytes, &szLenInBytes); // Not include null-terminated 
		if (NT_SUCCESS(status)) {
			return szLenInBytes;
		}
		return 0;
	}

	bool ncopy(wchar_t* dest, size_t sizeDestInBytes, const wchar_t* src, size_t numOfBytesToCopy)
	{
		auto status = RtlStringCbCopyNW(dest, sizeDestInBytes, src, numOfBytesToCopy);
		return NT_SUCCESS(status);
	}

	bool ncat(wchar_t* dest, size_t sizeDestInBytes, const wchar_t* src, size_t numOfBytesToAppend)
	{
		auto status = RtlStringCbCatNW(dest, sizeDestInBytes, src, numOfBytesToAppend);
		return NT_SUCCESS(status);
	}

	bool equal(const wchar_t* str1, const wchar_t* str2, size_t count)
	{
		return 0 == wcsncmp(str1, str2, count);
	}

	bool iequal(const wchar_t* str1, const wchar_t* str2, size_t count)
	{
		return 0 == _wcsnicmp(str1, str2, count);
	}

	bool toLower(wchar_t* str, size_t numberOfElements)
	{
		return 0 == _wcslwr_s(str, numberOfElements);
	}
}