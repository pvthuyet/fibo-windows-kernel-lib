#pragma once

#include <ntddk.h>
#include "ke_define.h"

namespace fibo::kernel
{
	class ScopedUnicodeString
	{
	public:
		ScopedUnicodeString();
		~ScopedUnicodeString();

		PCUNICODE_STRING get() const;
		PUNICODE_STRING get();

		VOID copy(PCUNICODE_STRING src);

		KE_NODISCARD NTSTATUS append(PCWSTR src);
		KE_NODISCARD NTSTATUS append(PCUNICODE_STRING src);

		KE_NODISCARD NTSTATUS allocate(USHORT numOfBytes, POOL_TYPE type = PagedPool, ULONG tag = 0);
		VOID release();

	private:
		UNICODE_STRING mUniStr;
		POOL_TYPE mPoolType;
		ULONG mTag;
	};
}

