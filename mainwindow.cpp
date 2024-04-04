#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(0);

    QFile file(":/style.qss");
    if(file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }


    screen = new QLineEdit();
    screen->setReadOnly(true);
    layout->addWidget(screen, 0, 0, 1, 4);

    zero = new QPushButton("0");
    layout->addWidget(zero, 5, 0, 1, 2);
    one = new QPushButton("1");
    layout->addWidget(one, 4, 0);
    two = new QPushButton("2");
    layout->addWidget(two, 4, 1);
    three = new QPushButton("3");
    layout->addWidget(three, 4, 2);
    four = new QPushButton("4");
    layout->addWidget(four, 3, 0);
    five = new QPushButton("5");
    layout->addWidget(five, 3, 1);
    six = new QPushButton("6");
    layout->addWidget(six, 3, 2);
    seven = new QPushButton("7");
    layout->addWidget(seven, 2, 0);
    eight = new QPushButton("8");
    layout->addWidget(eight, 2, 1);
    nine = new QPushButton("9");
    layout->addWidget(nine, 2, 2);

    plus = new QPushButton("+");
    plus->setObjectName("orange");
    layout->addWidget(plus, 4, 3);
    multiplication = new QPushButton("*");
    multiplication->setObjectName("orange");
    layout->addWidget(multiplication, 2, 3);
    minus = new QPushButton("-");
    minus->setObjectName("orange");
    layout->addWidget(minus, 3, 3);
    division = new QPushButton("/");
    division->setObjectName("orange");
    layout->addWidget(division, 1, 3);
    procent = new QPushButton("%");
    procent->setObjectName("white");
    layout->addWidget(procent, 1, 2);
    plusminus = new QPushButton("+/-");
    plusminus->setObjectName("white");
    layout->addWidget(plusminus, 1, 1);

    equal = new QPushButton("=");
    layout->addWidget(equal, 5, 3);
    clear = new QPushButton("AC");
    clear->setObjectName("white");
    layout->addWidget(clear, 1, 0);
    dot = new QPushButton(".");
    layout->addWidget(dot, 5, 2);

    setLayout(layout);


    connect(zero, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(one, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(two, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(three, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(four, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(five, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(six, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(seven, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(eight, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(nine, &QPushButton::clicked, this, &MainWindow::digit_pressed);


    connect(plus, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(minus, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(multiplication, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(division, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(procent, &QPushButton::clicked, this, &MainWindow::operator_pressed);
    connect(plusminus, &QPushButton::clicked, this, &MainWindow::operator_pressed);

    connect(dot, &QPushButton::clicked, this, &MainWindow::dot_pressed);

    connect(equal, &QPushButton::clicked, this, &MainWindow::equal_pressed);
    connect(clear, &QPushButton::clicked, this, &MainWindow::on_clear_pressed);
}

void MainWindow::digit_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    double labelNumber;
    QString newLabel;

    if (currentOperation != NONE && !secNumEntered) {
        labelNumber = button->text().toDouble();
        secNumEntered = true;
    } else {
        labelNumber = (screen->text() + button->text()).toDouble();
    }

    newLabel = QString::number(labelNumber, 'g', 15);
    screen->setText(newLabel);
}

void MainWindow::operator_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    curVal = screen->text().toDouble();
    button->setChecked(true);
    secNumEntered = false;

    if (button == plus) currentOperation = PLUS;
    else if (button == minus) currentOperation = MINUS;
    else if (button == multiplication) currentOperation = MUL;
    else if (button == division) currentOperation = DIV;
    else if (button == procent) currentOperation = PROC;
    else if (button == plusminus) currentOperation = PLUSMINUS;

    screen->clear();
}

void MainWindow::dot_pressed()
{
    if(!screen->text().contains(".")){
        screen->setText(screen->text() + ".");
    }
}

void MainWindow::equal_pressed()
{
    double num2 = screen->text().toDouble();
    double result;

    switch (currentOperation) {
    case PLUS:
        result = curVal + num2;
        break;
    case MINUS:
        result = curVal - num2;
        break;
    case MUL:
        result = curVal * num2;
        break;
    case DIV:
        result = curVal / num2;
        break;
    case PROC:
        result = std::fmod(curVal, num2);
        break;
    case PLUSMINUS:
        result = curVal * (-1);
        break;
    default:
        return;
    }

    screen->setText(QString::number(result));
    currentOperation = NONE;
}

void MainWindow::on_clear_pressed()
{
    screen->setText("0");
    currentOperation = NONE;
    secNumEntered = false;
    curVal = 0;

    plus->setChecked(false);
    minus->setChecked(false);
    multiplication->setChecked(false);
    division->setChecked(false);
    procent->setChecked(false);
}

MainWindow::~MainWindow() {}
