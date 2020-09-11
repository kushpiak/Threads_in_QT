#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(maxvalue);
    ui->progressBar->setValue(0);
    ui->progressBar->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->progressBar->show();
    for (int i = 0; i<maxvalue;i++)
    {
        ui->progressBar->setValue(i);
    }
    ui->progressBar->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    foo();
}

void MainWindow::foo()
{
    std::unique_lock<std::mutex> lck(_mtx);

    ui->progressBar->show();
    for (int i = 0; i<maxvalue;i++)
    {
        ui->progressBar->setValue(i);//emit setValue(count);
    }
    ui->progressBar->hide();




}
void MainWindow::boo()
{

}


void MainWindow::on_pushButton_3_clicked()
{
/*    ui->progressBar->show();
    std::thread thr(&MainWindow::boo,this);
    thr.join();
    ui->progressBar->hide();
*/
      ui->progressBar->show();

      QThread * thread=new QThread();
      Manager* man = new Manager();
      man->Init(maxvalue);

      // свзяка потока и полезной функции в connection
      connect(thread,SIGNAL(started()),man,SLOT(boo()));
      //останавливает выполнение потока - он испустит finished()
      connect(man,SIGNAL(FinishWork()),thread,SLOT(quit()));
      connect(thread,SIGNAL(finished()),man,SLOT(deleteLater()));
      connect(man,SIGNAL(DelThread()),thread,SLOT(deleteLater()));

      connect(man,SIGNAL(setValue(int)),ui->progressBar,SLOT(setValue(int)));
     // connect(man,SIGNAL(setValue(int)),this,SLOT(onSetValue(int)));
      connect(man,SIGNAL(DelThread()),ui->progressBar,SLOT(hide()));
      man->moveToThread(thread);
      thread->start();


}

void MainWindow::onSetValue(int value)
{
    ui->progressBar->setValue(value);
}

void Manager::Init(int max)
{
    maxvalue = max;
}

Manager::~Manager()
{
    emit DelThread();
}

void Manager::boo()
{
    std::unique_lock<std::mutex> lck(_mtx);
    for (int i = 0; i<maxvalue;i++)
    {
        emit setValue(i);
    }
    emit FinishWork();
}
