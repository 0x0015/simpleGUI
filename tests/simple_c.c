#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../src/simpleGUI_C.h"

int main(int argc, char** argv){
	simpleGUI_init(argc, argv);

	int counter = 0;
	while(simpleGUI_isRunning()){
		simpleGUI_pollEvents();

		char textLabel[32];
		snprintf(textLabel, 32, "Hello World!%i", counter);
		simpleGUI_text(textLabel);
		counter++;

		if(simpleGUI_button("test button")){
			printf("Button pressed!\n");
			counter *= -1;
		}

		static bool check = true;
		simpleGUI_checkbox("checkbox", &check);

		static int e = 0;
		simpleGUI_radioButton("radio 0", &e, 0);
		simpleGUI_radioButton("radio 1", &e, 1);
		simpleGUI_radioButton("radio 2", &e, 2);
		simpleGUI_radioButton("radio 3", &e, 3);

		if(simpleGUI_button("Set state of checkbox and radio")){
			check = false;
			e = 0;
		}

		static char str[128] = "Hello World!";
		simpleGUI_textInput("text input", str, sizeof(str));

		if(simpleGUI_button("Print input text"))
			printf("%s\n", str);

		if(simpleGUI_button("Reset text input"))
			strcpy(str, "Hello World!");

		const char* items[] = {"item 1", "item 2", "item 3", "item 4"};

		static int currentItem = 0;
		simpleGUI_combo("combo input", &currentItem, items, SIMPLEGUI_ARRAYSIZE(items));

		if(simpleGUI_button("Set state of combo"))
			currentItem = 2;

		simpleGUI_render();
		usleep(5000);//don't let it go too fast
	}

	simpleGUI_exit();
}
