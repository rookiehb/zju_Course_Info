#include "texteditor_self.h"
#include <QApplication>
#include <stack>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Texteditor_self w;
    w.show();

    return a.exec();
}
