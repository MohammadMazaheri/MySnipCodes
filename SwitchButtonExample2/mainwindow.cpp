#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->switchButton_test->resize(105,35);
    ui->switchButton_test->setValue(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_switchButton_test_valueChanged(bool newvalue)
{
    qDebug() << newvalue;
}
