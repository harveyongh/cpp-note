#include "buttonbar.hpp"

CnoteButtonBar::CnoteButtonBar(QWidget *parent) :
    QWidget(parent){
        buttonBar = new QToolBar(this);
        createButtons();
        setIcons();
        setupToolbar();
    }

void CnoteButtonBar::createButtons(){
    buttonNew = new QToolButton(this);
    buttonOpen = new QToolButton(this);
    buttonSave = new QToolButton(this);
    buttonCut = new QToolButton(this);
    buttonCopy = new QToolButton(this);
    buttonPaste = new QToolButton(this);
    buttonUndo = new QToolButton(this);
    buttonRedo = new QToolButton(this);
}

void CnoteButtonBar::setIcons(){
    buttonNew->setIcon(QIcon(":/icons/file.svg"));
    buttonOpen->setIcon(QIcon(":/icons/folder-open.svg"));
    buttonSave->setIcon(QIcon(":/icons/floppy-disk.svg"));
    buttonCut->setIcon(QIcon(":/icons/scissors.svg"));
    buttonCopy->setIcon(QIcon(":/icons/copy.svg"));
    buttonPaste->setIcon(QIcon(":/icons/paste.svg"));
    buttonUndo->setIcon(QIcon(":/icons/rotate-left.svg"));
    buttonRedo->setIcon(QIcon(":/icons/rotate-right.svg"));
}