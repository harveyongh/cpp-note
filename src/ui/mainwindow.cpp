#include "mainwindow.hpp"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QCloseEvent>
#include <QToolButton>


CnoteWindow::CnoteWindow(QWidget *parent) :
    QWidget(parent) {
        menuBar = new QMenuBar(this);
        createActions();
        createMenus();
        textEditor = new QTextEdit(this);
        buttonBar = new QToolBar(this);
        createButtonBar();
        // Layout settings
        setWindowTitle("C++Note");
        resize(600, 400);
        vbox = new QVBoxLayout(this);
        vbox->addWidget(menuBar);
        vbox->addWidget(buttonBar);
        vbox->addWidget(textEditor);

        // External signals
        QObject::connect(buttonNew, &QToolButton::clicked,
            this, &CnoteWindow::newFile);
        QObject::connect(buttonOpen, &QToolButton::clicked,
            this, &CnoteWindow::openFile);
        QObject::connect(buttonSave, &QToolButton::clicked,
            this, &CnoteWindow::saveFile);
        QObject::connect(buttonCut, &QToolButton::clicked,
            textEditor, &QTextEdit::cut);
        QObject::connect(buttonCopy, &QToolButton::clicked,
            textEditor, &QTextEdit::copy);
        QObject::connect(buttonPaste, &QToolButton::clicked,
            textEditor, &QTextEdit::paste);
        QObject::connect(buttonUndo, &QToolButton::clicked,
            textEditor, &QTextEdit::undo);
        QObject::connect(buttonRedo, &QToolButton::clicked,
            textEditor, &QTextEdit::redo);

        QObject::connect(actionOpen, &QAction::triggered, 
            this, &CnoteWindow::openFile);
        QObject::connect(actionNew, &QAction::triggered,
            this, &CnoteWindow::newFile);
        QObject::connect(actionSave, &QAction::triggered,
            this, &CnoteWindow::saveFile);
        QObject::connect(actionSaveAs, &QAction::triggered,
            this, &CnoteWindow::saveFileAs);
        QObject::connect(actionPrint, &QAction::triggered,
            this, &CnoteWindow::printDocument);

        QObject::connect(textEditor, &QTextEdit::textChanged,
            this, &CnoteWindow::setChanged);

        QObject::connect(actionCut, &QAction::triggered, 
            textEditor, &QTextEdit::cut);
        QObject::connect(actionCopy, &QAction::triggered, 
            textEditor, &QTextEdit::copy);
        QObject::connect(actionPaste, &QAction::triggered, 
            textEditor, &QTextEdit::paste);
        QObject::connect(actionUndo, &QAction::triggered, 
            textEditor, &QTextEdit::undo);
        QObject::connect(actionRedo, &QAction::triggered, 
            textEditor, &QTextEdit::redo);
        QObject::connect(actionSelectAll, &QAction::triggered, 
            textEditor, &QTextEdit::selectAll);
}

void CnoteWindow::closeEvent(QCloseEvent *event){
    if (checkFileChanged){
        int discardChanges = confirmUnsaved();
        if (discardChanges != 2){
            event->accept();
        } else if (discardChanges == 2){
            event->ignore();
        }
    } else{
        event->accept();
    }
}

void CnoteWindow::createMenus(){
    menuFile = menuBar->addMenu("&File");
    menuEdit = menuBar->addMenu("&Edit");
    QList<QAction*> fileActions = {actionNew, actionOpen,
        actionSave, actionSaveAs, actionPrint};
    QList<QAction*> editActions = {actionCut, actionCopy,actionPaste, 
        actionUndo, actionRedo, actionSelectAll};

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
    actionSelectAll = new QAction ("&Select all", this);
}

void CnoteWindow::openFile(){
    if (checkFileChanged){
        int discardChanges = confirmUnsaved();
        if (discardChanges == 2){
            return;
        }
    }
    filename = QFileDialog::getOpenFileName(this,
        tr("Open Text File"), QDir::currentPath(), 
        tr("Text Files (*.txt *.rtf *.csv)"));
    QFile file(filename);

    if (file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream fileIn(&file);
        textEditor->setText(fileIn.readAll());
        checkFileChanged = false;
        file.close();
    }else{
        qWarning("Error opening selected file!");
    }
}

