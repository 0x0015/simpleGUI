#include "window.hpp"
#include "internal.hpp"
#include <iostream>

simpleGUIWindow::simpleGUIWindow(QWidget* parent) : QMainWindow(parent){
    //Since this is a QMainWindow we cannot set a layout,
    //we can only set a central widget.
    auto centralWidget = new QWidget(this);

    //Since setting a layout on QMainWindow is not allowed,
    //this layout is used in centralWidget instead.
    layout = new QVBoxLayout();

    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);

}

void simpleGUIWindow::closeEvent(QCloseEvent* event){
	parent->running = false;
}

simpleGUIWindow::~simpleGUIWindow(){
	parent->running = false;
}
