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
	void text(const std::string_view label);
	bool button(const std::string_view label);
	bool checkbox(const std::string_view label, bool* check);
	bool radioButton(const std::string_view label, int* v, int button_v);

	int widgetCounter = -1;
	std::vector<char*> args;
	void sharedInit(int argc, char** argv);
};
