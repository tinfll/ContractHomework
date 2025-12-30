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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalysisWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QFrame *frame;
    QGroupBox *imageDisplayGroup;
    QHBoxLayout *horizontalLayout;
    QGroupBox *originalImageGroup;
    QVBoxLayout *verticalLayout_2;
    QLabel *originalImageLabel;
    QGroupBox *alphaChannelGroup;
    QVBoxLayout *verticalLayout_3;
    QLabel *alphaChannelLabel;
    QGroupBox *imageInfoGroup;
    QVBoxLayout *verticalLayout_4;
    QLabel *imageInfoLabel;
    QGroupBox *actionGroup;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *applyEffectButton;
    QPushButton *saveImageButton;
    QPushButton *backButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *AnalysisWindow)
    {
        if (AnalysisWindow->objectName().isEmpty())
            AnalysisWindow->setObjectName("AnalysisWindow");
        AnalysisWindow->resize(900, 700);
        AnalysisWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #f5f5f5;\n"
"}\n"
"QGroupBox {\n"
"    font-weight: bold;\n"
"    border: 2px solid #4a90e2;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 5px 0 5px;\n"
"    color: #4a90e2;\n"
"}\n"
"QLabel#imageInfoLabel {\n"
"    background-color: white;\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 4px;\n"
"    padding: 5px;\n"
"    font-family: 'Consolas', monospace;\n"
"}\n"
"QPushButton {\n"
"    background-color: #4a90e2;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"    padding: 8px 16px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3a7bc8;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2a6bb0;\n"
"}\n"
"QPushButton#backButton {\n"
"    background-color: #6c757d;\n"
"}\n"
"QPushButton#backButton:hover {\n"
"    background-color: #5a6268;\n"
"}"));
        centralwidget = new QWidget(AnalysisWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame);

        imageDisplayGroup = new QGroupBox(centralwidget);
        imageDisplayGroup->setObjectName("imageDisplayGroup");
        horizontalLayout = new QHBoxLayout(imageDisplayGroup);
        horizontalLayout->setObjectName("horizontalLayout");
        originalImageGroup = new QGroupBox(imageDisplayGroup);
        originalImageGroup->setObjectName("originalImageGroup");
        verticalLayout_2 = new QVBoxLayout(originalImageGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        originalImageLabel = new QLabel(originalImageGroup);
        originalImageLabel->setObjectName("originalImageLabel");
        originalImageLabel->setMinimumSize(QSize(300, 300));
        originalImageLabel->setMaximumSize(QSize(300, 300));
        originalImageLabel->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border: 2px dashed #ccc;\n"
"border-radius: 4px;"));
        originalImageLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(originalImageLabel);


        horizontalLayout->addWidget(originalImageGroup);

        alphaChannelGroup = new QGroupBox(imageDisplayGroup);
        alphaChannelGroup->setObjectName("alphaChannelGroup");
        verticalLayout_3 = new QVBoxLayout(alphaChannelGroup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        alphaChannelLabel = new QLabel(alphaChannelGroup);
        alphaChannelLabel->setObjectName("alphaChannelLabel");
        alphaChannelLabel->setMinimumSize(QSize(300, 300));
        alphaChannelLabel->setMaximumSize(QSize(300, 300));
        alphaChannelLabel->setStyleSheet(QString::fromUtf8("background-color: #808080;\n"
"border: 2px dashed #ccc;\n"
"border-radius: 4px;"));
        alphaChannelLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(alphaChannelLabel);


        horizontalLayout->addWidget(alphaChannelGroup);


        verticalLayout->addWidget(imageDisplayGroup);

        imageInfoGroup = new QGroupBox(centralwidget);
        imageInfoGroup->setObjectName("imageInfoGroup");
        verticalLayout_4 = new QVBoxLayout(imageInfoGroup);
        verticalLayout_4->setObjectName("verticalLayout_4");
        imageInfoLabel = new QLabel(imageInfoGroup);
        imageInfoLabel->setObjectName("imageInfoLabel");
        imageInfoLabel->setAlignment(Qt::AlignLeading);

        verticalLayout_4->addWidget(imageInfoLabel);


        verticalLayout->addWidget(imageInfoGroup);

        actionGroup = new QGroupBox(centralwidget);
        actionGroup->setObjectName("actionGroup");
        horizontalLayout_2 = new QHBoxLayout(actionGroup);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        applyEffectButton = new QPushButton(actionGroup);
        applyEffectButton->setObjectName("applyEffectButton");

        horizontalLayout_2->addWidget(applyEffectButton);

        saveImageButton = new QPushButton(actionGroup);
        saveImageButton->setObjectName("saveImageButton");

        horizontalLayout_2->addWidget(saveImageButton);

        backButton = new QPushButton(actionGroup);
        backButton->setObjectName("backButton");

        horizontalLayout_2->addWidget(backButton);


        verticalLayout->addWidget(actionGroup);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        AnalysisWindow->setCentralWidget(centralwidget);

        retranslateUi(AnalysisWindow);

        QMetaObject::connectSlotsByName(AnalysisWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AnalysisWindow)
    {
        AnalysisWindow->setWindowTitle(QCoreApplication::translate("AnalysisWindow", "\360\237\216\250 \347\224\237\346\227\245\345\233\276\347\211\207\345\210\206\346\236\220\345\267\245\345\235\212", nullptr));
        titleLabel->setText(QCoreApplication::translate("AnalysisWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; font-weight:700; color:#4a90e2;\">\360\237\216\250 \347\224\237\346\227\245\345\233\276\347\211\207\345\210\206\346\236\220\345\267\245\345\235\212</span></p></body></html>", nullptr));
        imageDisplayGroup->setTitle(QCoreApplication::translate("AnalysisWindow", "\345\233\276\347\211\207\351\242\204\350\247\210", nullptr));
        originalImageGroup->setTitle(QCoreApplication::translate("AnalysisWindow", "\345\216\237\345\233\276", nullptr));
        originalImageLabel->setText(QCoreApplication::translate("AnalysisWindow", "<\347\255\211\345\276\205\345\212\240\350\275\275\345\233\276\347\211\207>", nullptr));
        alphaChannelGroup->setTitle(QCoreApplication::translate("AnalysisWindow", "Alpha\351\200\232\351\201\223\357\274\210\351\200\217\346\230\216\351\200\232\351\201\223\357\274\211", nullptr));
        alphaChannelLabel->setText(QCoreApplication::translate("AnalysisWindow", "<Alpha\351\200\232\351\201\223\351\242\204\350\247\210>", nullptr));
        imageInfoGroup->setTitle(QCoreApplication::translate("AnalysisWindow", "\345\233\276\347\211\207\344\277\241\346\201\257", nullptr));
        imageInfoLabel->setText(QCoreApplication::translate("AnalysisWindow", "\346\226\207\344\273\266\350\267\257\345\276\204: \\n\345\260\272\345\257\270: \\n\346\240\274\345\274\217: \\nAlpha\351\200\232\351\201\223: \\n\351\200\217\346\230\216\345\272\246\347\273\237\350\256\241: ", nullptr));
        actionGroup->setTitle(QCoreApplication::translate("AnalysisWindow", "\346\223\215\344\275\234", nullptr));
        applyEffectButton->setText(QCoreApplication::translate("AnalysisWindow", "\342\234\250 \345\272\224\347\224\250\350\211\272\346\234\257\347\211\271\346\225\210", nullptr));
        saveImageButton->setText(QCoreApplication::translate("AnalysisWindow", "\360\237\222\276 \344\277\235\345\255\230\345\233\276\347\211\207", nullptr));
        backButton->setText(QCoreApplication::translate("AnalysisWindow", "\360\237\224\231 \350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnalysisWindow: public Ui_AnalysisWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSISWINDOW_H
