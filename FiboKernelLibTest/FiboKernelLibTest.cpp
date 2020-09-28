#include "stdafx.h"
#include "FiboKernelLibTest.h"
#include "constant.h"
#include "ke_mutex.h"
#include "ke_logger.h"
#include "ke_wstring.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	LOGENTER;
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);
	LOGEXIT;
	return STATUS_SUCCESS;
}