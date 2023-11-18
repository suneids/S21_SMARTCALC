#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <sstream>
#include <QRegularExpression>
extern "C" {
#include "../s21_calculate.h"
#include "../s21_common_funcs.h"
#include "../s21_validator.h"
}
using namespace std;

void MainWindow::ConfigureCalcPage(){
    trigonometry = new QMenu(this);
    trigonometry_funcs.append(new QAction("sin",this));
    trigonometry_funcs.append(new QAction("cos",this));
    trigonometry_funcs.append(new QAction("tan",this));
    trigonometry_funcs.append(new QAction("asin",this));
    trigonometry_funcs.append(new QAction("acos",this));
    trigonometry_funcs.append(new QAction("atan",this));
    for(int i = 0; i < trigonometry_funcs.length(); i++){
        trigonometry_funcs[i]->setObjectName(trigonometry_funcs[i]->text());
        trigonometry->addAction(trigonometry_funcs[i]);
        connect(trigonometry_funcs[i], SIGNAL(triggered()), this, SLOT(AddTrigonometryFunc()));
    }
    ui->trigonometry->setMenu(trigonometry);
    ui->trigonometry->setPopupMode(QToolButton::ToolButtonPopupMode::InstantPopup);
    int count = ui->controls->count();
    for(int i = 0; i < count; i++){
        if(ui->controls->itemAt(i)->widget()->objectName() != "trigonometry"){
            QPushButton *currentButton = dynamic_cast<QPushButton*>(ui->controls->itemAt(i)->widget());
            QString btn_text = currentButton->text();
            if(QString("mod+-/*1234567890()").count(btn_text) > 0 && QString::compare(btn_text, QString("+/-")) != 0)
                QObject::connect(currentButton, SIGNAL(clicked()), this, SLOT(AddSymbol()));
        }
    }
    QObject::connect(ui->goto_calc, SIGNAL(clicked()), this, SLOT(ShowCalcPage()));
    QObject::connect(ui->goto_graph, SIGNAL(clicked()), this, SLOT(ShowGraphPage()));
    QObject::connect(ui->goto_credit, SIGNAL(clicked()), this, SLOT(ShowCreditPage()));
    QObject::connect(ui->goto_deposit, SIGNAL(clicked()), this, SLOT(ShowDepositPage()));

    QObject::connect(ui->ln, SIGNAL(clicked()), this, SLOT(AddMathFunc()));
    QObject::connect(ui->log, SIGNAL(clicked()), this, SLOT(AddMathFunc()));
    QObject::connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(AddMathFunc()));
    QObject::connect(ui->backspace, SIGNAL(clicked()), this, SLOT(RemoveLastSymbol()));
    QObject::connect(ui->clear, SIGNAL(clicked()), this, SLOT(RemoveAllSymbols()));
    QObject::connect(ui->finish, SIGNAL(clicked()), this, SLOT(Calculate()));
    QObject::connect(ui->point, SIGNAL(clicked()), this, SLOT(AddPoint()));
}

MainWindow::~MainWindow()
{
    delete trigonometry;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    char *input = (char*)ui->input->text().toStdString().c_str();
    if(ui->input->text() == "Некорректное выражение")
        ui->input->setText("");
    if(ui->pages->currentIndex() != 0)
        return;
    if(ui->input->text().length() > 254)
        return;

    char key = QString((char)e->key()).toLower().toStdString()[0];
    if(e->key() == Qt::Key_Backspace){
        QString deleted_last = ui->input->text();
        deleted_last.chop(1);
        ui->input->setText(deleted_last);
    }
    else if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return){
        Calculate();
    }
    else if(s21_add_possible(input, &key)){
        ui->input->setText(ui->input->text() + key);
    }
}

//int MainWindow::s21_calculation_possible(char *input_str)
//{
//    int result = 0;
//    QString q_input = QString(input_str);
//    if(q_input.count('(') != q_input.count(')')){}

//    else{
//        result = 1;
//    }
//    return result;
//}

void MainWindow::AddSymbol(){
    char *button_text = (char*)(dynamic_cast<QPushButton*>(sender())->text().toStdString().c_str());
    char *input = (char*)ui->input->text().toStdString().c_str();
    if(s21_add_possible(input, button_text) && strlen(input) < 255){
        ui->input->setText(ui->input->text() + button_text);
    }
}

void MainWindow::Calculate(){
    char* input;
    QByteArray ba =  ui->input->text().toLatin1();
    input=ba.data();
    int error = 0;
    if(s21_calculation_possible(input)){
        QString q_input = QString::fromStdString((string)input);
        QString x_value = ui->x_value->text();
        x_value.replace(x_value.indexOf(','), 1, '.');
        while(q_input.count('x') > 0){
            q_input.replace(q_input.indexOf('x'), x_value.length(), x_value);
        }
        QString calc_result = Convert(s21_calculation((char*)q_input.toStdString().c_str(), 0, &error), 7);
        if(!error){
            ui->input->setText(calc_result);
        }
        else{
            ui->input->setText("Некорректное выражение");
        }
    }
}

