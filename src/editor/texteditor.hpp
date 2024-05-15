#include <QTextEdit>


class CnoteTextEditor : public QTextEdit
{
    Q_OBJECT
    public:
        CnoteTextEditor(QTextEdit *parent);
    
    private slots:
        //QTextEdit is capable of handling these behaviors...
        //To test if these slots are needed for anything
        //void cut();
        //void copy();
        //void paste();
        //void selectAll();
        //void del();// Shortened name for delete prevents conflict
        //void undo();
        //void redo();
};

