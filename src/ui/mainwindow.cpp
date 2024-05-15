#include "mainwindow.hpp"
#include <QDir>


CnoteWindow::CnoteWindow(QWidget *parent) :
    QWidget(parent) {
        menuBar = new QMenuBar(this);
        createActions();
        createMenus();
        textEditor = new QTextEdit(this);
        // Layout settings
        setWindowTitle("C++Note");
        resize(600, 400);
        vbox = new QVBoxLayout(this);
        vbox->addWidget(menuBar);
        vbox->addWidget(textEditor);

        QObject::connect(actionOpen, &QAction::triggered, 
            this, &CnoteWindow::open);
}

void CnoteWindow::createMenus(){
    menuFile = menuBar->addMenu("&File");
    menuEdit = menuBar->addMenu("&Edit");
    QList<QAction*> fileActions = {actionNew, actionOpen,
        actionSave, actionSaveAs, actionPrint};
    QList<QAction*> editActions = {actionCut, actionCopy,actionPaste, 
        actionUndo, actionRedo, actionDelete, actionSelectAll};

    menuFile->addActions(fileActions);
    menuEdit->addActions(editActions);
}

void CnoteWindow::createActions(){
    actionNew = new QAction ("&New", this);
    actionOpen = new QAction ("&Open", this);
    actionSave = new QAction ("&Save", this);
    actionSaveAs = new QAction ("&Save as", this);
    actionPrint = new QAction ("&Print", this);
    actionCut = new QAction ("&Cut", this);
    actionCopy = new QAction ("&Copy", this);
    actionPaste = new QAction ("&Paste", this);
    actionUndo = new QAction ("&Undo", this);
    actionRedo = new QAction ("&Redo", this);
    actionDelete = new QAction ("&Delete", this);
    actionSelectAll = new QAction ("&Select all", this);
}

void CnoteWindow::open(){
    filename = QFileDialog::getOpenFileName(this,
        tr("Open Text File"), QDir::currentPath(), 
        tr("Text Files (*.txt *.rtf *.csv)"));
    qInfo() << qPrintable(filename);
}