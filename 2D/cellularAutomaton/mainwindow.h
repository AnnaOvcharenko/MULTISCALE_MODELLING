#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPainter>
#include "grid.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_drawButton_clicked();

    void on_startButton_clicked();

    void on_stopButton_clicked();
    static void thr(MainWindow* m);

private:
    Ui::MainWindow *ui;
    bool isButtonDrawClicked=false;
    bool isButtonStartClicked=false;
    bool isButtonStopClicked=false;
    bool isUpdate=false;
    Grid grid;
};

#endif // MAINWINDOW_H
