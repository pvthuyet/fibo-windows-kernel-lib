#pragma once

#include <fltKernel.h>

namespace fibo::kernel
{
	enum class FileNameOptions
	{
		Normalized	= FLT_FILE_NAME_NORMALIZED,
		Opened		= FLT_FILE_NAME_OPENED,
		Short		= FLT_FILE_NAME_SHORT,

		QueryDefault		= FLT_FILE_NAME_QUERY_DEFAULT,
		QueryCacheOnly		= FLT_FILE_NAME_QUERY_CACHE_ONLY,
		QueryFileSystemOnly = FLT_FILE_NAME_QUERY_FILESYSTEM_ONLY,

		RequestFromCurrentProvider	= FLT_FILE_NAME_REQUEST_FROM_CURRENT_PROVIDER,
		DoNotCache					= FLT_FILE_NAME_DO_NOT_CACHE,
		AllowQueryOnReparse			= FLT_FILE_NAME_ALLOW_QUERY_ON_REPARSE
	};
	DEFINE_ENUM_FLAG_OPERATORS(FileNameOptions);

	class FilterFileNameInfo
	{
	public:
		FilterFileNameInfo(PFLT_CALLBACK_DATA data, 
			FileNameOptions options = FileNameOptions::QueryDefault | FileNameOptions::Normalized);
		~FilterFileNameInfo();

		operator bool() const;
		operator PFLT_FILE_NAME_INFORMATION() const;
		PFLT_FILE_NAME_INFORMATION operator->();

		PFLT_FILE_NAME_INFORMATION get() const;
		NTSTATUS parse();

	private:
		PFLT_FILE_NAME_INFORMATION mInfo{ nullptr };
	};
}
