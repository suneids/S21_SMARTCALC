#include "mainwindow.h"
#include <QApplication>
#include <sstream>
#include <iomanip>
#include <limits>
#include <QDebug>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;    
    w.show();
    return a.exec();
}
