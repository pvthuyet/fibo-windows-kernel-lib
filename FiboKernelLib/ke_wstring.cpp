#include <ntddk.h>
#include "ke_wstring.h"
#include "ke_utility.h"

namespace fibo::kernel
{
	constexpr size_t MAX_KE_WSTRING_LENGTH = MAX_UCSCHAR;

	KeWstring::KeWstring(const wchar_t* str, POOL_TYPE pool, ULONG tag) :
		KeWstring(str, 0, pool, tag)
	{
	}

	KeWstring::KeWstring(const wchar_t* str, size_t count, POOL_TYPE pool, ULONG tag) :
		mPoolType{ pool },
		mTag{ tag },
		mLen{ 0 },
		mCapacity{ 0 },
		mStr{ nullptr }
	{
		mLen = (0 == count) ? wcsnlen_s(str, MAX_KE_WSTRING_LENGTH) : count;
		if (mLen > 0)
		{
			mCapacity = Utility::minUpper(mLen);
			mStr = allocate(mCapacity, str, mLen);
			if (!mStr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}
		}
	}

	KeWstring::KeWstring(PCUNICODE_STRING str, POOL_TYPE pool, ULONG tag) :
		mPoolType{ pool },
		mTag{ tag },
		mLen{ 0 },
		mCapacity{ 0 },
		mStr{ nullptr }
	{
		mLen = str->Length / sizeof(wchar_t);
		if (mLen > 0)
		{
			mCapacity = Utility::minUpper(mLen);
			mStr = allocate(mCapacity, str->Buffer, mLen);
			if (!mStr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}
		}
	}

	KeWstring::KeWstring(const KeWstring& other) :
		mPoolType{ other.mPoolType },
		mTag{ other.mTag },
		mLen{ other.mLen },
		mCapacity{ other.mCapacity },
		mStr{ nullptr }
	{
		if (other.mLen > 0)
		{
			mStr = allocate(other.mCapacity, other.mStr, other.mLen);
			if (!mStr)
			{
				ExRaiseStatus(STATUS_NO_MEMORY);
			}
		}
	}

	KeWstring::KeWstring(KeWstring&& other) :
		mPoolType{ other.mPoolType },
		mTag{ other.mTag },
		mLen{ other.mLen },
		mCapacity{ other.mCapacity },
		mStr{ other.mStr }
	{
		// Reset other
		other.mLen = other.mCapacity = 0;
		other.mStr = nullptr;
	}

	KeWstring::~KeWstring()
	{
		release();
	}

	KeWstring& KeWstring::operator=(const KeWstring& other)
	{
		if (this != &other)
		{
			release();
			this->mPoolType = other.mPoolType;
			this->mTag = other.mTag;
			this->mLen = other.mLen;
			this->mCapacity = other.mCapacity;
			if (other.mLen > 0)
			{
				this->mStr = allocate(other.mCapacity, other.mStr, other.mLen);
				if (!this->mStr)
				{
					ExRaiseStatus(STATUS_NO_MEMORY);
				}
			}
		}
		return *this;
	}

	KeWstring& KeWstring::operator=(KeWstring&& other)
	{
		if (this != &other)
		{
			release();
			this->mPoolType = other.mPoolType;
			this->mTag = other.mTag;
			this->mLen = other.mLen;
			this->mCapacity = other.mCapacity;
			this->mStr = other.mStr;
			// Reset other
			other.mCapacity = other.mLen = 0;
			other.mStr = nullptr;
		}
		return *this;
	}

	KeWstring& KeWstring::operator+=(const KeWstring& other)
	{
		return append(other.mStr, other.mLen);
	}

	KeWstring& KeWstring::operator+=(PCWSTR str)
	{
		return append(str, 0);
	}

	bool KeWstring::operator==(const KeWstring& other) const
	{
		if (this != &other)
		{
			if (this->mLen != other.mLen)
			{
				return false;
			}

			if (0 == this->mLen)
			{
				return true;
			}

			return 0 == wcsncmp(this->mStr, other.mStr, this->mLen);
		}
		return true;
	}

	KeWstring::operator const wchar_t* () const
	{
		return this->mStr;
	}

	const wchar_t KeWstring::operator[](size_t index) const
	{
		return getAt(index);
	}

	wchar_t& KeWstring::operator[](size_t index)
	{
		return getAt(index);
	}

	const wchar_t* KeWstring::get() const
	{
		return this->mStr;
	}

	size_t KeWstring::length() const
	{
		return this->mLen;
	}

	KE_NODISCARD KeWstring KeWstring::toLower() const
	{
		KeWstring tmp(*this);
		_wcslwr_s(tmp.mStr, tmp.mLen);
		return tmp;
	}

	KeWstring& KeWstring::toLower()
	{
		_wcslwr_s(mStr, mLen);
		return *this;
	}

	KeWstring& KeWstring::truncate(size_t length)
	{
		if (mLen > length)
		{
			mLen = length;
			mStr[mLen] = L'\0';
		}
		return *this;
	}

	KeWstring& KeWstring::append(PCWSTR str, size_t count)
	{
		count = (0 == count) ? wcsnlen_s(str, MAX_KE_WSTRING_LENGTH) : count;
		if (count > 0)
		{
			NT_ASSERT(nullptr != str);
			auto newAlloc = false;
			auto newBuffer = mStr;
			auto newLen = mLen + count;
			auto newCapacity = mCapacity;

			if (newLen + 1 > mCapacity)
			{
				newCapacity = Utility::minUpper(newLen);
				newBuffer = allocate(newCapacity, mStr, mLen);
				newAlloc = true;
			}

			// copy 
			wcsncat_s(newBuffer, newCapacity, str, count);
			if (newAlloc)
			{
				release();
				this->mLen = newLen;
				this->mCapacity = newCapacity;
				this->mStr = newBuffer;
			}
		}
		return *this;
	}

	KE_NODISCARD const wchar_t KeWstring::getAt(size_t index) const
	{
		NT_ASSERT(mLen > index);
		return mStr[index];
	}

	wchar_t& KeWstring::getAt(size_t index)
	{
		NT_ASSERT(mLen > index);
		return mStr[index];
	}

	UNICODE_STRING* KeWstring::getUnicodeString(PUNICODE_STRING pUnicodeString) const
	{
		if (mStr) {
			RtlInitUnicodeString(pUnicodeString, mStr);
		}

		return pUnicodeString;
	}

	void KeWstring::release()
	{
		if (mStr)
		{
			ExFreePoolWithTag(mStr, mTag);
			mStr = nullptr;
			mCapacity = mLen = 0;
		}
	}

	KE_NODISCARD wchar_t* KeWstring::allocate(size_t newCount, const wchar_t* src, size_t count) const
	{
		NT_ASSERT(newCount > count);
		auto numOfBytes = newCount * sizeof(wchar_t);
		auto newStr = static_cast<wchar_t*>(ExAllocatePoolWithTag(mPoolType, numOfBytes, mTag));
		if (!newStr) {
			return nullptr;
		}

		RtlZeroMemory(newStr, numOfBytes);
		if (count > 0)
		{
			NT_ASSERT(nullptr != src);
			wcsncpy_s(newStr, newCount, src, count);
		}
		return newStr;
	}
}