#include "mainwindow.hpp"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>


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
            this, &CnoteWindow::openFile);
        QObject::connect(actionNew, &QAction::triggered,
            this, &CnoteWindow::newFile);
        QObject::connect(actionSave, &QAction::triggered,
            this, &CnoteWindow::saveFile);
        QObject::connect(actionSaveAs, &QAction::triggered,
            this, &CnoteWindow::saveFileAs);

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
        break;
    }
}

void CnoteWindow::newFile(){
    if (checkFileChanged){
        int discardChanges = confirmUnsaved();
        if (discardChanges != 2){
            textEditor->setText("");
            filename = "";
            checkFileChanged = false;
        }
    }
    
}

void CnoteWindow::setChanged(){
    checkFileChanged = true;
}