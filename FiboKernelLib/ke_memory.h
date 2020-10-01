#pragma once

#include <ntddk.h>
#include "ke_define.h"

namespace fibo::kernel::Memory
{
	KE_NODISCARD NTSTATUS allocateUnicodeString(_Inout_ PUNICODE_STRING str, 
		_In_ USHORT numOfBytes, 
		_In_ POOL_TYPE type = PagedPool, 
		_In_ ULONG tag = 0);

	VOID freeUnicodeString(_Inout_ PUNICODE_STRING str, _In_ ULONG tag);
}