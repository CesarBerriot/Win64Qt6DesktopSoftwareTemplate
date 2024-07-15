//
// Created by César B. on 4/8/2024.
//

#include "utils/utils.hpp"
#include <windows.h>
#include <cassert>
#include <chrono>

int64_t utils::get_unix_time_ms()
{	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string utils::win32_strerror(DWORD error_code)
{	char * buffer;
	size_t buflen = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								   NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char *)&buffer, 0, NULL);
	assert(buflen);
	std::string res = buffer;
	HLOCAL LocalFree_res = LocalFree(buffer);
	assert(!LocalFree_res);
	return res;
}
