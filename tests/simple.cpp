#include <iostream>
#include <vector>
#include "../src/simpleGUI.hpp"

int main(int argc, char** argv){
	simpleGUI::init(argc, argv);

	int counter = 0;
	while(simpleGUI::isRunning()){
		simpleGUI::pollEvents();

		simpleGUI::text("Hello World!" + std::to_string(counter));
		counter++;

		if(simpleGUI::button("test button")){
			std::cout<<"Button pressed!"<<std::endl;
			counter *= -1;
		}

		static bool check = true;
		simpleGUI::checkbox("checkbox", &check);

		static int e = 0;
		simpleGUI::radioButton("radio 0", &e, 0);
		simpleGUI::radioButton("radio 1", &e, 1);
		simpleGUI::radioButton("radio 2", &e, 2);
		simpleGUI::radioButton("radio 3", &e, 3);

		if(simpleGUI::button("Set state of checkbox and radio")){
			check = false;
			e = 0;
		}

		static std::string str = "Hello World!";
		simpleGUI::textInput("text input", str);

		if(simpleGUI::button("Print input text"))
			std::cout<<str<<std::endl;

		if(simpleGUI::button("Reset text input"))
			str = "Hello World!";

		static int currentItem = 0;
		simpleGUI::combo("combo input", &currentItem, {"item 1", "item 2", "item 3", "item 4"});

		if(simpleGUI::button("Set state of combo"))
			currentItem = 2;

		simpleGUI::render();
		usleep(5000);//don't let it go too fast
	}

	simpleGUI::exit();
}
