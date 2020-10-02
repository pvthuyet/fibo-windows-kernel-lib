#pragma once

#include <ntddk.h>
#include "ke_define.h"

namespace fibo::kernel
{
	class ScopedUnicodeString
	{
	public:
		ScopedUnicodeString();
		explicit ScopedUnicodeString(POOL_TYPE type, ULONG tag);
		~ScopedUnicodeString();

		KE_NODISCARD bool valid() const;
		KE_NODISCARD USHORT length() const;

		KE_NODISCARD PCUNICODE_STRING get() const;
		KE_NODISCARD PUNICODE_STRING get();

		KE_NODISCARD NTSTATUS copy(PCUNICODE_STRING src);

		KE_NODISCARD NTSTATUS append(PCWSTR src);
		KE_NODISCARD NTSTATUS append(PCUNICODE_STRING src);

		KE_NODISCARD NTSTATUS allocate(USHORT numOfBytes);
		KE_NODISCARD NTSTATUS allocate(USHORT numOfBytes, POOL_TYPE type, ULONG tag = 0);
		VOID release();

	private:
		UNICODE_STRING mUniStr;
		POOL_TYPE mPoolType;
		ULONG mTag;
	};
}

