#include "ke_memory.h"
#include <ntddk.h>

namespace fibo::kernel::KeMemory
{
	NTSTATUS allocateUnicodeString(_Inout_ PUNICODE_STRING str)
	{
		UNREFERENCED_PARAMETER(str);
		return STATUS_SUCCESS;
	}
}