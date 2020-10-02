#pragma once

namespace fibo::kernel
{
	class ExecutiveResource
	{
	public:
		~ExecutiveResource();

		void init();
		void lock();
		void unlock();
		void lockShared();
		void unlockShared();

	private:
		ERESOURCE mResource;
	};
}