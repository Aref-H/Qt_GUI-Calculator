#include "calculator.h"  // Including our Calculator header file
#include "ui_calculator.h"  // Includeing our Ui header file

double currValue = 0;  // Tracking our current value

// Tracking the last math button pressed
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

// Tracking the last memory button pressed
bool memAddTrig = false;
bool memClearTrig = false;
bool memGetTrig = false;

Calculator::Calculator(QWidget *parent)  // Calculator constructer
    : QMainWindow(parent)  // Our Qmain constructer parent
    , ui(new Ui::Calculator)  // Creating ui class and asigning it to our ui member
{
    ui->setupUi(this);  // Setting up our user interface

    ui->Display->setText(QString::number(currValue));  /* Making sure to show 0.0
                                                          by casting */

    QPushButton *numButtons[10];  // Holding refrence of our QpushButton

    //Assigning signals and slots
    for(int i = 0; i < 10; ++i) {
        // Push button name in Ui
        QString butName = "Button" + QString::number(i);  // Push button name in Ui
        // Sarching for specific widget by providing the name
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        // Whenever our num button released call function NumPressed
        connect(numButtons[i], SIGNAL(released()), this, SLOT (NumPressed()));
    }

    // Connecting our signals to  functions
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathPressed()));

    connect(ui->Equal, SIGNAL(released()), this, SLOT(EqualPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearPressed()));

    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(MemoryPressed()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(MemoryPressed()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(MemoryPressed()));

    connect(ui->DeciPoint, SIGNAL(released()), this, SLOT(DecimalPoint()));
}

Calculator::~Calculator()  // Our destructor to delete user interface
{
    delete ui;
}

// Our function when a number is pressed
void Calculator::NumPressed() {

    // Sender will returne a pointer to our pressed button
    QPushButton *button = (QPushButton *)sender();
    // Getting the numbber that is on the prssed button
    QString butVal = button->text();
    // Getting our current display valvue
    QString displayVal = ui->Display->text();
    // Checking if display value is equal to 0.0 or not
    if((displayVal.toDouble() != 0) || (displayVal.toDouble() != 0.0) ||
        (displayVal == "0.")) {
        QString newVal = displayVal + butVal;  // If equal to nonzero add new value
        double dblNewVal = newVal.toDouble();  // Converting to double

        // Seting up display so it can handle 16 diget before exponent
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    } else if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)) {
        ui->Display->setText(butVal);  // If equal to 0.0 or 0 put butVal init
    }
}

// Our function to get pressed math button
void Calculator::MathPressed() {
    // Each time a math button is pressed we will set these boolians equal to false
        divTrigger = false;
        mulTrigger = false;
        addTrigger = false;
        subTrigger = false;
    // Storing current diplay value and storing it in currValue
    QString displayVal = ui->Display->text();
    currValue = displayVal.toDouble();
    // Checking our sender to get which math button has been pressed
    QPushButton *button = (QPushButton *)sender();
    // Getting math  symbol on button
    QString butVal = button->text();
    // Checking which of our button is clicked
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0) {
        mulTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else {
        subTrigger = true;
    }
    ui->Display->setText(butVal);  // Clearing display to get our second number
}

// Our function to calculate our final number after mathematical operation
void Calculator::EqualPressed() {
    double solution = 0.0;  // Holding our calculation result
    QString displayVal = ui->Display->text();  // Getting our second number
    double dblDisplayVal = displayVal.toDouble();  // Changing our displayVal to double
    // Making sure one of our math button has been pressed
    if(divTrigger || mulTrigger || addTrigger || subTrigger) {
        if(divTrigger) {
            solution = currValue / dblDisplayVal;  // Mathematical operation (Add)
        }
        else if(mulTrigger) {
            solution = currValue * dblDisplayVal;  // ...
        }
        else if(addTrigger) {
            solution = currValue + dblDisplayVal;  // ...
        }
        else {
            solution = currValue - dblDisplayVal;  // ...
        }
    }
    ui->Display->setText(QString::number(solution));  // Putting our result on display
}

// Function to change number sign
void Calculator::ChangeNumberSign() {
    QString displayVal = ui->Display->text();  // Getting our number on our dispaly
    static QRegularExpression reg1("[-]?[1-9.]*");  // Regular expression check
    QRegularExpressionMatch match = reg1.match(displayVal);
    if(match.hasMatch()) {
        double dblDisplayVal = displayVal.toDouble();  // Casting to double
        double dblDisplayValSign = -1 * dblDisplayVal;  // Changing sign
        ui->Display->setText(QString::number(dblDisplayValSign));  // Puting it on display
    }
}

// Function to clear display
void Calculator::ClearPressed() {
    currValue = 0.0;  // Clear the currValue
    ui->Display->setText("");  // make display empety
}

// Function to save in memory
void Calculator::MemoryPressed() {
    static double memOne = 0.0;  // A static double to save the number on display

    // Each time a math button is pressed we will set these boolians equal to false
    memAddTrig = false;
    memClearTrig = false;
    memGetTrig = false;

    // Checking our sender to get which memory button has been pressed
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    // Checking which memory button and what the pressed button should do
    if(QString::compare(butVal, "M+", Qt::CaseInsensitive) == 0) {
        memAddTrig = true;
        if(memOne == 0.0) {
            memOne = displayVal.toDouble();
        }
    } else if(QString::compare(butVal, "M-", Qt::CaseInsensitive) == 0) {
        memClearTrig = true;
        memOne = 0.0;
    } else {
        memGetTrig = true;
        if(memOne == 0.0) {
            ui->Display->setText("EMPETY");
        } else {
            ui->Display->setText(QString::number(memOne));
        }
    }
}

//Function to add decimal point
void Calculator::DecimalPoint() {
    QString displayVal = ui->Display->text();
    static QRegularExpression reg2("[0-9].[0-9]");  /* Regular exprssion to see if there
                                                       is already decimal point or not */
    QRegularExpressionMatch match = reg2.match(displayVal);
    if(match.hasMatch() == 0) {  // if no decimal point, add one
        double dblDisplayVal = displayVal.toDouble();
        ui->Display->setText(QString::number(dblDisplayVal) + ".");
    }
}










