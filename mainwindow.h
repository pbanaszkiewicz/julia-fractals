#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scale.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QColor>
#include <QPixmap>

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
    void on_pbRun_clicked();

    void on_sliderMaxIt_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Scale *scale;
    QImage *image;
    QGraphicsScene *scene;

    QRgb pixelColor(int iterations_count, int max_iterations);
    int computeEscape(RealPoint R, double param_a, double param_b, double limit, int max_iterations);
};

#endif // MAINWINDOW_H
