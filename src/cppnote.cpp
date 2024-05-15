/*
This is the main project file for the CPPNote project
*/
#include "ui/mainwindow.hpp"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    CnoteWindow window;
    window.show();

    return app.exec();
}