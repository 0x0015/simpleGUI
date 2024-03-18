#include "window.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    simpleGUI gui;
    gui.show();

    app.exec();
}
