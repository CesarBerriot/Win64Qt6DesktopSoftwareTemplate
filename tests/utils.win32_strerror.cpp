#include <iostream>
#include <windows.h>
#include "utils/utils.hpp"

int main()
{	std::string error_success_str = utils::win32_strerror(ERROR_SUCCESS);
	bool matches = !error_success_str.compare("The operation completed successfully.\r\n");
	return matches ? EXIT_SUCCESS : EXIT_FAILURE;
}