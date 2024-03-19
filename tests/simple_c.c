#include <stdio.h>
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

		simpleGUI_render();
	}

	simpleGUI_exit();
}
