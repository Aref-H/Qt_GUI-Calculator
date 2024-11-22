#ifndef CALCULATOR_H  // Include gurds
#define CALCULATOR_H

#include <QMainWindow>  // Including our Qmainwindow class
#include <QRegularExpression>

QT_BEGIN_NAMESPACE  // Using Standard Ui namespace
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT  // Base class for all of our Qt objects

public:
    Calculator(QWidget *parent = nullptr);  // Declaring our constructor(no parent)
    ~Calculator();  // Our destructor to free resources

private:
    Ui::Calculator *ui;

// Declaring our slots: this slots will be
// executed when the signal has been submited
private slots:
    void NumPressed();  // When num button pressed
    void MathPressed();  // when math...
    void EqualPressed();  // when equal...
    void ClearPressed();  // When clear
    void MemoryPressed();  // When memory
    void ChangeNumberSign();  // when change...
    void DecimalPoint();  // When decimal...
};

#endif // CALCULATOR_H
