//
// Created by César B. on 4/8/2024.
//

#pragma once

#include <windows.h>
#include <dbghelp.h>
#include <vector>
#include "data_structures/data_structures.hpp"

namespace utils
{	/// returns time since epoch, in milliseconds
	int64_t get_unix_time_ms();
	/// strerror for win32 api errors
	std::string win32_strerror(DWORD);
}
