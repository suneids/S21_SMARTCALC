#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iomanip>
#include <limits>
#include <QDebug>
#include <qcustomplot.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QWidget::setFixedSize(520,680);
    ui->setupUi(this);
    ConfigureCalcPage();
    ConfigureGraphPage();
    ConfigureCreditPage();
    ConfigureDepositPage();
    ShowCalcPage();
}

void MainWindow::ShowCalcPage(){
    ui->pages->setCurrentIndex(0);
}

void MainWindow::ShowGraphPage(){
    ui->pages->setCurrentIndex(1);
    ui->lblFunction->setText("y = " + ui->input->text());
}

void MainWindow::ShowCreditPage(){
    ui->pages->setCurrentIndex(3);
}

void MainWindow::ShowDepositPage(){
    ui->pages->setCurrentIndex(2);
}
