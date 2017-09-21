#pragma once

#include <QtWidgets/QDialog>
#include "ui_MainDlg.h"

class MainDlg : public QDialog
{
    Q_OBJECT

public:
    MainDlg(QWidget *parent = Q_NULLPTR);

public slots:
    void onBtnToHtml();
    void onBtnFromHtml();
private:
    Ui::MainDlgClass ui;
};
