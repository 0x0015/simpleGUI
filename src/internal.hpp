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
	struct widgetPositionInfo{
		QLayout* layout = nullptr;
		bool sameLine = false;
		bool wasLastSameLine = false;
	};
	widgetPositionInfo widgetPosInfo;

	void init(int argc, char** argv);
	void init();
	void exit();
	void pollEvents();
	void render();
	template<class T, uint32_t widget_type, class... Args> bool emplaceCorrectQWidget(const Args&... args);
	void text(const std::string_view label);
	bool button(const std::string_view label);
	bool checkbox(const std::string_view label, bool* check);
	bool radioButton(const std::string_view label, int* v, int button_v);
	bool textInput(const std::string_view label, std::span<char> buf);
	bool textInput(const std::string_view label, std::string& buf);
	bool combo(const std::string_view label, int* current_item, const std::span<const std::string_view> items);
	bool combo(const std::string_view label, int* current_item, const std::span<const char*> items);
	bool combo(const std::string_view label, int* current_item, const std::span<const std::string> items);
	bool combo(const std::string_view label, int* current_item, const char** items, unsigned int num_items);

	void sameLine();

	int widgetCounter = -1;
	std::vector<char*> args;
	void sharedInit(int argc, char** argv);

private:
	void applySameline();
};

#include "widgetEmplace.hpp"