void CnoteWindow::saveFile(){
    if (checkFileChanged){
        QSaveFile file(filename);
        if (file.open(QFile::WriteOnly | QFile::Text)){
            QTextStream fileOut(&file);
            fileOut << textEditor->toPlainText();
            checkFileChanged = false;
            file.commit();
        }else{
            qWarning("Error saving to file!");
        }
    }
}

void CnoteWindow::saveFileAs(){
    QString saveAsName;
    saveAsName = QFileDialog::getSaveFileName(this,
        tr("Save current file as"), QDir::currentPath(), 
        tr("Text Files (*.txt *.rtf *.csv)"));
    if (saveAsName != ""){
        QSaveFile file(saveAsName);
        if (file.open(QFile::WriteOnly | QFile::Text)){
            QTextStream fileOut(&file);
            fileOut << textEditor->toPlainText();
            checkFileChanged = false;
            file.commit();
        }else{
            qWarning("Error saving to file!");
        }
    }else{
        qWarning("Error: invalid file chosen!");
    }
}

int CnoteWindow::confirmUnsaved(){
    QMessageBox confirmMsg;
    confirmMsg.setText("The document has unsaved changes.");
    confirmMsg.setInformativeText("Would you like to save first?");
    confirmMsg.setStandardButtons(QMessageBox::Save |
        QMessageBox::Discard | QMessageBox::Cancel);
    confirmMsg.setDefaultButton(QMessageBox::Save);
    int selection = confirmMsg.exec();

    switch (selection)
    {
    case QMessageBox::Save:
        saveFile();
        return 0;
        break;
    case QMessageBox::Discard:
        checkFileChanged = false;
        return 1;
        break;
    case QMessageBox::Cancel:
        return 2;
        break;
    default:
        // Not a valid option
        return 2;
        break;
    }
}

void CnoteWindow::printDocument(){
    QPrinter printer;
    QPrintDialog printDialog (&printer, this);
    if (printDialog.exec() == QDialog::Accepted){
        textEditor->print(&printer);
    }
    return;
}

void CnoteWindow::newFile(){
    if (checkFileChanged){
        int discardChanges = confirmUnsaved();
        if (discardChanges != 2){
            return;
        }
    }
    textEditor->setText("");
    filename = "";
    checkFileChanged = false;
}

void CnoteWindow::setChanged(){
    checkFileChanged = true;
}

void CnoteWindow::createButtonBar(){
    buttonNew = new QToolButton(this);
    buttonNew->setToolTip(tr("New file"));
    buttonOpen = new QToolButton(this);
    buttonOpen->setToolTip(tr("Open existing file"));
    buttonSave = new QToolButton(this);
    buttonSave->setToolTip(tr("Save file"));
    buttonCut = new QToolButton(this);
    buttonCut->setToolTip(tr("Cut selection"));
    buttonCopy = new QToolButton(this);
    buttonCopy->setToolTip(tr("Copy selection"));
    buttonPaste = new QToolButton(this);
    buttonPaste->setToolTip(tr("Paste from clipboard"));
    buttonUndo = new QToolButton(this);
    buttonUndo->setToolTip(tr("Undo last"));
    buttonRedo = new QToolButton(this);
    buttonRedo->setToolTip(tr("Redo last"));

    buttonBar->addWidget(buttonNew);
    buttonBar->addWidget(buttonOpen);
    buttonBar->addWidget(buttonSave);
    buttonBar->addSeparator();
    buttonBar->addWidget(buttonCut);
    buttonBar->addWidget(buttonCopy);
    buttonBar->addWidget(buttonPaste);
    buttonBar->addSeparator();
    buttonBar->addWidget(buttonUndo);
    buttonBar->addWidget(buttonRedo);

    buttonNew->setIcon(QIcon("../src/ui/icons/file.svg"));
    buttonOpen->setIcon(QIcon("../src/ui/icons/folder-open.svg"));
    buttonSave->setIcon(QIcon("../src/ui/icons/floppy-disk.svg"));
    buttonCut->setIcon(QIcon("../src/ui/icons/scissors.svg"));
    buttonCopy->setIcon(QIcon("../src/ui/icons/copy.svg"));
    buttonPaste->setIcon(QIcon("../src/ui/icons/paste.svg"));
    buttonUndo->setIcon(QIcon("../src/ui/icons/rotate-left.svg"));
    buttonRedo->setIcon(QIcon("../src/ui/icons/rotate-right.svg"));
}