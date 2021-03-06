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

namespace fibo::kernel
{
    //*****************************************************************
    class Mutex
    {
    public:
        void init();
        void lock();
        void unlock();

    private:
        KMUTEX _mutex;
    };

    //*****************************************************************
	class FastMutex
	{
	public:
		void init();
		void lock();
		void unlock();

	private:
		FAST_MUTEX _mutex;
	};

    //*****************************************************************
    class GuardedMutex
    {
    public:
        void init();
        void lock();
        void unlock();

    private:
        KGUARDED_MUTEX _mutex;
    };

    //*****************************************************************
    template <class _Mutex>
    class LockGuard 
    {
    public:
        using mutex_type = _Mutex;

        explicit LockGuard(_Mutex& _Mtx) : _MyMutex(_Mtx) 
        { 
            // construct and lock
            _MyMutex.lock();
        }

        ~LockGuard() 
        {
            _MyMutex.unlock();
        }

        LockGuard(const LockGuard&) = delete;
        LockGuard& operator=(const LockGuard&) = delete;

    private:
        _Mutex& _MyMutex;
    };
}