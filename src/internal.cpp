#include "internal.hpp"
#include <QApplication>
#include <QVBoxLayout>

void internal::init(){
	const char* str = "null";
	char* ncstr = new char[strlen(str)];
	memcpy(ncstr, str, strlen(str));
	args = {ncstr};

	sharedInit(args.size(), args.data());
}

void internal::init(int argc, char** argv){
	args.resize(argc-1);
	for(int i=0;i<argc-1;i++){
		char* arg = new char[strlen(args[i])];
		memcpy(arg, argv[i], strlen(argv[i]));
		args[i] = arg;
	}

	sharedInit(args.size(), args.data());
}

void internal::sharedInit(int argc, char** argv){
	app = std::make_shared<QApplication>(argc, argv);
	gui = std::make_shared<simpleGUIWindow>();
	gui->parent = this;
	widgetPosInfo.layout = gui->layout;
	gui->show();

	widgetCounter = 0;
	running = true;
}

void internal::pollEvents(){
	app->processEvents();
}

#include <iostream>
void internal::render(){
	for(unsigned int i=widgetCounter;i<widgets.size();i++){
		std::cout<<"Destroying widget!"<<std::endl;
		gui->layout->removeWidget(widgets[i].widget);
	}
	widgets.resize(widgetCounter);
	widgetCounter = 0;
}

void internal::exit(){
	running = false;
	gui = nullptr;
	app = nullptr;
}

internal::~internal(){
	for(auto& o : args)
		delete[] o;
}

