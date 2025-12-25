/********************************************************************************
** Form generated from reading UI file 'analysiswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSISWINDOW_H
#define UI_ANALYSISWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalysisWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QGroupBox *fileInfoGroup;
    QHBoxLayout *horizontalLayout;
    QLabel *file1Label;
    QLabel *file1NameLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *file2Label;
    QLabel *file2NameLabel;
    QTabWidget *tabWidget;
    QWidget *tagTab;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *tagTextBrowser;
    QWidget *commonTab;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *commonTextBrowser;
    QWidget *relationTab;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *relationTextBrowser;
    QHBoxLayout *buttonLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *backButton;

    void setupUi(QMainWindow *AnalysisWindow)
    {
        if (AnalysisWindow->objectName().isEmpty())
            AnalysisWindow->setObjectName("AnalysisWindow");
        AnalysisWindow->resize(800, 600);
        centralwidget = new QWidget(AnalysisWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        fileInfoGroup = new QGroupBox(centralwidget);
        fileInfoGroup->setObjectName("fileInfoGroup");
        horizontalLayout = new QHBoxLayout(fileInfoGroup);
        horizontalLayout->setObjectName("horizontalLayout");
        file1Label = new QLabel(fileInfoGroup);
        file1Label->setObjectName("file1Label");

        horizontalLayout->addWidget(file1Label);

        file1NameLabel = new QLabel(fileInfoGroup);
        file1NameLabel->setObjectName("file1NameLabel");
        file1NameLabel->setStyleSheet(QString::fromUtf8("color: #2196F3; font-weight: bold;"));

        horizontalLayout->addWidget(file1NameLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        file2Label = new QLabel(fileInfoGroup);
        file2Label->setObjectName("file2Label");

        horizontalLayout->addWidget(file2Label);

        file2NameLabel = new QLabel(fileInfoGroup);
        file2NameLabel->setObjectName("file2NameLabel");
        file2NameLabel->setStyleSheet(QString::fromUtf8("color: #4CAF50; font-weight: bold;"));

        horizontalLayout->addWidget(file2NameLabel);


        verticalLayout->addWidget(fileInfoGroup);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tagTab = new QWidget();
        tagTab->setObjectName("tagTab");
        verticalLayout_2 = new QVBoxLayout(tagTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tagTextBrowser = new QTextBrowser(tagTab);
        tagTextBrowser->setObjectName("tagTextBrowser");

        verticalLayout_2->addWidget(tagTextBrowser);

        tabWidget->addTab(tagTab, QString());
        commonTab = new QWidget();
        commonTab->setObjectName("commonTab");
        verticalLayout_3 = new QVBoxLayout(commonTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        commonTextBrowser = new QTextBrowser(commonTab);
        commonTextBrowser->setObjectName("commonTextBrowser");

        verticalLayout_3->addWidget(commonTextBrowser);

        tabWidget->addTab(commonTab, QString());
        relationTab = new QWidget();
        relationTab->setObjectName("relationTab");
        verticalLayout_4 = new QVBoxLayout(relationTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        relationTextBrowser = new QTextBrowser(relationTab);
        relationTextBrowser->setObjectName("relationTextBrowser");

        verticalLayout_4->addWidget(relationTextBrowser);

        tabWidget->addTab(relationTab, QString());

        verticalLayout->addWidget(tabWidget);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(horizontalSpacer_2);

        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #6c757d;\n"
"    color: white;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 12px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5a6268;\n"
"}"));

        buttonLayout->addWidget(backButton);


        verticalLayout->addLayout(buttonLayout);

        AnalysisWindow->setCentralWidget(centralwidget);

        retranslateUi(AnalysisWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AnalysisWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AnalysisWindow)
    {
        AnalysisWindow->setWindowTitle(QCoreApplication::translate("AnalysisWindow", "\351\200\232\350\256\257\345\275\225\345\210\206\346\236\220", nullptr));
        titleLabel->setText(QCoreApplication::translate("AnalysisWindow", "\351\200\232\350\256\257\345\275\225\345\257\271\346\257\224\345\210\206\346\236\220", nullptr));
        fileInfoGroup->setTitle(QCoreApplication::translate("AnalysisWindow", "\345\210\206\346\236\220\346\226\207\344\273\266", nullptr));
        file1Label->setText(QCoreApplication::translate("AnalysisWindow", "\346\226\207\344\273\2661: ", nullptr));
        file1NameLabel->setText(QCoreApplication::translate("AnalysisWindow", "\346\234\252\351\200\211\346\213\251", nullptr));
        file2Label->setText(QCoreApplication::translate("AnalysisWindow", "\346\226\207\344\273\2662: ", nullptr));
        file2NameLabel->setText(QCoreApplication::translate("AnalysisWindow", "\346\234\252\351\200\211\346\213\251", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tagTab), QCoreApplication::translate("AnalysisWindow", "\360\237\223\212 \346\240\207\347\255\276\347\273\237\350\256\241", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(commonTab), QCoreApplication::translate("AnalysisWindow", "\360\237\224\227 \345\205\261\345\220\214\350\201\224\347\263\273\344\272\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(relationTab), QCoreApplication::translate("AnalysisWindow", "\342\235\244\357\270\217 \347\244\276\344\272\244\345\205\263\350\201\224\345\272\246", nullptr));
        backButton->setText(QCoreApplication::translate("AnalysisWindow", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnalysisWindow: public Ui_AnalysisWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSISWINDOW_H
