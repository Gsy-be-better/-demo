#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QFileDialog>//文件对话框所需
#include<QFileInfo>//获取文件信息所需
#include<QDebug>
#include<QDateTime>
#include<QDataStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->choose->setEnabled(true);
    ui->change->setEnabled(false);
    ui->cancal_change->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_choose_clicked()
{
    path = QFileDialog::getOpenFileName(this,"open","../","TXT(*.txt)");
    if(path.isEmpty() == false)
    {
        //文件对象
        QFile file(path);
        QList<QString> l;
        //打开文件
        if(file.open(QIODevice::ReadOnly | QIODevice::Text) == true)
        {
            QString array;
            while (file.atEnd() == false)
            {
                array += file.readLine();
            }
            ui->textEdit->setText(array);
        }
        //关闭文件
        file.close();
    }
    ui->choose->setEnabled(false);
    ui->change->setEnabled(true);
    ui->cancal_change->setEnabled(true);
    ui->pushButton_3->setEnabled(false);
}

QString MainWindow::hang_wei(QString temp)
{
    for(int i = 0; i < temp.size(); i++)
    {
        if(temp[i] == '\n')
        {
            temp.insert(i, ',');
//            qDebug() << temp;
            return temp;
        }
    }
    return NULL;
}
void MainWindow::first_line(QString temp)
{
    QList<QString> l = temp.split("  ");
    QString ans = l[0] + ',' + "  " + l[1] + ',' + "  " + l[2] + ',' + "  " + hang_wei(l[3]);
    gsy.push_back(ans);
}

void MainWindow::on_change_clicked()
{
    if(path.isEmpty() == false)
    {
        //文件对象
        QFile file(path);
        QList<QString> l;
        //打开文件
        if(file.open(QIODevice::ReadOnly | QIODevice::Text) == true)
        {
            QString array;
            //test
            array = file.readLine();
            array = "xdata float list[288]={" + array.mid(3, array.size()-3);
            //首行函数
            first_line(array);
            for(int i = 0; i < 70; i++)
            {
                array = file.readLine();
                //中间行函数
                middle_line(array);
            }
            array = file.readLine();
            array = array.insert(array.size() - 1 ,"};");
            //尾间行函数
            last_line(array);
        }
        //关闭文件
        file.close();
        QString result;
        for(int i = 0; i < gsy.size(); i++)
        {
            result += gsy[i];
        }
        ui->textEdit->setText(result);
        ui->choose->setEnabled(false);
        ui->change->setEnabled(false);
        ui->cancal_change->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
    }
    else
    {
        ui->textEdit->setText("出错，请重新选择！");
        ui->choose->setEnabled(true);
        ui->change->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}
void MainWindow::middle_line(QString temp)
{
    QString ans;
    QList<QString> l = temp.split(" ");
//    qDebug() << l;
    for(int i = 0; i < l.size() - 1; i++)
    {
        if(l[i] == "")
        {
            ans += l[i] + " ";
        }
        else
        {
            ans += l[i] + ',' + " ";
        }
    }
    ans += hang_wei(l[l.size() - 1]);
    gsy.push_back(ans);
}
void MainWindow::last_line(QString temp)
{
    QString ans;
    QList<QString> l = temp.split(" ");
//    qDebug() << l;
    for(int i = 0; i < l.size() - 1; i++)
    {
        if(l[i] == "")
        {
            ans += l[i] + " ";
        }
        else
        {
            ans += l[i] + ',' + " ";
        }
    }
    ans += l[l.size() - 1];
//    qDebug() << ans;
    gsy.push_back(ans);
}
QString MainWindow::last_hang_wei(QString temp)
{
    for(int i = 0; i < temp.size(); i++)
    {
        if(temp[i] == '}')
        {
            temp.insert(i, ',');
            return temp;
        }
    }
    return NULL;
}

void MainWindow::on_pushButton_3_clicked()
{
    if(path.isEmpty() == false)
    {
        QFile file(path);//创建文件对象
        //打开文件
        if(file.open(QIODevice::WriteOnly | QIODevice::Text) == true)
        {
            QString str = ui->textEdit->toPlainText();
            /* 转换为字节数组 */
            QByteArray strBytes = str.toUtf8();
            file.write(strBytes,strBytes.length());
            ui->textEdit->clear();
            file.close();
        }
    }
    gsy.clear();
    ui->choose->setEnabled(true);
    ui->change->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

void MainWindow::on_cancal_change_clicked()
{
    gsy.clear();
    ui->choose->setEnabled(true);
    ui->change->setEnabled(false);
    ui->cancal_change->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}
