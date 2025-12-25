#ifndef EDITCONTACTDIALOG_H
#define EDITCONTACTDIALOG_H

#include <QDialog>
#include "Contact.h"

namespace Ui {
class EditContactDialog;
}

class EditContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditContactDialog(QWidget *parent = nullptr);
    ~EditContactDialog();

    void setContact(const Contact &contact);


    Contact getContact() const { return editedContact; }

private:
    void onSaveButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::EditContactDialog *ui;
    Contact editedContact;
};

#endif // EDITCONTACTDIALOG_H
