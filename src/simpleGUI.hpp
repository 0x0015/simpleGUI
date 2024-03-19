#pragma once

#include <memory>
#include <string_view>
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
}
