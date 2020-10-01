#include "ke_memory.h"
#include <ntddk.h>

namespace fibo::kernel::Memory
{
	_Use_decl_annotations_
	NTSTATUS allocateUnicodeString(_Inout_ PUNICODE_STRING str,
			_In_ USHORT numOfBytes,
			_In_ POOL_TYPE type,
			_In_ ULONG tag)
	{
		PAGED_CODE();
		
		if (!str || 0 == numOfBytes) {
			return STATUS_INVALID_PARAMETER;
		}

		str->Buffer = static_cast<PWCH>(ExAllocatePoolWithTag(type, numOfBytes, tag));
		if (nullptr == str->Buffer) {
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		RtlZeroMemory(str->Buffer, numOfBytes);
		str->Length = 0;
		str->MaximumLength = numOfBytes;
		return STATUS_SUCCESS;
	}

	_Use_decl_annotations_
	VOID freeUnicodeString(_Inout_ PUNICODE_STRING str, _In_ ULONG tag)
	{
		PAGED_CODE();
		
		if (str)
		{
			if (str->Buffer)
			{
				ExFreePoolWithTag(str->Buffer, tag);
			}
			str->Buffer = nullptr;
			str->MaximumLength = str->Length = 0;
		}
	}
}