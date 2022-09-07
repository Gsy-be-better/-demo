#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QList>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QList<QString> gsy;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString path;
    QString hang_wei(QString);
    QString last_hang_wei(QString);
    void first_line(QString temp);
    void middle_line(QString temp);
    void last_line(QString temp);
private slots:

    void on_choose_clicked();

    void on_change_clicked();

    void on_pushButton_3_clicked();

    void on_cancal_change_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
