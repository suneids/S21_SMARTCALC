#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QKeyEvent>
#include <QMenu>
#include <QAction>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void ShowCalcPage();
    void AddSymbol();
    void AddTrigonometryFunc();
    void AddMathFunc();
    void RemoveLastSymbol();
    void RemoveAllSymbols();
    void Calculate();
    void AddPoint();

    void ShowGraphPage();
    void CreateGraph();

    void ShowCreditPage();
    void CalculateMontlyPayment();
    void ChangePaymentType();

    void ShowDepositPage();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *e);
private:
    void ConfigureCalcPage();
    QMenu *trigonometry;
    QList<QAction*> trigonometry_funcs;
    Ui::MainWindow *ui;
    QString Convert(long double value, int prec);
    void Replace(QString *str, QString old_, QString new_);
    double min(QVector<double>);
    double max(QVector<double>);

    void ConfigureGraphPage();
    long double CalcuteY(QString x, int *error);

    void ConfigureCreditPage();

    void ConfigureDepositPage();

};
#endif // MAINWINDOW_H
