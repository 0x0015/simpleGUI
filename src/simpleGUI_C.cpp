#include "simpleGUI_C.h"
#include "simpleGUI.hpp"

void simpleGUI_init(int argc, char** argv){
	if(argc == 0 || !argv)
		simpleGUI::init();
	else
		simpleGUI::init(argc, argv);
}

void simpleGUI_exit(){
	simpleGUI::exit();
}

bool simpleGUI_isRunning(){
	return simpleGUI::isRunning();
}

void simpleGUI_pollEvents(){
	simpleGUI::pollEvents();
}

void simpleGUI_render(){
	simpleGUI::render();
}

void simpleGUI_text(const char* label){
	simpleGUI::text(label);
}

bool simpleGUI_button(const char* label){
	return simpleGUI::button(label);
}

bool simpleGUI_checkbox(const char* label, bool* check){
	return simpleGUI::checkbox(label, check);
}

bool simpleGUI_radioButton(const char* label, int* v, int button_v){
	return simpleGUI::radioButton(label, v, button_v);
}

bool simpleGUI_textInput(const char* label, char* buf, unsigned int bufSize){
	return simpleGUI::textInput(label, std::span<char>(buf, bufSize));
}
