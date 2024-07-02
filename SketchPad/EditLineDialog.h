#pragma once

#include <QDialog>
#include "ui_EditLineDialog.h"

class EditLineDialog : public QDialog
{
    Q_OBJECT

public:
    EditLineDialog(QWidget *parent = nullptr);
    ~EditLineDialog();

private:
    Ui::EditLineDialogClass ui;
};
