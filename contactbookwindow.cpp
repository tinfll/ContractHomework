#include "contactbookwindow.h"
#include "addcontactdialog.h"
#include "editcontactdialog.h"
#include "ui_contactbookwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QSpacerItem>
#include <QDir>
#include <QScrollArea>
#include <QMenu>
#include <QCursor>


ContactBookWindow::ContactBookWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ContactBookWindow)
    , currentFilePath("")
{
    ui->setupUi(this);


    connect(ui->backButton, &QPushButton::clicked, this, &ContactBookWindow::onBackButtonClicked);

    connect(ui->addContactButton, &QPushButton::clicked, this, &ContactBookWindow::onAddContactButtonClicked);

    // 查询
    connect(ui->searchButton, &QPushButton::clicked, this, &ContactBookWindow::onSearchButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &ContactBookWindow::onResetButtonClicked);


}

//按钮区
ContactBookWindow::~ContactBookWindow()
{
    delete ui;
}
void ContactBookWindow::onAddContactButtonClicked()
{
    showAddContactDialog();
}

void ContactBookWindow::onSearchButtonClicked()
{
    performSearch();
}

void ContactBookWindow::onResetButtonClicked()
{
    resetSearch();
}

//传递所选文件
void ContactBookWindow::setFilePath(const QString &filePath)
{
    currentFilePath = filePath;

    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    setWindowTitle("我们都有各自的生活:" + fileName);


    // 加载并显示联系人
    loadContactsFromFile();

    filteredContacts = contacts;
    updateDisplay();
}

//加载文件
void ContactBookWindow::loadContactsFromFile()
{
    contacts.clear();

    if (currentFilePath.isEmpty() || !QFile::exists(currentFilePath)) {
        QMessageBox::warning(this, "错误", "文件不存在: " + currentFilePath);
        return;
    }

    QFile file(currentFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开文件: " + currentFilePath);
        return;
    }

    QTextStream in(&file);
    int lineCount = 0;
    int successCount = 0;

    //debug用
    while (!in.atEnd()) {
        lineCount++;
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        Contact contact;
        if (contact.parseFromString(line)) {
            contacts.append(contact);
            successCount++;
        } else {
            qWarning() << "第" << lineCount << "行解析失败:" << line;
        }
    }

    file.close();

    qDebug() << "从文件" << currentFilePath << "加载了" << successCount
             << "个联系人(共" << lineCount << "行)";
}

//刷新界面/界面ui展示
void ContactBookWindow::updateDisplay()
{
    // 清除之前的显示
    clearContactsDisplay();

    // 更新数量标签
    ui->countLabel->setText(QString("共 %1 个联系人").arg(contacts.size()));

    // 获取滚动区域的内容布局
    QVBoxLayout *contactsLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

    // 移除占位的spacer
    if (contactsLayout->count() > 0) {
        QLayoutItem* spacer = contactsLayout->takeAt(0);
        delete spacer;
    }

    // 如果没有过滤到任何联系人
    if (filteredContacts.isEmpty()) {
        QLabel *emptyLabel = new QLabel("没有找到匹配的联系人");
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #999; font-style: italic; padding: 20px;");
        contactsLayout->addWidget(emptyLabel);
    }else {
        // 添加过滤后的联系人按钮
        for (const Contact &contact : filteredContacts) {
            QWidget *contactRow = new QWidget();
            QHBoxLayout *rowLayout = new QHBoxLayout(contactRow);
            rowLayout->setContentsMargins(2, 2, 2, 2);
            rowLayout->setSpacing(5);
        }



    // 添加联系人+管理按钮!!
    for (const Contact &contact : contacts) {


        QWidget *contactRow = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(contactRow);
        rowLayout->setContentsMargins(2, 2, 2, 2);
        rowLayout->setSpacing(5);

        // 联系人信息按钮（左边）
        QPushButton *contactButton = new QPushButton(contact.getShortInfo());
        contactButton->setProperty("contactId", contact.id);
        contactButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        // 设置联系人按钮样式
        contactButton->setStyleSheet(
            "QPushButton {"
            "    text-align: left;"
            "    padding: 8px;"
            "    border: 1px solid #ddd;"
            "    border-radius: 4px;"
            "    background-color: white;"
            "}"
            "QPushButton:hover {"
            "    background-color: #f0f0f0;"
            "    border-color: #ccc;"
            "}"
            );

        // 管理按钮（右边）
        QPushButton *manageButton = new QPushButton("管理");
        manageButton->setProperty("contactId", contact.id);
        manageButton->setFixedWidth(60);  // 固定宽度
        manageButton->setStyleSheet(
            "QPushButton {"
            "    padding: 8px;"
            "    border: 1px solid #4CAF50;"
            "    border-radius: 4px;"
            "    background-color: #4CAF50;"
            "    color: white;"
            "    font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "    background-color: #45a049;"
            "    border-color: #3d8b40;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #3d8b40;"
            "}"
            );

        // 添加按钮到水平布局
        rowLayout->addWidget(contactButton);
        rowLayout->addWidget(manageButton);

        // 添加到主布局
        contactsLayout->addWidget(contactRow);

        // 连接信号
        connect(contactButton, &QPushButton::clicked, this, &ContactBookWindow::onContactButtonClicked);
        connect(manageButton, &QPushButton::clicked, this, &ContactBookWindow::onManageButtonClicked);


    }


    // 如果没有任何联系人，显示提示
    if (contacts.isEmpty()) {
        QLabel *emptyLabel = new QLabel("暂无联系人数据");
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #999; font-style: italic;");
        contactsLayout->addWidget(emptyLabel);
    }

    // 添加拉伸因子，让按钮在上面
    contactsLayout->addStretch();
}
}

