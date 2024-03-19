#ifndef SIMPLEGUI_C_H
#define SIMPLEGUI_C_H

#ifdef __cplusplus
extern "C"{
#else
#include <stdbool.h>
#endif

void simpleGUI_init(int argc, char** argv);
void simpleGUI_exit();
bool simpleGUI_isRunning();
void simpleGUI_pollEvents();
void simpleGUI_render();
void simpleGUI_text(const char* label);
bool simpleGUI_button(const char* label);
bool simpleGUI_checkbox(const char* label, bool* check);
bool simpleGUI_radioButton(const char* label, int* v, int button_v);

#ifdef __cplusplus
}
#endif

#endif
