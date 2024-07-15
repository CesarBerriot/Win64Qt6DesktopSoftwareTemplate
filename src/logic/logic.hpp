//
// Created by César B. on 4/8/2024.
//

#pragma once

#include <string>

namespace logic
{	void init();
	void bind_ui_elements();
	void load_themes();
	void increase_counter();
	void reset_counter();
	void open_file_callback(std::string path);
	void export_to_file_callback(std::string path);
	/// called post-initialization, runs the Qt application
	int run();
}
