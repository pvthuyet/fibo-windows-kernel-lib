#include <ntddk.h>
#include "ke_mutex.h"

namespace fibo::kernel
{
	//*****************************************************************
	// Mutex implement
	void Mutex::init()
	{
		KeInitializeMutex(&_mutex, 0);
	}

	void Mutex::lock()
	{
		KeWaitForSingleObject(&_mutex, Executive, KernelMode, FALSE, nullptr);
	}

	void Mutex::unlock()
	{
		KeReleaseMutex(&_mutex, FALSE);
	}

	//*****************************************************************
	// FastMutex implement
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

	//*****************************************************************
	// GuardedMutex implement
	void GuardedMutex::init()
	{
		KeInitializeGuardedMutex(&_mutex);
	}

	void GuardedMutex::lock()
	{
		KeAcquireGuardedMutex(&_mutex);
	}

	void GuardedMutex::unlock()
	{
		KeReleaseGuardedMutex(&_mutex);
	}
}