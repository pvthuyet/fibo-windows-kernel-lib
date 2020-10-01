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