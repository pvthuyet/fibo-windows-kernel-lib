#include "ke_memory.h"
#include <ntddk.h>

namespace fibo::kernel::Memory
{
	_Use_decl_annotations_
	NTSTATUS allocateUnicodeString(_Inout_ PUNICODE_STRING str,
			_In_ size_t numOfBytes,
			_In_ POOL_TYPE type,
			_In_ ULONG tag)
	{
		if (!str || 0 == numOfBytes) {
			return STATUS_INVALID_PARAMETER;
		}

		numOfBytes = min(numOfBytes, UNICODE_STRING_MAX_BYTES); // Limit the memory for unicode_string
		str->Buffer = static_cast<PWCH>(ExAllocatePoolWithTag(type, numOfBytes, tag));
		if (nullptr == str->Buffer) {
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		RtlZeroMemory(str->Buffer, numOfBytes);
		str->Length = 0;
		str->MaximumLength = static_cast<USHORT>(numOfBytes);
		return STATUS_SUCCESS;
	}

	_Use_decl_annotations_
	VOID freeUnicodeString(_Inout_ PUNICODE_STRING str, _In_ ULONG tag)
	{
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