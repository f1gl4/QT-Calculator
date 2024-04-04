#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>
#include <QFile>

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>


class MainWindow : public QWidget
{
    Q_OBJECT

    double curVal;
    bool secNumEntered = false;

    QLineEdit *screen;

    QPushButton *one;
    QPushButton *two;
    QPushButton *three;
    QPushButton *four;
    QPushButton *five;
    QPushButton *six;
    QPushButton *seven;
    QPushButton *eight;
    QPushButton *nine;
    QPushButton *zero;

    QPushButton *dot;

    QPushButton *plus;
    QPushButton *minus;
    QPushButton *multiplication;
    QPushButton *division;
    QPushButton *procent;
    QPushButton *plusminus;

    QPushButton *equal;
    QPushButton *clear;

    enum Operation {
        PLUS,
        MINUS,
        DIV,
        MUL,
        PROC,
        PLUSMINUS,
        NONE
    } currentOperation = NONE;

private slots:
    void digit_pressed();
    void dot_pressed();
    void equal_pressed();
    void on_clear_pressed();
    void operator_pressed();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};

#endif // MAINWINDOW_H
