//
// Created by César B. on 4/8/2024.
//

#include "logic.hpp"
#include <QApplication>
#include <QShortcut>
#include <QMainWindow>
#include <libgen.h>
#include "ui/ui.hpp"
#include "globals/globals.hpp"

void logic::init()
{	globals::counter.on_value_changed.bind([](int value) { ui::display_counter(value); });
}

void logic::bind_ui_elements()
{	ui::main_window::menu_bar::file_menu::on_open_action_clicked.bind([] { ui::create_sample_open_file_dialog("*.txt", open_file_callback); });
	ui::main_window::menu_bar::file_menu::on_export_action_clicked.bind([] { ui::create_sample_export_to_file_dialog("*.json", export_to_file_callback); });
	ui::main_window::menu_bar::file_menu::on_load_external_theme_action_clicked.bind([] { ui::create_external_theme_open_dialog(ui::load_theme); });
	ui::main_window::menu_bar::themes_menu::on_theme_action_clicked.bind(ui::load_theme);
	ui::main_window::menu_bar::help_menu::on_about_action_clicked.bind(ui::show_about_dialog);
	ui::main_window::menu_bar::help_menu::on_shortcuts_info_action_clicked.bind(ui::show_shortcuts_info_dialog);
	ui::main_window::menu_bar::on_help_context_mode_action_clicked.bind(ui::enter_help_context_mode);
	ui::main_window::central_widget::counter::button_panel::on_increase_button_clicked.bind(increase_counter);
	ui::main_window::central_widget::counter::button_panel::on_reset_button_clicked.bind(reset_counter);
}

void logic::load_themes()
{	ui::load_theme(globals::default_theme);
	ui::load_theme_registry(globals::theme_registry);
}

void logic::increase_counter()
{	globals::counter = globals::counter + 1;
	ui::display_status(make_string("Increased counter by one. New value : " << globals::counter.get() << '.'));
}

void logic::reset_counter()
{	globals::counter = 0;
	ui::display_status("Reset counter to zero.");
}

void logic::open_file_callback(std::string path)
{	char * filename = basename((char *)path.c_str());
	ui::display_status(make_string("Opened file : '" << filename << '\''));
}

void logic::export_to_file_callback(std::string path)
{	char * filename = basename((char *)path.c_str());
	ui::display_status(make_string("Exported to file : '" << filename << '\''));
}

int logic::run()
{	return QApplication::exec();
}
