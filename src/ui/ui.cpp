//
// Created by César B. on 4/8/2024.
//

#include "ui.hpp"
#include <QStatusBar>
#include <QMenuBar>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QFileDialog>
#include <QPushButton>
#include <QSpacerItem>
#include <QHeaderView>
#include <QWhatsThis>
#include <vector>
#include "utils/exceptions.hpp"
#include "globals/globals.hpp"

void ui::init()
{	int argc = 0;
	application = new QApplication(argc, nullptr);
	main_window::init();
	about_dialog::init();
	shortcuts_info_dialog::init();
}

void ui::main_window::init()
{	// main_window
	main_window = new QMainWindow;
	main_window->show();
	main_window->resize(size::w, size::h);
	// menu bar
	menu_bar::init();
	main_window->setMenuBar(menu_bar::menu_bar);
	// central widget
	central_widget::init();
	main_window->setCentralWidget(central_widget::central_widget);
	// status bar
	status_bar::init();
	main_window->setStatusBar(status_bar::status_bar);
}

void ui::main_window::menu_bar::init()
{	menu_bar = new QMenuBar;
	// file
	file_menu::init();
	menu_bar->addMenu(file_menu::file_menu);
	// themes
	themes_menu::init();
	menu_bar->addMenu(themes_menu::themes_menu);
	// help
	help_menu::init();
	menu_bar->addMenu(help_menu::help_menu);
	// ?
	help_context_mode_action = new QAction("?");
	QObject::connect(help_context_mode_action, &QAction::triggered, [] { on_help_context_mode_action_clicked(); });
	menu_bar->addAction(help_context_mode_action);
}

void ui::main_window::menu_bar::file_menu::init()
{	file_menu = new QMenu("&File");
	open_action = make_menu_action("&Open", std::string("Ctrl+O"), std::string("Sample Open File Dialog."), on_open_action_clicked, file_menu);
	export_action = make_menu_action("&Export", std::string("Ctrl+E"), std::string("Sample Export File Dialog."), on_export_action_clicked, file_menu);
	load_external_theme_action = make_menu_action("&Load External Theme", std::string("Ctrl+T"), std::string("Load an external theme from user storage."), on_load_external_theme_action_clicked, file_menu);
}

void ui::main_window::menu_bar::themes_menu::init()
{	themes_menu::themes_menu = new QMenu("&Themes");
}

void ui::main_window::menu_bar::themes_menu::clear()
{	themes_menu->clear();
}

void ui::main_window::menu_bar::themes_menu::create_category_menu(QMenu * parent, data_structures::theme_registry_category category)
{	QMenu * menu = new QMenu(make_string('&' << category.label).c_str());
	for(auto sub_category : category.sub_categories)
		create_category_menu(menu, sub_category);
	for(auto item : category.items)
		create_item_action(menu, item);
	parent->addMenu(menu);
}

void ui::main_window::menu_bar::themes_menu::create_item_action(QMenu * parent, data_structures::theme_registry_item item)
{	QAction * action = new QAction(make_string('&' << item.label).c_str());
	QObject::connect(action, &QAction::triggered, [item] { on_theme_action_clicked(item.resource_path); });
	parent->addAction(action);
}

void ui::main_window::menu_bar::help_menu::init()
{	help_menu = new QMenu("&Help");
	about_action = make_menu_action("&About", {}, {}, on_about_action_clicked, help_menu);
	shortcuts_info_action = make_menu_action("&Shortcuts", {}, {}, on_shortcuts_info_action_clicked, help_menu);
}

void ui::main_window::central_widget::init()
{	central_widget = new QWidget;
	layout = new QVBoxLayout;
	central_widget->setLayout(layout);
	counter::init();
	layout->addWidget(counter::counter);
}

void ui::main_window::central_widget::counter::init()
{	// container widget
	counter = new QWidget;
	// layout
	layout = new QVBoxLayout;
	counter->setLayout(layout);
	// label
	label = new QLabel;
	QFont font = QApplication::font();
	font.setPointSize(74);
	label->setFont(font);
	label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	label->setWhatsThis("A demo counter.");
	display_counter(globals::counter);
	layout->addWidget(label);
	// spacer
	spacer = new QSpacerItem(0, 20);
	layout->addItem(spacer);
	// button panel
	button_panel::init();
	layout->addWidget(button_panel::button_panel);
}

void ui::main_window::central_widget::counter::button_panel::init()
{	// container widget
	button_panel = new QWidget;
	// layout
	layout = new QHBoxLayout;
	layout->setAlignment(Qt::AlignTop);
	button_panel->setLayout(layout);
	// buttons
	auto make_button = [](QPushButton *& button, char const * text, char const * shortcut, char const * whats_this, templates::delegate<void()> & delegate)
	{	button = new QPushButton(text);
		QFont font = QApplication::font();
		font.setPointSize(24);
		button->setFont(font);
		QAction * action = new QAction;
		action->setShortcut(QKeySequence(shortcut));
		QObject::connect(action, &QAction::triggered, [&button] { button->click(); });
		main_window->addAction(action);
		button->setWhatsThis(whats_this);
		QObject::connect(button, &QPushButton::clicked, [&delegate] { delegate(); });
		layout->addWidget(button);
	};
	make_button(increase_button, "Increase Counter", "Ctrl+I", "Increases the counter.", on_increase_button_clicked);
	make_button(reset_button, "Reset Counter", "Ctrl+R", "Resets the counter.", on_reset_button_clicked);
}

