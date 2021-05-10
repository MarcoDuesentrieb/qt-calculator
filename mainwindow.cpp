#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>
#define MUL u'\u00D7'
#define DIV u'\u00F7'

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::digit_pressed()
{
    qDebug() << sender()->objectName();
    QPushButton *button = (QPushButton*)sender();
    QString text = ui->label->text();
    // ui->label->text().append(button->text());
    double labelNumber;
    QString labelString;
    if(text == "0")
        text = button->text();
    else
        text.append(button->text());
    // labelNumber = (ui->label->text() + button->text()).toDouble();
    // labelString =  QString::number(labelNumber, 'g', 15);

     ui->label->setText(text);
}

void MainWindow::on_pushButton_dot_released()
{
    QString text = ui->label->text();
    QRegExp seperator("[-+%u'\u00D7'u'\u00F7']");
    QStringList list_temp = text.split(seperator);
    QString current_number = list_temp.last();
    if(!current_number.contains('.'))
        ui->label->setText(text + '.');
}

void MainWindow::on_pushButton_delete_released()
{
    QString labelText = ui->label->text();
    if(labelText.size())
    {
        QString newText = labelText.left(labelText.size()-1);
        ui->label->setText(newText);
    }
}

void MainWindow::on_pushButton_percent_released()
{
    QString labelText = ui->label->text();
    if(labelText.endsWith('+') || labelText.endsWith('-')
            || labelText.endsWith(u'\u00D7') || labelText.endsWith(u'\u00F7')
            || labelText.endsWith('%'))
    {
        labelText[labelText.count()-1] = '%';
    }
    else
    {
        labelText.append('%');
    }
    ui->label->setText(labelText);
}


void MainWindow::on_pushButton_plus_released()
{
    QString labelText = ui->label->text();
    if(labelText.endsWith('+') || labelText.endsWith('-')
            || labelText.endsWith(u'\u00D7') || labelText.endsWith(u'\u00F7')
            || labelText.endsWith('%'))
    {
        labelText[labelText.count()-1] = '+';
    }
    else
    {
        labelText.append('+');
    }
    ui->label->setText(labelText);
}

void MainWindow::on_pushButton_minus_released()
{
    QString labelText = ui->label->text();
    if(labelText.endsWith('+') || labelText.endsWith('-'))
    {
        labelText[labelText.count()-1] = '-';
    }
    else
    {
        labelText.append('-');
    }
    ui->label->setText(labelText);
}

void MainWindow::on_pushButton_multiply_released()
{
    QString labelText = ui->label->text();
    if(labelText.endsWith('+') || labelText.endsWith('-')
            || labelText.endsWith(u'\u00D7') || labelText.endsWith(u'\u00F7')
            || labelText.endsWith('%'))
    {
        labelText[labelText.count()-1] = u'\u00D7';
    }
    else
    {
        labelText.append(u'\u00D7');
    }
    ui->label->setText(labelText);
}

void MainWindow::on_pushButton_divide_released()
{
    QString labelText = ui->label->text();
    if(labelText.endsWith('+') || labelText.endsWith('-')
            || labelText.endsWith(u'\u00D7') || labelText.endsWith(u'\u00F7')
            || labelText.endsWith('%'))
    {
        labelText[labelText.count()-1] = u'\u00F7';
    }
    else
    {
        labelText.append(u'\u00F7');
    }
    ui->label->setText(labelText);
}

void MainWindow::on_pushButton_equals_released()
{
    // String slicing
    // First create list of numbers and operators

    QString text = ui->label->text();

    QRegExp seperator("[-+%u'\u00D7'u'\u00F7']");
    QString operators("[+-%u'\u00D7'u'\u00F7'");


    QStringList list_temp = text.split(seperator);
    QList<double> list_number;
    foreach(QString str, list_temp)
        list_number.push_back(str.toDouble());

    QStringList list_operator;
    for(uint8_t i = 0; i < text.count(); i++)
    {
        QChar c = text.at(i);
        if(operators.contains(c))
            list_operator.append(c);
    }

    qDebug() <<  list_number;
    qDebug() <<  list_operator;

    // Percent
    while(list_operator.contains(QString('%')))
    {
        for(uint8_t i = 0; i < list_operator.count(); i++)
        {
            if(list_operator.at(i) == QString('%'))
            {
                double left_op = list_number[i];
                double partial_result = left_op / 100.0;

                list_number[i] = partial_result;
                list_operator.removeAt(i);
                qDebug() <<  "Result:\n" << list_number;
                break;
            }
        }
    }
    // Multiplication
    while(list_operator.contains(QString(MUL)))
    {
        for(uint8_t i = 0; i < list_operator.count(); i++)
        {
            if(list_operator.at(i) == QString(MUL))
            {
                double left_op = list_number[i];
                double right_op = list_number[i+1];
                double partial_result = left_op * right_op;

                list_number[i] = partial_result;
                list_number.removeAt(i+1);
                list_operator.removeAt(i);
                qDebug() <<  "Result:\n" << list_number;
                break;
            }
        }
    }
    // Division
    while(list_operator.contains(QString(DIV)))
    {
        for(uint8_t i = 0; i < list_operator.count(); i++)
        {
            if(list_operator.at(i) == QString(DIV))
            {
                double left_op = list_number[i];
                double right_op = list_number[i+1];
                double partial_result = left_op / right_op;

                list_number[i] = partial_result;
                list_number.removeAt(i+1);
                list_operator.removeAt(i);
                qDebug() <<  "Result:\n" << list_number;
                break;
            }
        }
    }
    // Addition
    while(list_operator.contains(QString('+')))
    {
        for(uint8_t i = 0; i < list_operator.count(); i++)
        {
            if(list_operator.at(i) == QString('+'))
            {
                double left_op = list_number[i];
                double right_op = list_number[i+1];
                double partial_result = left_op + right_op;

                list_number[i] = partial_result;
                list_number.removeAt(i+1);
                list_operator.removeAt(i);
                qDebug() <<  "Result:\n" << list_number;
                break;
            }
        }
    }
    // Subtraction
    while(list_operator.contains(QString('-')))
    {
        for(uint8_t i = 0; i < list_operator.count(); i++)
        {
            if(list_operator.at(i) == QString('-'))
            {
                double left_op = list_number[i];
                double right_op = list_number[i+1];
                double partial_result = left_op - right_op;

                list_number[i] = partial_result;
                list_number.removeAt(i+1);
                list_operator.removeAt(i);
                qDebug() <<  "Result:\n" << list_number;
                break;
            }
        }
    }


    QString result_as_qstring;
    result_as_qstring = QString::number(list_number.takeAt(0), 'g', 15);
    ui->label->setText(result_as_qstring);
    qDebug() <<  "End of calculation";

}

void MainWindow::on_pushButton_clear_released()
{
    ui->label->setText("0");
}


