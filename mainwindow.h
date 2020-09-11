#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mutex>
#include <thread>
namespace Ui {
class MainWindow;
}
class Manager: public QObject
{
Q_OBJECT
public:
    void Init(int max);
    ~Manager();
signals:
    void FinishWork();
    void setValue(int);
    void DelThread();
public slots:
    void boo();

private:
    int maxvalue;
    std::mutex _mtx;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void onSetValue(int value);
    void boo();

signals:



private:
    Ui::MainWindow *ui;
    const int maxvalue = 200000;
    void foo();

    std::mutex _mtx;
};

#endif // MAINWINDOW_H
