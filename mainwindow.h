#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;



private slots:
    void digit_pressed();
    void on_pushButton_dot_released();
    void on_pushButton_delete_released();
    void on_pushButton_percent_released();
    void on_pushButton_plus_released();
    void on_pushButton_minus_released();
    void on_pushButton_multiply_released();
    void on_pushButton_divide_released();
    void on_pushButton_equals_released();
    void on_pushButton_clear_released();
};

#endif // MAINWINDOW_H
