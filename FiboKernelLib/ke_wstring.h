/*************************************************************************
*
* FIBO Library - Version 1.0 - September 1st, 2020
* @author thuyetvp@gmail.com
*
* Permission is hereby granted, free of charge, to any person or organization
* obtaining a copy of the software and accompanying documentation covered by
* this license (the "Software") to use, reproduce, display, distribute,
* execute, and transmit the Software, and to prepare derivative works of the
* Software, and to permit third-parties to whom the Software is furnished to
* do so, all subject to the following:
*
* The copyright notices in the Software and this entire statement, including
* the above license grant, this restriction and the following disclaimer,
* must be included in all copies of the Software, in whole or in part, and
* all derivative works of the Software, unless such copies or derivative
* works are solely in the form of machine-executable object code generated by
* a source language processor.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
* SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
* FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "ke_define.h"
#include "ke_constant.h"

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

		KE_NODISCARD KeWstring toLower() const;
		KeWstring& toLower();

		KeWstring& truncate(size_t length);
		KeWstring& append(PCWSTR str, size_t count = 0);

		KE_NODISCARD const wchar_t getAt(size_t index) const;
		wchar_t& getAt(size_t index);
		UNICODE_STRING* getUnicodeString(PUNICODE_STRING) const;

		bool contain(const KeWstring& sstr, bool icase = false) const;
		bool contain(PCUNICODE_STRING sstr, bool icase = false) const;
		bool contain(const wchar_t* sstr, size_t count = 0, bool icase = false) const;

		size_t find(const KeWstring& sstr, bool icase = false) const;
		size_t find(PCUNICODE_STRING sstr, bool icase = false) const;
		size_t find(const wchar_t* sstr, size_t count = 0, bool icase = false) const;

	private:
		KE_NODISCARD wchar_t* allocateAndAppend(size_t numOfBytes, const wchar_t* src = nullptr, size_t count = 0) const;
		void release();

	private:
		wchar_t* mStr{ nullptr };
		size_t mNumberOfElements{ 0 };	// Number of element of mStr. Not include null-terminated
		size_t mCapacity{ 0 };			// size of mStr in bytes
		POOL_TYPE mPoolType{ PagedPool };
		ULONG mTag{ 0 };
	};
}