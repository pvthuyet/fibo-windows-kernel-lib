#include <ntddk.h>
#include "ke_wstring.h"
#include "ke_utility.h"
#include "ke_strutils.h"

namespace fibo::kernel
{
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
		mLen = (0 == count) ? StrUtils::length(str) : count;
		if (mLen > 0)
		{
			mCapacity = Utility::aligned((mLen + 1) * sizeof(wchar_t));
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
			mCapacity = Utility::aligned((mLen + 1) * sizeof(wchar_t));
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

			return StrUtils::equal(this->mStr, other.mStr, this->mLen);
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
		StrUtils::toLower(tmp.mStr, tmp.mLen + 1);
		return tmp;
	}

	KeWstring& KeWstring::toLower()
	{
		StrUtils::toLower(mStr, mLen + 1);
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
		count = (0 == count) ? StrUtils::length(str) : count;
		if (str && count > 0)
		{
			auto newAlloc = false;
			auto newBuffer = mStr;
			auto newLen = mLen + count;
			auto newCapacity = mCapacity;

			if (newLen + 1 > mCapacity)
			{
				newCapacity = Utility::aligned((newLen + 1) * sizeof(wchar_t));
				newBuffer = allocate(newCapacity, mStr, mLen);
				newAlloc = true;
			}

			// copy 
			StrUtils::ncat(newBuffer, newCapacity, str, count * sizeof(wchar_t));
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

	bool KeWstring::contain(const wchar_t* sstr, bool icase) const
	{
		auto sstrLen = StrUtils::length(sstr);
		if (sstrLen > mLen) {
			return false;
		}

		// Case is insensitive
		if (icase)
		{
			// Main string
			KeWstring lwstr(*this);
			lwstr.toLower();

			// Search string
			KeWstring lwsstr(sstr, sstrLen, mPoolType, mTag);
			lwsstr.toLower();

			return lwstr.contain(lwsstr, false);
		}

		// Case is sensitive
		return nullptr != StrUtils::substr(mStr, sstr);
	}

	bool KeWstring::contain(const KeWstring& sstr, bool icase) const
	{
		if (sstr.mLen > mLen) {
			return false;
		}

		// Case is insensitive
		if (icase)
		{
			// Main string
			KeWstring lwstr(*this);
			lwstr.toLower();

			// Search string
			KeWstring lwsstr(sstr);
			lwsstr.toLower();
			return lwstr.contain(lwsstr, false);
		}

		// Case is sensitive
		return nullptr != StrUtils::substr(mStr, sstr.mStr);
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

	KE_NODISCARD wchar_t* KeWstring::allocate(size_t numOfBytes, const wchar_t* src, size_t count) const
	{
		auto newStr = static_cast<wchar_t*>(ExAllocatePoolWithTag(mPoolType, numOfBytes, mTag));
		if (!newStr) {
			return nullptr;
		}

		RtlZeroMemory(newStr, numOfBytes);
		if (src)
		{
			auto bytesToCopy = (0 == count) ? StrUtils::lengthInbytes(src) : (count * sizeof(wchar_t));
			if (bytesToCopy > 0) {
				StrUtils::ncopy(newStr, numOfBytes, src, bytesToCopy);
			}
		}
		return newStr;
	}
}