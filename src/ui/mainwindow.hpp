#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QAction>
#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include <QScrollBar>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QString>
#include <string>
#include <QTextDocument>
#include <QFile>
#include <QSaveFile>
#include <QLayout>
#include <QList>
#include <QToolBar>
#include <QToolButton>

class CnoteWindow : public QWidget
{
    Q_OBJECT
    public:
        CnoteWindow(QWidget *parent = nullptr);
    private:
        QString filename = "";
        bool checkFileChanged = false;
    protected:
        void closeEvent(QCloseEvent *event) override;
    private slots:
        void printDocument();
        void setChanged();
        void openFile();
        void newFile();
        void saveFile();// Handles save and save as
        void saveFileAs();
    signals:
        // Signals sent to editor from menu
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
        void createButtonBar();
        int confirmUnsaved();
    private:
        QToolBar *buttonBar;
        QTextEdit *textEditor;
        QTextDocument *loadedDoc;
        QVBoxLayout *vbox;
        QDialog *confirmUnsavedDialog;
        QMenu *menuFile;
        QMenu *menuEdit;
        QMenuBar *menuBar;
        QAction *actionNew;
        QAction *actionOpen;
        QAction *actionSave;
        QAction *actionSaveAs;
        QAction *actionPrint;
        QAction *actionCut;
        QAction *actionCopy;
        QAction *actionPaste;
        QAction *actionUndo;
        QAction *actionRedo;
        QAction *actionSelectAll;
        QToolButton *buttonNew;
        QToolButton *buttonOpen;
        QToolButton *buttonSave;
        QToolButton *buttonCut;
        QToolButton *buttonCopy;
        QToolButton *buttonPaste;
        QToolButton *buttonUndo;
        QToolButton *buttonRedo;
};

#endif // MAINWINDOW_HPP