void ui::main_window::status_bar::init()
{	status_bar = new QStatusBar;
	display("Ready.");
}

void ui::main_window::status_bar::display(std::string info)
{	status_bar->showMessage(QString::fromStdString(info));
}

void ui::about_dialog::init()
{	about_dialog = new QDialog(main_window::main_window);
	about_dialog->setModal(true);
	layout = new QVBoxLayout;
	label = new QLabel;
	layout->addWidget(label);
	about_dialog->setLayout(layout);
	// dialog
	about_dialog->setContentsMargins(QMargins() + 10);
	about_dialog->setWindowTitle("About");
	// layout
	layout->setSizeConstraint(QLayout::SetFixedSize);
	// label
	label->setOpenExternalLinks(true);
	label->setTextFormat(Qt::MarkdownText);
	label->setText(
		"# MyProject  \n"
		"Made with ♥ by César Berriot  \n"
		"<a style=color:blue; href=\"https://www.linkedin.com/in/c%C3%A9sar-berriot/\">LinkedIn</a> • "
		"<a style=color:blue; href=\"https://github.com/CesarBerriot\">Github</a> • "
		"<a style=color:blue; href=\"https://github.com/CesarBerriot/DllExportsViewer\">This project</a>"
	);
}

void ui::shortcuts_info_dialog::init()
{	shortcuts_info_dialog = new QDialog(main_window::main_window);
	shortcuts_info_dialog->setModal(true);
	layout = new QVBoxLayout;
	shortcuts_info_dialog->setLayout(layout);
	// dialog
	shortcuts_info_dialog->setContentsMargins(QMargins() + 10);
	shortcuts_info_dialog->setWindowTitle("Shortcuts");
	// layout
	layout->setSizeConstraint(QLayout::SetFixedSize);
	// shortcuts
	auto add_shortcut = [](char const * label, char const * key_sequence)
	{	QHBoxLayout * shortcut_layout = new QHBoxLayout;
		shortcut_layout->addWidget(new QLabel(label));
		shortcut_layout->addItem(new QSpacerItem(70, 0, QSizePolicy::MinimumExpanding));
		shortcut_layout->addWidget(new QLabel(key_sequence));
		layout->addLayout(shortcut_layout);
	};
	add_shortcut("Sample open file dialog", "Ctrl + O");
	add_shortcut("Sample export to file dialog", "Ctrl + E");
	add_shortcut("Load theme from user storage", "Ctrl + T");
	add_shortcut("Increase counter", "Ctrl + I");
	add_shortcut("Reset counter", "Ctrl + R");
}

QAction * ui::make_menu_action(std::string text, templates::optional<std::string> shortcut, templates::optional<std::string> whats_this, templates::delegate<void()> & delegate, QMenu * parent)
{	QAction * action = new QAction(QString::fromStdString(text));
	if(shortcut.is_set())
	{	action->setShortcut(QString::fromStdString(shortcut));
		action->setShortcutVisibleInContextMenu(true);
	}
	if(whats_this.is_set())
		action->setWhatsThis(QString::fromStdString(whats_this));
	QObject::connect(action, &QAction::triggered, [&delegate] { delegate(); });
	parent->addAction(action);
	return action;
}

void ui::display_counter(int counter)
{	std::string string = make_string(globals::counter.get());
	main_window::central_widget::counter::label->setText(QString::fromStdString(string));
}

void ui::create_sample_open_file_dialog(std::string filter, void (*callback)(std::string))
{	QString result = QFileDialog::getOpenFileName(ui::main_window::main_window, "Open File", QDir::homePath(), filter.c_str());
	if(result.length())
		callback(result.toStdString());
	else
		display_status("Sample import file dialog cancelled.");
}

void ui::create_sample_export_to_file_dialog(std::string filter, void (* callback)(std::string))
{	QString result = QFileDialog::getSaveFileName(ui::main_window::main_window, "Export to file", QDir::homePath(), filter.c_str());
	if(result.length())
		callback(result.toStdString());
	else
		display_status("Sample export file dialog cancelled.");
}

void ui::create_external_theme_open_dialog(void (* callback)(std::string))
{	QString result = QFileDialog::getOpenFileName(ui::main_window::main_window, "External Theme", QDir::homePath(), "*.qss");
	if(result.length())
		callback(result.toStdString());
	else
		display_status("External Theme import file dialog cancelled.");
}

void ui::enter_help_context_mode()
{	QWhatsThis::enterWhatsThisMode();
}

void ui::load_theme(std::string resource_path)
{	if(!resource_path.length())
	{	ui::main_window::main_window->setStyleSheet("");
		return;
	}
	QFile theme = QFile(resource_path.c_str());
	if(!theme.exists())
		throw utils::exception(EXIT_FAILURE, make_string("Failed to load a theme : '" << resource_path << '\''));
	theme.open(QIODevice::ReadOnly);
	main_window::main_window->setStyleSheet(theme.readAll());
	theme.close();
}

void ui::load_theme_registry(data_structures::theme_registry theme_registry)
{	namespace themes_menu = main_window::menu_bar::themes_menu;
	themes_menu::clear();
	for(auto category : theme_registry.categories)
		themes_menu::create_category_menu(themes_menu::themes_menu, category);
	for(auto item : theme_registry.global_items)
		themes_menu::create_item_action(themes_menu::themes_menu, item);
}

void ui::show_about_dialog()
{	about_dialog::about_dialog->show();
}

void ui::show_shortcuts_info_dialog()
{	shortcuts_info_dialog::shortcuts_info_dialog->show();
}
