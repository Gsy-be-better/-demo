#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./dataBase.db");
    bool ok = db.open();
    if (ok){
        qDebug()<<"link success";
    }
    else {
        qDebug()<<"error open database because"<<db.lastError().text();
    }
    QSqlQuery q;
    q.exec("create table if not exists data("
           "time varchar(20) primary key"
           ");");
    QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    q.prepare("insert into data(time) values (?)");
    q.addBindValue(current_time);
    q.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

