#pragma once

#include <memory>
#include <string_view>
#include <span>
class internal;

namespace simpleGUI{
	inline std::shared_ptr<internal> g_internal;
	void init();
	void init(int argc, char** argv);
	void exit();
	bool isRunning();
	void pollEvents();
	void render();
	void text(const std::string_view label);
	bool button(const std::string_view label);
	bool checkbox(const std::string_view label, bool* check);
	bool radioButton(const std::string_view label, int* v, int button_v);
	bool textInput(const std::string_view label, std::span<char> buf);;
	bool textInput(const std::string_view label, std::string& buf);
	bool combo(const std::string_view label, int* current_item, const std::span<const std::string_view> items);
	bool combo(const std::string_view label, int* current_item, const std::span<const char*> items);
	bool combo(const std::string_view label, int* current_item, const std::span<const std::string> items);
	bool combo(const std::string_view label, int* current_item, const char** items, unsigned int num_items);
	bool combo(const std::string_view label, int* current_item, std::initializer_list<const char*> items);

	void sameLine();
}
