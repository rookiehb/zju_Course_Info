#ifndef TEXTEDITOR_SELF_H
#define TEXTEDITOR_SELF_H

#include <QMainWindow>
//#include "未来可能有的查找.h"
#include <QTextCharFormat>
#include "edit_self.h"
#include <QTextEdit>
#include <Qstring>
#include <QStack>
#include <QLineEdit>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCloseEvent>

namespace Ui {
class Texteditor_self;
}

class Texteditor_self : public QMainWindow
{
    Q_OBJECT
public:
    explicit Texteditor_self(QWidget *parent = nullptr);
    ~Texteditor_self();

    void closeEvent(QCloseEvent *event);

    QStack<QString> temp,store;
    int pin=0;//用于undo redo
    void ChangeFormat(const QTextCharFormat &mod);
    void mousePressEvent(QMouseEvent *event);
    void createActions();
    void createToolBars();
    QString pasteBoard;
    bool flag=false;

    private slots:
        void newWindow();
        void SaveFile();
        void LoadFile();
        void SaveasFile();
        void Undo();
        void Redo();
        void on_textEdit_textChanged(); //每次更新文本的时候压入栈temp
        void initstack();
        void showFindText();
        void searchText();
        void replaceThisText();
        void replaceAllText();




        void on_actionDel_triggered();

        void on_actionInsert_triggered();

        void on_actionCut_triggered();

        void on_action_triggered();

        void on_fu();

        void on_tie();



        void TextColor();
        void TextFont();
        void TextLeft();
        void TextRight();
        void TextJustify();
        void TextCenter();

    private:
        // Edit edit;
        Ui::Texteditor_self *ui;
        QString Test;
        QTextEdit *text_edit;

        QLineEdit *findLineEdit;
        QLineEdit *replaceLineEdit;
        QDialog *findDlg;
        QPushButton *btn;
        QVBoxLayout *layout;

        void UI_init();
        bool newFile;
        void save();
        void save(QString a);
        int SearchTextNum;

        QMenu *m_contextMenu;

        QString originalText;

        QToolBar *editToolBar;
        QToolBar *fmtToolBar;
        QAction *newAct;
        QAction *open;
        QAction *Save;
        QAction *saveAs;
        QAction *copy;
        QAction *paste;
        QAction *find;
        QAction *undo;
        QAction *redo;
        QAction *left;
        QAction *middle;
        QAction *right;
        QAction *just;
        QAction *font;
        QAction *color;
        QAction *insert;
        QAction *cut;
    };

#endif // TEXTEDITOR_SELF_H
