#include <iostream>
#include <vector>
#include "../src/simpleGUI.hpp"

int main(int argc, char** argv){
	simpleGUI::init(argc, argv);
	
	int elements = 1;

	while(simpleGUI::isRunning()){
		simpleGUI::pollEvents();

		for(int i=0;i<elements;i++)
			simpleGUI::text("Hello World!");

		if(simpleGUI::button("Add element"))
			elements++;
		if(simpleGUI::button("Remove element"))
			elements = std::max(elements-1, 1);

		simpleGUI::render();
		usleep(5000);//don't let it go too fast
	}

	simpleGUI::exit();
}
