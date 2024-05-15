#include "mainwindow.hpp"


CnoteWindow::CnoteWindow(QWidget *parent) :
    QWidget(parent) {
        menuBar = new QMenuBar(this);
        createMenus();
        //scrollBar = new QScrollBar(this);
        textEditor = new QTextEdit(this);
        // Layout settings
        setWindowTitle("&C++Note");
        resize(600, 400);
        //windowLayout = new QGridLayout(this);
        //windowLayout->addWidget(menuBar, 0, 0, 2, 3);
        //windowLayout->addWidget(textEditor, 1, 0, 2, 3);
        //windowLayout->addWidget(scrollBar, 1, 3);
        vbox = new QVBoxLayout(this);
        vbox->addWidget(menuBar);
        vbox->addWidget(textEditor);
}

void CnoteWindow::createMenus(){
    
    menuFile = menuBar->addMenu("&File");
    menuEdit = menuBar->addMenu("&Edit");

}