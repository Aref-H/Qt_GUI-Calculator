#include "calculator.h"           // Header file of our mainwindow
#include <QApplication>           /* Handeling widget , event handeling
                                     and mous movement and so on... */

int main(int argc, char *argv[])  // Our main func
{
    QApplication a(argc, argv);   // Creating application object
    Calculator w;                 // Calculator application object
    w.show();                     // Display calculator option on screen
    return a.exec();              // Putting our application in a excution loop
}
