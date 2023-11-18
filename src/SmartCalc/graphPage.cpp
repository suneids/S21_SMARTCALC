#include "mainwindow.h"
#include "ui_mainwindow.h"
extern "C" {
#include "../s21_calculate.h"
#include "../s21_lexem_parse.h"
#include "../s21_validator.h"
}
using namespace std;

void MainWindow::ConfigureGraphPage(){
    QObject::connect(ui->plot, SIGNAL(clicked()), this, SLOT(CreateGraph()));
}


void MainWindow::CreateGraph(){
    ui->graph->clearGraphs();
    QString start_xs = ui->start_x->text();
    QString end_xs = ui->end_x->text();
    QString step_xs = ui->step_x->text();
    start_xs.replace(start_xs.indexOf(','), 1, '.');
    step_xs.replace(step_xs.indexOf(','), 1, '.');
    end_xs.replace(end_xs.indexOf(','), 1, '.');
    long double start_x = start_xs.toDouble();
    long double step_x = step_xs.toDouble();
    long double end_x = end_xs.toDouble();
    int error = 0;
    int len = ((end_x - start_x) / step_x + 1);
    if(len > 0){
        QVector<double> x_values, y_values;
        while(start_x <= end_x && !error){
            x_values.append(start_x);
            long double calc_result = CalcuteY(Convert(start_x, 8), &error);
            if(!error)
                y_values.append(calc_result);
            start_x += step_x;
            error = 0;
        }
        if(!error){
            ui->graph->addGraph();
            ui->graph->graph(0)->setData(x_values, y_values);
            ui->graph->xAxis->setRange(min(x_values), max(x_values));
            ui->graph->yAxis->setRange(min(y_values), max(y_values));
            ui->graph->replot();
        }
    }
}

long double MainWindow::CalcuteY(QString x, int *error){
    long double result = 0;
    char* input;
    QByteArray ba =  ui->input->text().toLatin1();
    input=ba.data();
    if(s21_calculation_possible(input)){
        QString q_input = QString::fromStdString((string)input);
        x.replace(x.indexOf(','), 1, '.');
        while(q_input.count('x') > 0){
            Replace(&q_input, "x", x);
        }
        result = s21_calculation((char*)q_input.toStdString().c_str(),  1, error);
    }
    return result;
}

double MainWindow::min(QVector<double> mas){
    double result = 0;
    foreach(double value, mas) {
        if(result == 0){
            result = value;
        }
        else if(result > value){
            result = value;
        }
    }
    return floor(result);
}

double MainWindow::max(QVector<double> mas){
    double result = 0;
    foreach(double value, mas) {
        if(result == 0){
            result = value;
        }
        else if(result < value){
            result = value;
        }
    }
    return ceil(result);
}

