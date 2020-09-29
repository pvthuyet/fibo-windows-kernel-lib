#include "ke_filename_info.h"

namespace fibo::kernel
{
	FilterFileNameInfo::FilterFileNameInfo(PFLT_CALLBACK_DATA data, FileNameOptions options)
	{
		auto status = FltGetFileNameInformation(data, static_cast<FLT_FILE_NAME_OPTIONS>(options), &mInfo);
		if (!NT_SUCCESS(status)) {
			mInfo = nullptr;
		}
	}

	FilterFileNameInfo::~FilterFileNameInfo()
	{
		if (mInfo) {
			FltReleaseFileNameInformation(mInfo);
			mInfo = nullptr;
		}
	}

	FilterFileNameInfo::operator bool() const
	{
		return nullptr != mInfo;
	}

	FilterFileNameInfo::operator PFLT_FILE_NAME_INFORMATION() const
	{
		return get();
	}

	PFLT_FILE_NAME_INFORMATION FilterFileNameInfo::operator->()
	{
		return mInfo;
	}

	PFLT_FILE_NAME_INFORMATION FilterFileNameInfo::get() const
	{
		return mInfo;
	}

	NTSTATUS FilterFileNameInfo::parse()
	{
		return FltParseFileNameInformation(mInfo);
	}
}