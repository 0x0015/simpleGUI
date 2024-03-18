#pragma once
#include <memory>
#include "window.hpp"
#include <vector>
#include "widget.hpp"

class QApplication;

class internal{
public:
	~internal();
	std::shared_ptr<QApplication> app;
	std::shared_ptr<simpleGUIWindow> gui;
	bool running = false;
	std::vector<widget> widgets;
	void init(int argc, char** argv);
	void init();
	void exit();
	void pollEvents();
	void render();
	void text(const std::string& label);
	bool button(const std::string& label);
	void checkbox(const std::string& label, bool* check);

	int widgetCounter = -1;
	std::vector<char*> args;
	void sharedInit(int argc, char** argv);
};
