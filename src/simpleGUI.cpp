#include "simpleGUI.hpp"
#include "internal.hpp"
#include <vector>

void simpleGUI::init(){
	g_internal = std::make_shared<internal>();
	g_internal->init();
}

void simpleGUI::init(int argc, char** argv){
	g_internal = std::make_shared<internal>();
	g_internal->init(argc, argv);
}

bool simpleGUI::isRunning(){
	return g_internal->running;
}

void simpleGUI::pollEvents(){
	g_internal->pollEvents();
}

void simpleGUI::exit(){
	g_internal->exit();
}

void simpleGUI::render(){
	g_internal->render();
}

void simpleGUI::text(const std::string_view label){
	g_internal->text(label);
}

bool simpleGUI::button(const std::string_view label){
	return g_internal->button(label);
}

bool simpleGUI::checkbox(const std::string_view label, bool* check){
	return g_internal->checkbox(label, check);
}

bool simpleGUI::radioButton(const std::string_view label, int* v, int button_v){
	return g_internal->radioButton(label, v, button_v);
}

bool simpleGUI::textInput(const std::string_view label, std::span<char> buf){
	return g_internal->textInput(label, buf);
}

bool simpleGUI::textInput(const std::string_view label, std::string& buf){
	return g_internal->textInput(label, buf);
}

bool simpleGUI::combo(const std::string_view label, int* current_item, const std::span<const std::string_view> items){
	return g_internal->combo(label, current_item, items);
}

bool simpleGUI::combo(const std::string_view label, int* current_item, const std::span<const char*> items){
	return g_internal->combo(label, current_item, items);
}

bool simpleGUI::combo(const std::string_view label, int* current_item, const std::span<const std::string> items){
	return g_internal->combo(label, current_item, items);
}

bool simpleGUI::combo(const std::string_view label, int* current_item, const char** items, unsigned int num_items){
	return g_internal->combo(label, current_item, items, num_items);
}

bool simpleGUI::combo(const std::string_view label, int* current_item, std::initializer_list<const char*> items){
	//span<const char*> is messed up somehow; doesn't have a constructer for std::span<const char*> or std::span<std::string_view>
	return g_internal->combo(label, current_item, (const char**) std::data(items), (unsigned int)items.size());
}

void simpleGUI::sameLine(){
	g_internal->sameLine();
}

