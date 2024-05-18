#include "buttonbar.hpp"

CnoteButtonBar::CnoteButtonBar(QWidget *parent) :
    QWidget(parent){
        buttonBar = new QToolBar(this);
        createButtons();
        setIcons();
        setupToolbar();
    }

void CnoteButtonBar::setupToolbar(){
    buttonBar = new QToolBar(this);
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
}

void CnoteButtonBar::createButtons(){
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