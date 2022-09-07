#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QDateTime>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    unsigned char receiveResultBuffer[] = {
        0x01, 0xFE, 0x62, 0xA6, 0x9E, 0x64, 0x02, 0x3A, 0x62, 0xA6,
        0x9E, 0x64, 0x02, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
        0xAE, 0xB2, 0xBE};//183
    write_result(receiveResultBuffer);
    read_result();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::write_result(unsigned char* receiveResultBuffer)
{
    QFile f("D:\\result1.txt");
    if(!f.open(QIODevice::ReadWrite | QIODevice::Append))
    {
        qDebug() << "打开文件失败";
        return;
    }
    QTextStream txtOutput(&f);
    QString str = QDateTime::currentDateTime().toString("yyyy#MM#dd#hh#mm#ss#zzz") + "#";
    txtOutput << str;
    for(int i = 12; i < 177; i++)
    {
        str = QString("%1").arg((int)receiveResultBuffer[i],2,16,QLatin1Char('0')).toUpper() + "#";
        txtOutput << str;
    }
    txtOutput << "\n";
    f.close();
}
void MainWindow::read_result()
{
    QFile data("D:\\result1.txt");
    if(false == data.open(QFile::ReadOnly))
    {
        qDebug() << "打开文件失败";
        return;
    }
    char buffer[2048];
    int lineLen = data.readLine(buffer,sizeof(buffer));
    if(lineLen == -1)
    {
        qDebug() << "读取失败";
    }
    qDebug() << buffer;
    qDebug() << QString(buffer).split('#',QString::SkipEmptyParts);
}
