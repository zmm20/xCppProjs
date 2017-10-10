#include "stdafx.h"
#include "MainDlg.h"
#include <QMessageBox>

MainDlg::MainDlg(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    setWindowState(Qt::WindowMaximized);

    connect(ui.btnToHtml, SIGNAL(clicked()), this, SLOT(onClicked_btnToHtml()));
    connect(ui.btnFromHtml, SIGNAL(clicked()), this, SLOT(onClicked_btnFromHtml()));
    connect(ui.btnSelFirstLine, SIGNAL(clicked()), this, SLOT(onClicked_btnSelFirstLine()));
    connect(ui.btnSelLeft20, SIGNAL(clicked()), this, SLOT(onClicked_btnSelLeft20()));
    connect(ui.btnDelSel, SIGNAL(clicked()), this, SLOT(onClicked_btnDelSel()));
    connect(ui.btnTest, SIGNAL(clicked()), this, SLOT(onClicked_btnTest()));
}

void MainDlg::onClicked_btnToHtml()
{
    //QMessageBox::information(this, "title", "onBtnToHtml");
    ui.plainTextEdit->clear();
    QString ss = ui.textEdit->document()->toHtml("utf8"); //ui.textEdit->toHtml();
    
    ui.plainTextEdit->appendPlainText(ss);
}

void MainDlg::onClicked_btnFromHtml()
{
    //QMessageBox::information(this, "title", "onBtnFromHtml");
    ui.textEdit->clear();
    QString ss = ui.plainTextEdit->toPlainText();
    ui.textEdit->insertHtml(ss);
}

void MainDlg::onClicked_btnSelFirstLine()
{
    QTextCursor txtcur = ui.textEdit->textCursor();
    txtcur.setPosition(0);
    txtcur.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    QString qstr = txtcur.selectedText();

    ui.plainTextEdit->appendPlainText(qstr);
}
void MainDlg::onClicked_btnSelLeft20()
{
    QTextCursor txtcur = ui.textEdit->textCursor();
    txtcur.setPosition(0);
    txtcur.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 20);
    QString qstr = txtcur.selectedText();

    ui.plainTextEdit->appendPlainText(qstr);
}

void MainDlg::onClicked_btnDelSel()
{
    QTextCursor txtcur = ui.textEdit->textCursor();
    //txtcur.setPosition(0);
    //txtcur.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 20);
    txtcur.removeSelectedText();
}

void MainDlg::onClicked_btnTest()
{
    //QString qstr("中国");
    //std::wstring wstr = qstr.toStdWString();

    //ui.plainTextEdit->appendPlainText("test:");
    //ui.plainTextEdit->appendPlainText(QString("中国 wstr size = %1").arg(wstr.length()));
    //ui.plainTextEdit->appendPlainText(QString("中国 qstr size = %1").arg(qstr.length()));

    QFont ft;
    ft.setFamily("宋体");
    ft.setPixelSize(16);
    ui.textEdit->setCurrentFont(ft);
}