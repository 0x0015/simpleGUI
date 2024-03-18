#include "simpleGUI.hpp"
#include "internal.hpp"

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

void simpleGUI::text(const std::string& label){
	g_internal->text(label);
}

bool simpleGUI::button(const std::string& label){
	return g_internal->button(label);
}

void simpleGUI::checkbox(const std::string& label, bool* check){
	g_internal->checkbox(label, check);
}


