/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *selectPersonButton;
    QPushButton *compareButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *exitButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(732, 576);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setFamilies({QString::fromUtf8("Fusion Pixel 10px M zh_hant")});
        font.setPointSize(16);
        font.setBold(false);
        label->setFont(font);
        label->setCursor(QCursor(Qt::ArrowCursor));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Fusion Pixel 10px M zh_hant")});
        groupBox->setFont(font1);
        groupBox->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(16, 16, -1, -1);
        selectPersonButton = new QPushButton(groupBox);
        selectPersonButton->setObjectName("selectPersonButton");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("FLOWERS")});
        font2.setPointSize(12);
        selectPersonButton->setFont(font2);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../tinf/public/icon/footLogo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        selectPersonButton->setIcon(icon);

        verticalLayout_2->addWidget(selectPersonButton);

        compareButton = new QPushButton(groupBox);
        compareButton->setObjectName("compareButton");
        compareButton->setEnabled(true);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Fixedsys")});
        font3.setPointSize(12);
        compareButton->setFont(font3);

        verticalLayout_2->addWidget(compareButton);


        verticalLayout->addWidget(groupBox);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName("exitButton");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Fixedsys")});
        font4.setPointSize(12);
        font4.setBold(true);
        exitButton->setFont(font4);
        exitButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #f44336;\n"
"    color: white;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #d32f2f;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #b71c1c;\n"
"}"));

        verticalLayout->addWidget(exitButton);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Welcome", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        label->setText(QCoreApplication::translate("MainWindow", "\350\226\207\343\201\256\345\256\207\345\256\231\357\274\201\357\274\201\357\274\201\357\274\201\357\274\201\357\274\201", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\347\224\237\346\227\245\345\277\253\344\271\220", nullptr));
        selectPersonButton->setText(QCoreApplication::translate("MainWindow", "ChooseYourGift", nullptr));
        compareButton->setText(QCoreApplication::translate("MainWindow", "\351\233\250\350\226\207\347\224\273\347\224\273\347\232\204\345\203\217\347\264\240\346\225\260\345\255\227\345\212\240\345\267\245\345\267\245\345\235\212(?)", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
