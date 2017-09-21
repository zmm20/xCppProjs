#include "stdafx.h"
#include "MainDlg.h"
#include <QMessageBox>

MainDlg::MainDlg(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    setWindowState(Qt::WindowMaximized);

    connect(ui.btnToHtml, SIGNAL(clicked()), this, SLOT(onBtnToHtml()));
    connect(ui.btnFromHtml, SIGNAL(clicked()), this, SLOT(onBtnFromHtml()));
}

void MainDlg::onBtnToHtml()
{
    //QMessageBox::information(this, "title", "onBtnToHtml");
    ui.plainTextEdit->clear();
    QString ss = ui.textEdit->document()->toHtml("utf8"); //ui.textEdit->toHtml();
    
    ui.plainTextEdit->appendPlainText(ss);
}

void MainDlg::onBtnFromHtml()
{
    //QMessageBox::information(this, "title", "onBtnFromHtml");
    ui.textEdit->clear();
    QString ss = ui.plainTextEdit->toPlainText();
    ui.textEdit->insertHtml(ss);
}