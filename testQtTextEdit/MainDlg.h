#pragma once

#include <QtWidgets/QDialog>
#include "ui_MainDlg.h"

class MainDlg : public QDialog
{
    Q_OBJECT

public:
    MainDlg(QWidget *parent = Q_NULLPTR);

public slots:
    void onClicked_btnToHtml();
    void onClicked_btnFromHtml();
    void onClicked_btnSelFirstLine();
    void onClicked_btnSelLeft20();
    void onClicked_btnDelSel();
    void onClicked_btnTest();
private:
    Ui::MainDlgClass ui;
};
