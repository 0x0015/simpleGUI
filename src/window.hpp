#pragma once

#include <QMainWindow>
#include <QCloseEvent>
#include <QVBoxLayout>

class internal;

class simpleGUIWindow : public QMainWindow
{
    Q_OBJECT

    void closeEvent(QCloseEvent* event) override;

public:
    simpleGUIWindow(QWidget* parent = nullptr);
    ~simpleGUIWindow();
    QLayout* layout;
    internal* parent;
};