void MainWindow::AddTrigonometryFunc()
{
    char *input = (char*)ui->input->text().toStdString().c_str();
    if(ui->input->text() == "Некорректное выражение")
        ui->input->setText("");
    QAction *act = qobject_cast<QAction*>(sender());
    if(act && s21_can_add_function(input)){
        ui->input->setText(ui->input->text()+act->objectName()+"(");
    }
}

void MainWindow::AddMathFunc()
{
    char *input = (char*)ui->input->text().toStdString().c_str();
    if(ui->input->text() == "Некорректное выражение")
        ui->input->setText("");
    QPushButton *act = qobject_cast<QPushButton*>(sender());
    if(s21_can_add_function(input)){
        ui->input->setText(ui->input->text()+act->objectName()+"(");
    }
}

void MainWindow::RemoveLastSymbol(){
    QString new_text = ui->input->text();
    new_text.chop(1);
    ui->input->setText(new_text);
}

void MainWindow::RemoveAllSymbols(){
    ui->input->setText("");
}

//int MainWindow::s21_add_possible(char *key)
//{
//    int result = 0;
//    char kf_symbol = key[0];
//    if(s21_is_oper(key)){
//        if(CanAddOperator(key))
//            result = 1;
//    }
//    else if(s21_is_func(key)){
//        if(CanAddFunction())
//            result = 1;
//    }
//    else if(s21_is_digit(kf_symbol) || kf_symbol == 'x'){
//        if(CanAddDigit(key))
//            result = 1;
//    }
//    return result;
//}

//int MainWindow::CanAddOperator(char *key){
//    int result = 0;
//    char kf_symbol = key[0];
//    QString current_input = ui->input->text();
//    char last_symbol = current_input.toStdString()[current_input.length()-1];
//    if((current_input.count("(") == current_input.count(")")) && (kf_symbol == ')')){
//        qDebug() << 1 << key;
//    }
//    else if(current_input.length() == 0 && QString("(-").count(kf_symbol) == 0){
//        qDebug() << 2.1 << key;
//    }
//    else if(s21_is_oper(&last_symbol) && QString("()").count(kf_symbol) == 0){
//        if(QString("()").count(last_symbol) > 0){
//            result = 1;
//        }
//        qDebug() << 5 << key;
//    }
//    else if(kf_symbol == '(' && !s21_is_oper(&last_symbol) ){
//        qDebug() << 6 << key;
//    }
//    else if(kf_symbol == ')' && !s21_is_digit(last_symbol) && QString(")x").count(kf_symbol) == 0){
//        qDebug() << 7<< key;
//    }
//    else{
//        result = 1;
//    }
//    return result;
//}

//int MainWindow::CanAddFunction(){
//    int result = 0;
//    QString current_input = ui->input->text();
//    char last_symbol = current_input.toStdString()[current_input.length()-1];
//    if(s21_is_digit(last_symbol)){

//    }
//    else{
//        result = 1;
//    }
//    return result;
//}

//int MainWindow::CanAddDigit(char *key){
//    int result = 0;
//    char kf_symbol = key[0];
//    QString current_input = ui->input->text();
//    char last_symbol = current_input.toStdString()[current_input.length()-1];
//    if((s21_is_digit(last_symbol) || last_symbol == 'x') && kf_symbol == 'x'){
//        qDebug() << 3 << key;
//    }
//    else if(last_symbol == ')'){
//        qDebug() << 3.1 << key;
//    }
//    else{
//        result = 1;
//    }
//    return result;
//}

QString MainWindow::Convert(long double value, int prec) {
    return QString::number(value, 'f', prec);
}

void MainWindow::Replace(QString *str, QString old_, QString new_){
    QString temp = "";
    int id = str->indexOf(old_);
    for(int i = 0; i < id; i++){
        temp += str->toStdString().c_str()[i];
    }
    temp = temp + new_;
    for(int i = id+1; i < str->length(); i++){
        temp += str->toStdString().c_str()[i];
    }
    *str = temp;
}

void MainWindow::AddPoint(){
    QString input = ui->input->text();
    char c = input.toStdString().c_str()[input.length()-1];
    if(s21_is_digit(c)){
        if(input.count(".") == 0){
            ui->input->setText(input + '.');
        }
        else{
            QStringList lex = ui->input->text().split(QRegularExpression("[+*:-]"), Qt::SkipEmptyParts);
            if(lex[lex.length()-1].count('.') == 0){
               ui->input->setText(input + '.');
            }
        }
    }
}
