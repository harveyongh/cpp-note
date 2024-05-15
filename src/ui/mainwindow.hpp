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

class CnoteWindow : public QWidget
{
    Q_OBJECT
    public:
        CnoteWindow(QWidget *parent = nullptr);
    private:
        QString filename = "";
        void openDocument(QString filename);
        void saveDocument(QString filename);
    protected:
        //void closeEvent(QCloseEvent *event) override;
    private slots:
        //void print();
        void open();
        //void save(QString filename);// Handles save and save as
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
        bool confirmUnsaved();
    private:
        QTextEdit *textEditor;
        QTextDocument *loadedDoc;
        QVBoxLayout *vbox;
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
        QAction *actionDelete;
        QAction *actionSelectAll;
};

#endif // MAINWINDOW_HPP
