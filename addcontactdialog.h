#ifndef ADDCONTACTDIALOG_H
#define ADDCONTACTDIALOG_H

#include <QWidget>
#include <QDialog>
#include "contact.h"

namespace Ui {
class AddContactDialog;
}

class AddContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddContactDialog(QWidget *parent = nullptr);
    ~AddContactDialog();

    Contact getContact() const { return newContact; }

private slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::AddContactDialog *ui;
    Contact newContact;
};

#endif // ADDCONTACTDIALOG_H
