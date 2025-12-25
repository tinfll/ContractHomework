#include "editcontactdialog.h"
#include "ui_editcontactdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>

EditContactDialog::EditContactDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditContactDialog)
{
    ui->setupUi(this);

    // 连接按钮
    connect(ui->saveButton, &QPushButton::clicked, this, &EditContactDialog::onSaveButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &EditContactDialog::onCancelButtonClicked);
}

EditContactDialog::~EditContactDialog()
{
    delete ui;
}

void EditContactDialog::setContact(const Contact &contact)
{
    editedContact = contact;

    // 填充表单
    ui->nameEdit->setText(contact.name);
    ui->genderEdit->setText(contact.gender);
    ui->ageEdit->setText(contact.age);
    ui->phoneEdit->setText(contact.phone);
    ui->cityEdit->setText(contact.city);
    ui->companyEdit->setText(contact.company);
    ui->addressEdit->setText(contact.address);
    ui->tagsEdit->setText(contact.tags.join(" "));

    // 设置窗口标题包含联系人名字
    setWindowTitle(QString("修改联系人 - %1").arg(contact.name));
}

void EditContactDialog::onSaveButtonClicked()
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

    // 验证必填字段
    if (name.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "姓名和电话不能为空！");
        return;
    }

    // 更新联系人信息（保持原ID不变）
    editedContact.name = name;
    editedContact.gender = gender;
    editedContact.age = age;
    editedContact.phone = phone;
    editedContact.city = city;
    editedContact.company = company;
    editedContact.address = address;

    // 解析标签
    if (!tags.isEmpty()) {
        QStringList tagList = tags.split(QRegularExpression("[ ,;]+"), Qt::SkipEmptyParts);
        editedContact.tags = tagList;
    } else {
        editedContact.tags.clear();
    }

    qDebug() << "修改联系人:" << name << phone;

    accept();  // 关闭对话框并返回Accepted
}

void EditContactDialog::onCancelButtonClicked()
{
    reject();  // 关闭对话框并返回Rejected
}
