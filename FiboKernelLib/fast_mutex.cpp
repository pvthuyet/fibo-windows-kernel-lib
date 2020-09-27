#include <ntddk.h>
#include "fast_mutex.h"

namespace fibo::kernel
{
	void FastMutex::init()
	{
		ExInitializeFastMutex(&_mutex);
	}

	void FastMutex::lock()
	{
		ExAcquireFastMutex(&_mutex);
	}

	void FastMutex::unlock()
	{
		ExReleaseFastMutex(&_mutex);
	}
}