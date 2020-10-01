#pragma once

#include <ntdef.h>

namespace fibo::kernel::KeMemory
{
	NTSTATUS allocateUnicodeString(_Inout_ PUNICODE_STRING str);
}

