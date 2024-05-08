#include "mainwindow.hpp"
#include "../editor/texteditor.hpp"

using namespace cppnote;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), textEditor(new TextEditor(this))
{
}