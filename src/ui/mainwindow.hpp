#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QAction>
#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include <QScrollBar>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <string>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(const QString &title, QWidget *parent);

    protected:
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void print();
        void open();
        void save(std::string="");// Handles save and save as
        void cut();
        void copy();
        void paste();
        void selectAll();
        void del();// Shortened name for delete prevents conflict
        void undo();
        void redo();
    
    private:
        void createActions();
        void createMenus();
        bool confirmUnsaved();

    private:
        QTextEdit *textEditor;
        QScrollBar *scrollBar;
        QStatusBar *statusBar;

        QMenu *menuFile;
        QMenu *menuEdit;

        QAction actionNew;
        QAction actionOpen;
        QAction actionSave;
        QAction actionSaveAs;
        QAction actionPrint;
        QAction actionCut;
        QAction actionCopy;
        QAction actionPaste;
        QAction actionUndo;
        QAction actionRedo;
        QAction actionDelete;
        QAction actionSelectAll;

};

#endif // MAINWINDOW_H_
