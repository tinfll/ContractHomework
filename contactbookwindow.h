#ifndef CONTACTBOOKWINDOW_H
#define CONTACTBOOKWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QList>
#include "Contact.h"

namespace Ui {
class ContactBookWindow;
}

class ContactBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ContactBookWindow(QWidget *parent = nullptr);
    ~ContactBookWindow();

    void setFilePath(const QString &filePath);

//按钮都于此slot

private slots:
    void onContactButtonClicked();
    void onBackButtonClicked();
    void onAddContactButtonClicked();
    void onManageButtonClicked();  // 新增管理按钮点击事件
    void onSearchButtonClicked();      // 新增：查询按钮点击
    void onResetButtonClicked();       // 新增：重置按钮点击


//此为函数...
private:
    Ui::ContactBookWindow *ui;
    QString currentFilePath;  // 存储完整路径
    QList<Contact> contacts;  // 存储所有联系人
    QList<Contact> filteredContacts;   // 新增：过滤后的联系人列表

    //BASIC:
    void loadContactsFromFile();
    void displayContacts();
    void clearContactsDisplay();

    void saveContactsToFile();  // 保存到文件
    void showAddContactDialog();  // 显示添加联系人对话框

    void deleteContact(int index);
    void showEditContactDialog(int index);

    //查询
    void performSearch();
    void filterContacts();
    void resetSearch();
    void updateDisplay();

};

#endif // CONTACTBOOKWINDOW_H
