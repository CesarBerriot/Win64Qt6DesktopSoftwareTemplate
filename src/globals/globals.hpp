//
// Created by César B. on 4/11/2024.
//

#pragma once

#include "data_structures/data_structures.hpp"
#include "templates/trackable_value.hpp"

namespace globals
{	inline std::string default_theme = ":/RC_THEMES/Jaime Quiroga/Aqua.qss";
	extern data_structures::theme_registry theme_registry;
	inline templates::trackable_value<int> counter = 0;
}
