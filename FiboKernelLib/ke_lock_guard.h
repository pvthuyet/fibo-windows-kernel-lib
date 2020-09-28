#pragma once

namespace fibo::kernel
{
	template <class MutexType>
	struct LockGuard
	{
		explicit LockGuard(const LockGuard&) = delete;

		LockGuard(MutexType& mux) : mMux(mux)
		{
			mMux.lock();
		}

		~LockGuard()
		{
			mMux.unlock();
		}

	private:
		MutexType& mMux;
	};
}