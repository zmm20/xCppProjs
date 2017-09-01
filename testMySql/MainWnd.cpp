#include "MainWnd.h"
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QtSql/qsqldriver.h>

MainWnd::MainWnd(QWidget *parent)
    : QMainWindow(parent)
    , m_db(QSqlDatabase::addDatabase("QMYSQL3"))
{
    ui.setupUi(this);

    //QSettings settings("Software Inc", "Spreadsheet"); // windows��ע����н����� Software Inc -> Spreadsheet
    QSettings settings("config/config.ini", QSettings::IniFormat); // INI�ļ�
    // read
    QString str = settings.value("mysql/server").toString();
    if (str.isEmpty())
        QMessageBox::critical(this, "error", u8"��config.ini ��û���ҵ���: server!");
    m_db.setHostName(str);

    str = settings.value("mysql/db").toString();
    m_db.setDatabaseName(str);
    str = settings.value("mysql/user").toString();
    m_db.setUserName(str);
    str = settings.value("mysql/password").toString();
    m_db.setPassword(str);
    int port = settings.value("mysql/port").toInt();
    m_db.setPort(port);
   
    connect(ui.btnConnect, SIGNAL(clicked()), this, SLOT(onBtnConnect()));
    connect(ui.btnQuery, SIGNAL(clicked()), this, SLOT(onBtnQuery()));
}

void MainWnd::onBtnConnect()
{
    bool ok = m_db.open();
    if (!ok)
    {
        QMessageBox::critical(this, "error", m_db.lastError().text());
        return;
    }

    // hasFeature �������ʧ��, ���п�����mysql�Ĳ����Ҫ���±���.
    const auto driver = m_db.driver();
    bool hasTransaction = driver->hasFeature(QSqlDriver::Transactions);
    if (!hasTransaction)
        QMessageBox::information(this, "", u8"��֧������!");
}

void MainWnd::onBtnQuery()
{
    ui.listWidget->clear();

    bool bOk = false;
    bOk = m_db.transaction();
    if (!bOk)
    {
        const QString ss = m_db.lastError().text();
        QMessageBox::information(this, "", ss);
    }

    QSqlQuery query(m_db);
    int numrows = 0;
    query.exec("select * from stu");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        
        // method 1:
        //int age = query.value(2).toInt();
        // method 2:
        int age = query.value("sex").toInt();

        ui.listWidget->insertItem(numrows, QString::number(id) + "\t" + name + "\t" + QString::number(age));
        numrows++;
    }

    query.clear();
    if (!query.exec("INSERT INTO stu (`name`, `sex`) VALUES('zhangsan', 1);"))
        return;

    bOk = m_db.rollback();
    if (!bOk)
        QMessageBox::information(this, "", u8"����ع�ʧ��!");
}
