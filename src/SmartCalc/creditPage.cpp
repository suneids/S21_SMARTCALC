#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <math.h>
using namespace std;
void MainWindow::ConfigureCreditPage(){
    QObject::connect(ui->calculatePayments, SIGNAL(clicked()), this, SLOT(CalculateMontlyPayment()));
    QObject::connect(ui->payment_type, SIGNAL(clicked()), this, SLOT(ChangePaymentType()));
}

void MainWindow::CalculateMontlyPayment(){
    QString credit_sums = ui->credit_value->text(),
            credit_percents = ui->credit_percent->text(),
            credit_periods = ui->credit_period->text();
    credit_sums.replace(credit_sums.indexOf(','), 1, '.');
    credit_percents.replace(credit_percents.indexOf(','), 1, '.');
    credit_periods.replace(credit_periods.indexOf(','), 1, '.');
    long double credit_sum = credit_sums.toDouble(),
                credit_percent = credit_percents.toDouble()/100,
                credit_period = credit_periods.toDouble();
    QVector<long double> payments;
    if(ui->payment_type->text() == "Аннуитетный"){
        long double mp = credit_percent/12.0;
        long double kf = (mp*powl((1+mp),12*credit_period))/(powl((1+mp), 12*credit_period)-1);
        payments.append(credit_sum*kf);
        ui->montly_payment->setText(Convert(payments[0], 2));
        ui->overpayment->setText(Convert(credit_sum*kf*12*credit_period - credit_sum, 2));
        ui->total_payout->setText(Convert(credit_sum*kf*12*credit_period,2));
    }
    else{
        long double remained = credit_sum;
        long double base_payment = credit_sum/(credit_period*12);
        long double total_payed = 0;
        for(int i = 0; i < 12*credit_period; i++){
            long double current_payment = base_payment + (remained*credit_percent/12.0);
            remained -= base_payment;
            payments.append(current_payment);
            total_payed += current_payment;
        }
        ui->montly_payment->setText(Convert(payments[0],2)+"\n"+Convert(payments[payments.length()-1],2));
        ui->overpayment->setText(Convert(total_payed - credit_sum, 2));
        ui->total_payout->setText(Convert(total_payed, 2));
    }
}

void MainWindow::ChangePaymentType(){
    if(ui->payment_type->text() == "Аннуитетный"){
        ui->payment_type->setText("Дифференцированный");
    }
    else{
        ui->payment_type->setText("Аннуитетный");
    }
}
