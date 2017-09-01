#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWnd.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

class MainWnd : public QMainWindow
{
    Q_OBJECT

public:
    MainWnd(QWidget *parent = Q_NULLPTR);

private slots:
    void onBtnConnect();
    void onBtnQuery();
private:
    Ui::MainWndClass ui;

    QSqlDatabase m_db;
};
