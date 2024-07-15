//
// Created by César B. on 4/11/2024.
//

#pragma once

#include <cstdint>
#include <windows.h>
#include <dbghelp.h>
#include <vector>
#include <cstdint>

namespace data_structures
{	struct theme_registry_item { std::string label; std::string resource_path; };
	struct theme_registry_category
	{	std::string label;
		std::vector<theme_registry_category> sub_categories;
		std::vector<theme_registry_item> items;
	};
	struct theme_registry
	{
		std::vector<theme_registry_category> categories;
		std::vector<theme_registry_item> global_items;
	};
}
