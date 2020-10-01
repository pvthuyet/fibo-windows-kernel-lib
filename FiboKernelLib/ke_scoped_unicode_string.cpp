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

	PCUNICODE_STRING ScopedUnicodeString::get() const
	{
		return &mUniStr;
	}

	PUNICODE_STRING ScopedUnicodeString::get()
	{
		return &mUniStr;
	}

	VOID ScopedUnicodeString::copy(PCUNICODE_STRING src)
	{
		return RtlCopyUnicodeString(&mUniStr, src);
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