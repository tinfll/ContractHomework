#include "addcontactdialog.h"
#include "ui_addcontactdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>

AddContactDialog::AddContactDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddContactDialog)
{
    ui->setupUi(this);
    setWindowTitle("添加新联系人");

    connect(ui->okButton, &QPushButton::clicked, this, &AddContactDialog::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AddContactDialog::onCancelButtonClicked);
}

AddContactDialog::~AddContactDialog()
{
    delete ui;
}

void AddContactDialog::onOkButtonClicked()
{
    // 获取输入
    QString name = ui->nameEdit->text().trimmed();
    QString gender = ui->genderEdit->text().trimmed();
    QString age = ui->ageEdit->text().trimmed();
    QString phone = ui->phoneEdit->text().trimmed();
    QString city = ui->cityEdit->text().trimmed();
    QString company = ui->companyEdit->text().trimmed();
    QString address = ui->addressEdit->text().trimmed();
    QString tags = ui->tagsEdit->text().trimmed();

    // 简单验证
    if (name.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "姓名和电话不能为空！");
        return;
    }

    // 创建新联系人
    newContact.name = name;
    newContact.gender = gender;
    newContact.age = age;
    newContact.phone = phone;
    newContact.city = city;
    newContact.company = company;
    newContact.address = address;

    // 解析标签（用空格或逗号分隔）
    if (!tags.isEmpty()) {
        QStringList tagList = tags.split(QRegularExpression("[ ,;]+"), Qt::SkipEmptyParts);
        newContact.tags = tagList;
    }

    // ID将在添加到列表时设置
    newContact.id = 0;

    qDebug() << "新联系人信息:" << name << phone << city;

    accept();  // 关闭对话框并返回Accepted
}

void AddContactDialog::onCancelButtonClicked()
{
    reject();  // 关闭对话框并返回Rejected
}