//清空界面
void ContactBookWindow::clearContactsDisplay()
{
    QVBoxLayout *contactsLayout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());

    if (!contactsLayout) return;

    // 删除所有子控件
    while (contactsLayout->count() > 0) {
        QLayoutItem* item = contactsLayout->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

//保存机制
void ContactBookWindow::saveContactsToFile()
{
    if(currentFilePath.isEmpty()){
        QMessageBox::warning(this, "e", "empty");
        return;
    }

    QFile file(currentFilePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, "错误", "无法保存文件: " + currentFilePath);
        return;
    }

    QTextStream out(&file);

    for(const Contact &contact : contacts){
        // 构建基本部分：ID 姓名 性别 电话 城市 单位
        QString line = QString("%1 %2 %3 %4 %5 %6 %7")
                           .arg(contact.id)
                           .arg(contact.name)
                           .arg(contact.gender)
                           .arg(contact.age)
                           .arg(contact.phone)
                           .arg(contact.city)
                           .arg(contact.company);

        // 添加标签（如果有）
        if (!contact.tags.isEmpty()) {
            // 每个标签用空格分隔
            for (const QString &tag : contact.tags) {
                line += " " + tag.trimmed();
            }
        }

        out << line << "\n";
        qDebug() << "保存行:" << line;

    }

    file.close();

    qDebug() << "已保存" << contacts.size() << "个联系人到文件";
}

//加数机制
void ContactBookWindow::showAddContactDialog(){
    AddContactDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted){
        Contact newContact = dialog.getContact();

        //初始化变量
        int maxID = 0;
        //算....计数...?
        for(const Contact &contact : contacts) {
            if(contact.id > maxID){
                maxID = contact.id;
            }
        }
        newContact.id = maxID + 1;

        contacts.append(newContact);

        saveContactsToFile();

        updateDisplay();

        QMessageBox::information(this, "成功", QString("已添加联系人: %1").arg(newContact.name));

    }

}

//查看联系人详情
void ContactBookWindow::onContactButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int contactId = button->property("contactId").toInt();

    // 联系人
    for (const Contact &contact : contacts) {
        if (contact.id == contactId) {
            // 显示详细信息
            QString details = QString("编号: %1\n"
                                      "姓名: %2\n"
                                      "性别: %3\n"
                                      "年龄: %4\n"
                                      "电话: %5\n"
                                      "城市: %6\n"
                                      "单位/地址: %7\n"
                                      "标签: %8")
                                  .arg(contact.id)
                                  .arg(contact.name)
                                  .arg(contact.gender)
                                  .arg(contact.age)
                                  .arg(contact.phone)
                                  .arg(contact.city)
                                  .arg(contact.company)
                                  .arg(contact.tags.join(", "));

            QMessageBox::information(this,
                                     QString("联系人: %1").arg(contact.name),
                                     details);
            break;
        }
    }
}

//管理
void ContactBookWindow::onManageButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int contactId = button->property("contactId").toInt();

    // 查找联系人
    Contact *selectedContact = nullptr;
    int contactIndex = -1;
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].id == contactId) {
            selectedContact = &contacts[i];
            contactIndex = i;
            break;
        }
    }

    if (!selectedContact) {
        QMessageBox::warning(this, "错误", "未找到联系人！");
        return;
    }

    // 弹出管理选项菜单
    QMenu menu(this);

    QAction *editAction = menu.addAction("修改");
    QAction *deleteAction = menu.addAction("删除");
    menu.addSeparator();
    QAction *cancelAction = menu.addAction("取消");

    // 显示菜单
    QAction *selectedAction = menu.exec(QCursor::pos());

    if (selectedAction == editAction) {
        // 修改联系人
        showEditContactDialog(contactIndex);
    } else if (selectedAction == deleteAction) {
        // 删除联系人
        deleteContact(contactIndex);
    }
}

