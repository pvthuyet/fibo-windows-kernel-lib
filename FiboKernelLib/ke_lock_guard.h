#pragma once

namespace fibo::kernel
{
	template <typename T>
	struct LockGuard
	{
		LockGuard(T& mux) : mMux(mux)
		{
			mMux.lock();
		}

		~LockGuard()
		{
			mMux.unlock();
		}

	private:
		T& mMux;
	};
}