#pragma once

#include "ke_define.h"

namespace fibo::kernel
{
	class KeWstring final
	{
	public:
		explicit KeWstring(const wchar_t* str, POOL_TYPE pool = PagedPool, ULONG tag = 0);
		KeWstring(const wchar_t* str, size_t count, POOL_TYPE pool = PagedPool, ULONG tag = 0);
		explicit KeWstring(PCUNICODE_STRING str, POOL_TYPE pool = PagedPool, ULONG tag = 0);
		KeWstring(const KeWstring& other);
		KeWstring(KeWstring&& other);
		~KeWstring();

		KeWstring& operator= (const KeWstring& other);
		KeWstring& operator=(KeWstring&& other);

		KeWstring& operator+=(const KeWstring& other);
		KeWstring& operator+=(PCWSTR str);

		bool operator==(const KeWstring& other) const;
		operator const wchar_t* () const;
		const wchar_t operator[](size_t index) const;
		wchar_t& operator[](size_t index);

		const wchar_t* get() const;
		size_t length() const;

		_NODISCARD KeWstring toLower() const;
		KeWstring& toLower();

		KeWstring& truncate(ULONG length);
		KeWstring& append(PCWSTR str, size_t count = 0);

		_NODISCARD const wchar_t getAt(size_t index) const;
		wchar_t& getAt(size_t index);
		UNICODE_STRING* getUnicodeString(PUNICODE_STRING) const;

		void release();

	private:
		_NODISCARD wchar_t* allocate(size_t newBufferSize, const wchar_t* src = nullptr, size_t srcLen = 0) const;

	private:
		wchar_t* mStr{ nullptr };
		size_t mLen{ 0 };
		size_t mCapacity{ 0 };
		POOL_TYPE mPoolType{ PagedPool };
		ULONG mTag{ 0 };
	};
}