//删除
void ContactBookWindow::deleteContact(int index)
{
    if (index < 0 || index >= contacts.size()) {
        return;
    }

    QString contactName = contacts[index].name;

    // 确认删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除",
                                  QString("确定要删除联系人【%1】吗？").arg(contactName),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 从列表中删除
        contacts.removeAt(index);

        // 重新编号所有联系人（确保ID连续）
        for (int i = 0; i < contacts.size(); i++) {
            contacts[i].id = i + 1;
        }

        // 保存到文件
        saveContactsToFile();

        // 刷新显示
        updateDisplay();

        QMessageBox::information(this, "成功", QString("已删除联系人: %1").arg(contactName));
    }
}

//编辑
void ContactBookWindow::showEditContactDialog(int index)
{
    if (index < 0 || index >= contacts.size()) {
        return;
    }

    // 创建编辑对话框
    EditContactDialog dialog(this);

    // 设置当前联系人信息
    dialog.setContact(contacts[index]);

    // 显示对话框
    if (dialog.exec() == QDialog::Accepted) {
        // 获取修改后的联系人
        Contact updatedContact = dialog.getContact();

        // 保持原ID不变
        updatedContact.id = contacts[index].id;

        // 更新列表中的联系人
        contacts[index] = updatedContact;

        // 保存到文件
        saveContactsToFile();

        // 刷新显示
        updateDisplay();

        QMessageBox::information(this, "成功",
                                 QString("已修改联系人: %1").arg(updatedContact.name));

        qDebug() << "联系人修改完成:" << updatedContact.name;
    }
}


//查询
void ContactBookWindow::performSearch()
{
    QString keyword = ui->searchInput->text().trimmed();
    int searchType = ui->searchTypeComboBox->currentIndex();

    if (keyword.isEmpty()) {
        QMessageBox::information(this, "提示", "请输入查询关键词");
        return;
    }

    // 执行查询
    filterContacts();

    // 如果没有找到结果
    if (filteredContacts.isEmpty()) {
        QMessageBox::information(this, "查询结果",
                                 QString("没有找到匹配【%1】的联系人").arg(keyword));
    }else {
        // 如果有结果，显示成功消息
        int searchType = ui->searchTypeComboBox->currentIndex();
        QString typeText = ui->searchTypeComboBox->currentText();
        QMessageBox::information(this, "查询成功",
                                 QString("找到 %1 个匹配【%2】的联系人\n查询类型: %3")
                                     .arg(filteredContacts.size())
                                     .arg(keyword)
                                     .arg(typeText));
    }
    updateDisplay();
}

void ContactBookWindow::filterContacts()
{
    QString keyword = ui->searchInput->text().trimmed().toLower();
    int searchType = ui->searchTypeComboBox->currentIndex();

    filteredContacts.clear();

    for (const Contact &contact : contacts) {
        bool match = false;

        switch (searchType) {
        case 0: // 按姓名查询
            match = (contact.name.toLower() == keyword);
            break;

        case 1: // 按城市查询
            match = (contact.city.toLower() == keyword);
            break;

        case 2: // 按标签查询
            for (const QString &tag : contact.tags) {
                if (tag.toLower() == keyword) {
                    match = true;
                    break;
                }
            }
            break;

        case 3: // 按电话查询
            match = (contact.phone == keyword); // 电话通常不区分大小写
            break;

        default:
            break;
        }

        if (match) {
            filteredContacts.append(contact);
        }
    }

    qDebug() << "查询完成，类型:" << searchType
             << "关键词:" << keyword
             << "匹配到" << filteredContacts.size() << "个联系人";
}

void ContactBookWindow::resetSearch()
{
    // 重置查询条件
    ui->searchInput->clear();
    ui->searchTypeComboBox->setCurrentIndex(0);

    // 显示所有联系人
    filteredContacts = contacts;

    // 更新显示
    updateDisplay();

    qDebug() << "重置查询，显示所有" << contacts.size() << "个联系人";
}



//返回
void ContactBookWindow::onBackButtonClicked()
{
    this->close();
    if (parentWidget()) {
        parentWidget()->show();
    }
}



/*

void ContactBookWindow::loadContractsFromFile()
{
    QWidget *centralWidget = ui->centralwidget;
    if(!centralWidget) return;


    QString filePath = QCoreApplication::applicationDirPath();

    QString exeDir = ;
    QString dataDir = exeDir + "/Data/";



}*/
