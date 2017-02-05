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

private slots:

    void on_save_b_clicked();

    void on_approve_b_clicked();

    void on_validate_b_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
