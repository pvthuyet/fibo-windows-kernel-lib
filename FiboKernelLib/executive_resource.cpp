#include <ntddk.h>
#include "executive_resource.h"

namespace fibo::kernel
{
	ExecutiveResource::~ExecutiveResource()
	{
		ExDeleteResourceLite(&mResource);
	}

	void ExecutiveResource::init()
	{
		ExInitializeResourceLite(&mResource);
	}

	void ExecutiveResource::lock()
	{
		ExAcquireResourceExclusiveLite(&mResource, TRUE);
	}

	void ExecutiveResource::unlock()
	{
		ExReleaseResourceLite(&mResource);
	}

	void ExecutiveResource::lockShared()
	{
		ExAcquireResourceSharedLite(&mResource, TRUE);
	}

	void ExecutiveResource::unlockShared()
	{
		ExReleaseResourceLite(&mResource);
	}
}
