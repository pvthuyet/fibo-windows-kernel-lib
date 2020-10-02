#include "ke_scoped_unicode_string.h"
#include "ke_memory.h"
#include "ke_strutils.h"
#include "ke_utility.h"

namespace fibo::kernel
{
	ScopedUnicodeString::ScopedUnicodeString() :
		ScopedUnicodeString(PagedPool, 0)
	{
	}

	ScopedUnicodeString::ScopedUnicodeString(PCUNICODE_STRING src, POOL_TYPE type, ULONG tag) :
		ScopedUnicodeString(type, tag)
	{
		NT_ASSERT(src);
		auto status = allocate(src->MaximumLength);
		if (!NT_SUCCESS(status)) {
			ExRaiseStatus(STATUS_NO_MEMORY);
		}
		RtlCopyUnicodeString(&mUniStr, src);
	}

	ScopedUnicodeString::ScopedUnicodeString(USHORT numOfAllocBytes, PCUNICODE_STRING src, POOL_TYPE type, ULONG tag) :
		ScopedUnicodeString(type, tag)
	{
		NT_ASSERT(numOfAllocBytes > 0);
		auto status = allocate(numOfAllocBytes);
		if (!NT_SUCCESS(status)) {
			ExRaiseStatus(STATUS_NO_MEMORY);
		}
		RtlCopyUnicodeString(&mUniStr, src);
	}

	ScopedUnicodeString::ScopedUnicodeString(POOL_TYPE type, ULONG tag) :
		mUniStr{ 0 },
		mPoolType{ type },
		mTag{ tag }
	{
	}

	ScopedUnicodeString::~ScopedUnicodeString()
	{
		release();
	}

	bool ScopedUnicodeString::valid() const
	{
		return 0 != mUniStr.MaximumLength;
	}

	USHORT ScopedUnicodeString::length() const
	{
		return mUniStr.Length / sizeof(wchar_t);
	}

	PCUNICODE_STRING ScopedUnicodeString::get() const
	{
		return &mUniStr;
	}

	PUNICODE_STRING ScopedUnicodeString::get()
	{
		return &mUniStr;
	}

	NTSTATUS ScopedUnicodeString::copy(PCUNICODE_STRING src)
	{
		if (!valid()) {
			return STATUS_MEMORY_NOT_ALLOCATED;
		}
		RtlCopyUnicodeString(&mUniStr, src);

		return STATUS_SUCCESS;
	}

	NTSTATUS ScopedUnicodeString::append(PCWSTR src)
	{
		return RtlAppendUnicodeToString(&mUniStr, src);
	}

	NTSTATUS ScopedUnicodeString::append(PCUNICODE_STRING src)
	{
		return RtlAppendUnicodeStringToString(&mUniStr, src);
	}

	NTSTATUS ScopedUnicodeString::allocate(USHORT numOfBytes)
	{
		return allocate(numOfBytes, mPoolType, mTag);
	}

	NTSTATUS ScopedUnicodeString::allocate(USHORT numOfBytes, POOL_TYPE type, ULONG tag)
	{
		Memory::freeUnicodeString(&mUniStr, mTag);
		mPoolType = type;
		mTag = tag;
		USHORT algnSize = static_cast<USHORT>(Utility::aligned(numOfBytes));
		return Memory::allocateUnicodeString(&mUniStr, algnSize, type, tag);
	}

	VOID ScopedUnicodeString::release()
	{
		Memory::freeUnicodeString(&mUniStr, mTag);
	}
}