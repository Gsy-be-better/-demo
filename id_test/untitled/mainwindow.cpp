#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <stdio.h>
#include <QDateTime>
#include <stdlib.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    int a = 0x31;
//    char b = '1';
//    if(a == b)
//    {
//        qDebug() << "没找到！";
//    }


    write_result_txt();
write_result_txt();
write_result_txt();
//    FILE *fp;
////    char *test = "163631d75986e1d8";
//    char temp[1024];
//    fp = fopen("d:\\Wittower_ID_License", "rb");
//    if (fp == NULL)
//    {
//        qDebug() << "没找到！";
//    }
//    fgets(temp, 1024,fp);
////    fputs(test, fp);
////    for(int i = 0; i < 16; i++)
////    {
////        temp[i] = fgetc(fp);;
////        qDebug() << temp[i];
//////        fputc(temp, fp);
////    }
//    qDebug() << temp;
//    fclose(fp);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::write_result_txt()
{
    qDebug() << "开始写入" << QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QFile f("d:\\result.txt");
    if(!f.open(QIODevice::ReadWrite | QIODevice::Append))   //以读写且追加的方式写入文本
    {
        qDebug() << "打开文件失败";
        return;
    }
    QTextStream txtOutput(&f);
    QString str = "@time：" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + "  ";
    txtOutput << str;
    str = "@sig_out.movement：" + QString::number(1) + " ";
    txtOutput << str;
    str = "心率：" + QString::number(99) + " ";
    txtOutput << str;
    str = "呼吸率：" + QString::number(16) + " ";
    txtOutput << str;
    str = "心率波形：";
    for(int i = 0; i < 40; i++)
    {
        str = str + QString::number(180) + " ";
    }
    txtOutput << str;
    str = "呼吸波形：";
    for(int i = 0; i < 40; i++)
    {
        str = str + QString::number(200) + " ";
    }
    txtOutput << str;
    str = "总能量波形：" + QString::number(66) + " ";
    txtOutput << str;
    txtOutput << "\n";
    f.close();
}

