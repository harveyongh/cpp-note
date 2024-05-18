#ifndef BUTTONBAR_HPP
#define BUTTONBAR_HPP

#include <QToolButton>
#include <QToolBar>

class CnoteButtonBar : public QWidget
{
    Q_OBJECT
    public:
        CnoteButtonBar(QWidget *parent);

    private:
        void createButtons();

        QToolBar *buttonBar;

        QToolButton *buttonNew;
        QToolButton *buttonOpen;
        QToolButton *buttonSave;

        QToolButton *buttonCut;
        QToolButton *buttonCopy;
        QToolButton *buttonPaste;
        QToolButton *buttonUndo;
        QToolButton *buttonRedo;

};

#endif //BUTTONBAR_HPP