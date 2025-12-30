/********************************************************************************
** Form generated from reading UI file 'addcontactdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCONTACTDIALOG_H
#define UI_ADDCONTACTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddContactDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QLabel *label_2;
    QLineEdit *genderEdit;
    QLabel *label_3;
    QLineEdit *ageEdit;
    QLabel *label_4;
    QLineEdit *phoneEdit;
    QLabel *label_5;
    QLineEdit *cityEdit;
    QLabel *label_6;
    QLineEdit *companyEdit;
    QLabel *label_7;
    QLineEdit *addressEdit;
    QLabel *label_8;
    QLineEdit *tagsEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddContactDialog)
    {
        if (AddContactDialog->objectName().isEmpty())
            AddContactDialog->setObjectName("AddContactDialog");
        AddContactDialog->resize(400, 400);
        verticalLayoutWidget = new QWidget(AddContactDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 341));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        nameEdit = new QLineEdit(verticalLayoutWidget);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        genderEdit = new QLineEdit(verticalLayoutWidget);
        genderEdit->setObjectName("genderEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, genderEdit);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        ageEdit = new QLineEdit(verticalLayoutWidget);
        ageEdit->setObjectName("ageEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, ageEdit);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        phoneEdit = new QLineEdit(verticalLayoutWidget);
        phoneEdit->setObjectName("phoneEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, phoneEdit);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        cityEdit = new QLineEdit(verticalLayoutWidget);
        cityEdit->setObjectName("cityEdit");

        formLayout->setWidget(4, QFormLayout::FieldRole, cityEdit);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName("label_6");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        companyEdit = new QLineEdit(verticalLayoutWidget);
        companyEdit->setObjectName("companyEdit");

        formLayout->setWidget(5, QFormLayout::FieldRole, companyEdit);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName("label_7");

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        addressEdit = new QLineEdit(verticalLayoutWidget);
        addressEdit->setObjectName("addressEdit");

        formLayout->setWidget(6, QFormLayout::FieldRole, addressEdit);

        label_8 = new QLabel(verticalLayoutWidget);
        label_8->setObjectName("label_8");

        formLayout->setWidget(7, QFormLayout::LabelRole, label_8);

        tagsEdit = new QLineEdit(verticalLayoutWidget);
        tagsEdit->setObjectName("tagsEdit");

        formLayout->setWidget(7, QFormLayout::FieldRole, tagsEdit);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(verticalLayoutWidget);
        okButton->setObjectName("okButton");

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(verticalLayoutWidget);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AddContactDialog);

        QMetaObject::connectSlotsByName(AddContactDialog);
    } // setupUi

    void retranslateUi(QDialog *AddContactDialog)
    {
        AddContactDialog->setWindowTitle(QCoreApplication::translate("AddContactDialog", "\346\267\273\345\212\240\347\244\274\347\211\251", nullptr));
        label->setText(QCoreApplication::translate("AddContactDialog", "\345\247\223\345\220\215:", nullptr));
        label_2->setText(QCoreApplication::translate("AddContactDialog", "\346\200\247\345\210\253:", nullptr));
        genderEdit->setText(QCoreApplication::translate("AddContactDialog", "\345\245\263", nullptr));
        label_3->setText(QCoreApplication::translate("AddContactDialog", "\345\271\264\351\276\204:", nullptr));
        label_4->setText(QCoreApplication::translate("AddContactDialog", "\347\224\265\350\257\235:", nullptr));
        label_5->setText(QCoreApplication::translate("AddContactDialog", "\345\237\216\345\270\202:", nullptr));
        label_6->setText(QCoreApplication::translate("AddContactDialog", "\345\215\225\344\275\215:", nullptr));
        label_7->setText(QCoreApplication::translate("AddContactDialog", "\344\275\217\345\235\200:", nullptr));
        label_8->setText(QCoreApplication::translate("AddContactDialog", "\346\240\207\347\255\276:", nullptr));
        tagsEdit->setText(QCoreApplication::translate("AddContactDialog", "\346\234\213\345\217\213", nullptr));
        okButton->setText(QCoreApplication::translate("AddContactDialog", "\347\241\256\345\256\232", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddContactDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddContactDialog: public Ui_AddContactDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCONTACTDIALOG_H
