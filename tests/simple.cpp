#include <iostream>
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

		simpleGUI::render();
	}

	simpleGUI::exit();
}
