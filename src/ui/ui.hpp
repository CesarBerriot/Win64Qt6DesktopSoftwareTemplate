//
// Created by César B. on 4/8/2024.
//

#pragma once

class QApplication;
class QMainWindow;
class QMenuBar;
class QMenu;
class QAction;
class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QStatusBar;
class QStatusBar;
class QPushButton;
class QSpacerItem;
class QDialog;

#include <string>
#include "templates/delegate.hpp"
#include "templates/optional.hpp"
#include "utils/utils.hpp"

namespace ui
{	void init();
	inline QApplication * application;
	namespace main_window
	{	void init();
		namespace size { enum { w = 600, h = 400 }; }
		inline QMainWindow * main_window;
		namespace menu_bar
		{	void init();
			inline QMenuBar * menu_bar;
			namespace file_menu
			{	void init();
				inline QMenu * file_menu;
				inline QAction * open_action;
				inline QAction * export_action;
				inline QAction * load_external_theme_action;
				inline templates::delegate<void()> on_open_action_clicked;
				inline templates::delegate<void()> on_export_action_clicked;
				inline templates::delegate<void()> on_load_external_theme_action_clicked;
			}
			namespace themes_menu
			{	void init();
				void clear();
				void create_category_menu(QMenu * parent, data_structures::theme_registry_category);
				void create_item_action(QMenu * parent, data_structures::theme_registry_item);
				inline QMenu * themes_menu;
				inline templates::delegate<void(std::string resource_path)> on_theme_action_clicked;
			}
			namespace help_menu
			{	void init();
				inline QMenu * help_menu;
				inline QAction * about_action;
				inline QAction * shortcuts_info_action;
				inline templates::delegate<void()> on_about_action_clicked;
				inline templates::delegate<void()> on_shortcuts_info_action_clicked;
			}
			inline QAction * help_context_mode_action;
			inline templates::delegate<void()> on_help_context_mode_action_clicked;
		}
		namespace central_widget
		{	void init();
			inline QWidget * central_widget;
			inline QVBoxLayout * layout;
			namespace counter
			{	void init();
				inline QWidget * counter;
				inline QVBoxLayout * layout;
				inline QLabel * label;
				inline QSpacerItem * spacer;
				namespace button_panel
				{	void init();
					inline QWidget * button_panel;
					inline QHBoxLayout * layout;
					inline QPushButton * increase_button;
					inline QPushButton * reset_button;
					inline templates::delegate<void()> on_increase_button_clicked;
					inline templates::delegate<void()> on_reset_button_clicked;
				}
			}
		}
		namespace status_bar
		{	void init();
			inline QStatusBar * status_bar;
			void display(std::string);
		}
	}
	namespace about_dialog
	{	void init();
		inline QDialog * about_dialog;
		inline QVBoxLayout * layout;
		inline QLabel * label;
	}
	namespace shortcuts_info_dialog
	{	void init();
		inline QDialog * shortcuts_info_dialog;
		inline QVBoxLayout * layout;
	}
	QAction * make_menu_action(std::string text, templates::optional<std::string> shortcut, templates::optional<std::string> whats_this, templates::delegate<void()> & delegate, QMenu * parent);
	void display_counter(int counter);
	inline void display_status(std::string info) { main_window::status_bar::display(info); }
	void create_sample_open_file_dialog(std::string filter /* = "*.txt" */, void(*callback)(std::string));
	void create_sample_export_to_file_dialog(std::string filter /* = "*.json" */, void(*callback)(std::string));
	void create_external_theme_open_dialog(void(*callback)(std::string));
	void enter_help_context_mode();
	void load_theme(std::string resource_path);
	void load_theme_registry(data_structures::theme_registry);
	void show_about_dialog();
	void show_shortcuts_info_dialog();
}
