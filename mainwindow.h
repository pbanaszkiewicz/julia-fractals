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

private:
    Ui::MainWindow *ui;
    Scale *scale;
    QImage *image;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
