#pragma once

#include <memory>
class internal;

namespace simpleGUI{
	inline std::shared_ptr<internal> g_internal;
	void init();
	void init(int argc, char** argv);
	void exit();
	bool isRunning();
	void pollEvents();
	void render();
	void text(const std::string& label);
	bool button(const std::string& label);
	void checkbox(const std::string& label, bool* check);
}
