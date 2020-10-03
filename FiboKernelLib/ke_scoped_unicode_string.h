#pragma once

#include <ntddk.h>
#include "ke_define.h"

namespace fibo::kernel
{
	class ScopedUnicodeString
	{
	public:
		ScopedUnicodeString();
		explicit ScopedUnicodeString(PCWCH src, size_t count, POOL_TYPE type = PagedPool, ULONG tag = KE_DRIVER_TAG_DEFAULT);
		explicit ScopedUnicodeString(PCUNICODE_STRING src, POOL_TYPE type = PagedPool, ULONG tag = KE_DRIVER_TAG_DEFAULT);
		explicit ScopedUnicodeString(size_t numOfAllocBytes, PCUNICODE_STRING src, POOL_TYPE type = PagedPool, ULONG tag = KE_DRIVER_TAG_DEFAULT);
		explicit ScopedUnicodeString(POOL_TYPE type, ULONG tag = KE_DRIVER_TAG_DEFAULT);

		~ScopedUnicodeString();

		operator bool() const;

		KE_NODISCARD bool valid() const;
		KE_NODISCARD USHORT length() const;

		KE_NODISCARD PCUNICODE_STRING get() const;
		KE_NODISCARD PUNICODE_STRING get();

		KE_NODISCARD NTSTATUS copy(PCUNICODE_STRING src);

		KE_NODISCARD NTSTATUS append(PCWSTR src);
		KE_NODISCARD NTSTATUS append(PCUNICODE_STRING src);

		KE_NODISCARD NTSTATUS allocate(size_t numOfBytes);
		KE_NODISCARD NTSTATUS allocate(size_t numOfBytes, POOL_TYPE type, ULONG tag = 0);
		VOID release();

	private:
		UNICODE_STRING mUniStr;
		POOL_TYPE mPoolType;
		ULONG mTag;
	};
}

