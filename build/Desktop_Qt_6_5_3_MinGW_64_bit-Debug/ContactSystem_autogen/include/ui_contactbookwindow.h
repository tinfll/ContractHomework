/********************************************************************************
** Form generated from reading UI file 'contactbookwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTBOOKWINDOW_H
#define UI_CONTACTBOOKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContactBookWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *searchLayout;
    QComboBox *searchTypeComboBox;
    QLineEdit *searchInput;
    QPushButton *searchButton;
    QPushButton *resetButton;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *addContactButton;
    QLabel *countLabel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *backButton;

    void setupUi(QMainWindow *ContactBookWindow)
    {
        if (ContactBookWindow->objectName().isEmpty())
            ContactBookWindow->setObjectName("ContactBookWindow");
        ContactBookWindow->resize(600, 500);
        centralwidget = new QWidget(ContactBookWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        searchTypeComboBox = new QComboBox(centralwidget);
        searchTypeComboBox->addItem(QString());
        searchTypeComboBox->addItem(QString());
        searchTypeComboBox->addItem(QString());
        searchTypeComboBox->addItem(QString());
        searchTypeComboBox->setObjectName("searchTypeComboBox");

        searchLayout->addWidget(searchTypeComboBox);

        searchInput = new QLineEdit(centralwidget);
        searchInput->setObjectName("searchInput");

        searchLayout->addWidget(searchInput);

        searchButton = new QPushButton(centralwidget);
        searchButton->setObjectName("searchButton");

        searchLayout->addWidget(searchButton);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName("resetButton");

        searchLayout->addWidget(resetButton);


        verticalLayout->addLayout(searchLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);

        horizontalLayout->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addContactButton = new QPushButton(centralwidget);
        addContactButton->setObjectName("addContactButton");

        horizontalLayout->addWidget(addContactButton);


        verticalLayout->addLayout(horizontalLayout);

        countLabel = new QLabel(centralwidget);
        countLabel->setObjectName("countLabel");
        countLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(countLabel);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 580, 365));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");

        verticalLayout->addWidget(backButton);

        ContactBookWindow->setCentralWidget(centralwidget);

        retranslateUi(ContactBookWindow);

        QMetaObject::connectSlotsByName(ContactBookWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ContactBookWindow)
    {
        ContactBookWindow->setWindowTitle(QCoreApplication::translate("ContactBookWindow", "\347\244\274\347\211\251", nullptr));
        searchTypeComboBox->setItemText(0, QCoreApplication::translate("ContactBookWindow", "\345\247\223\345\220\215", nullptr));
        searchTypeComboBox->setItemText(1, QCoreApplication::translate("ContactBookWindow", "\345\237\216\345\270\202", nullptr));
        searchTypeComboBox->setItemText(2, QCoreApplication::translate("ContactBookWindow", "\346\240\207\347\255\276", nullptr));
        searchTypeComboBox->setItemText(3, QCoreApplication::translate("ContactBookWindow", "\347\224\265\350\257\235", nullptr));

        searchTypeComboBox->setCurrentText(QCoreApplication::translate("ContactBookWindow", "\345\247\223\345\220\215", nullptr));
        searchInput->setPlaceholderText(QCoreApplication::translate("ContactBookWindow", "\350\276\223\345\205\245\346\237\245\350\257\242\345\205\263\351\224\256\350\257\215...", nullptr));
        searchButton->setText(QCoreApplication::translate("ContactBookWindow", "\346\237\245\350\257\242", nullptr));
        resetButton->setText(QCoreApplication::translate("ContactBookWindow", "\351\207\215\347\275\256", nullptr));
        titleLabel->setText(QCoreApplication::translate("ContactBookWindow", "\347\244\274\347\211\251\345\210\227\350\241\250", nullptr));
        addContactButton->setText(QCoreApplication::translate("ContactBookWindow", "+ \346\267\273\345\212\240\347\244\274\347\211\251(??)", nullptr));
        countLabel->setText(QCoreApplication::translate("ContactBookWindow", "\345\205\261 0 \344\270\252\347\244\274\347\211\251", nullptr));
        backButton->setText(QCoreApplication::translate("ContactBookWindow", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ContactBookWindow: public Ui_ContactBookWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTBOOKWINDOW_H
