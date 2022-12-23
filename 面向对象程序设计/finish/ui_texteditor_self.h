/********************************************************************************
** Form generated from reading UI file 'texteditor_self.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDITOR_SELF_H
#define UI_TEXTEDITOR_SELF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "edit_self.h"

QT_BEGIN_NAMESPACE

class Ui_Texteditor_self
{
public:
    QWidget *centralWidget;
    Edit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Texteditor_self)
    {
        if (Texteditor_self->objectName().isEmpty())
            Texteditor_self->setObjectName(QStringLiteral("Texteditor_self"));
        Texteditor_self->resize(672, 470);
        centralWidget = new QWidget(Texteditor_self);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textEdit = new Edit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 671, 411));
        Texteditor_self->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Texteditor_self);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 672, 22));
        Texteditor_self->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Texteditor_self);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Texteditor_self->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Texteditor_self);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Texteditor_self->setStatusBar(statusBar);

        retranslateUi(Texteditor_self);

        QMetaObject::connectSlotsByName(Texteditor_self);
    } // setupUi

    void retranslateUi(QMainWindow *Texteditor_self)
    {
        Texteditor_self->setWindowTitle(QApplication::translate("Texteditor_self", "Texteditor_self", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Texteditor_self: public Ui_Texteditor_self {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTEDITOR_SELF_H
