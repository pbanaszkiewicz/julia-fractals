#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scale;
    delete image;
}

void MainWindow::on_pbRun_clicked()
{
    qDebug() << ui->image->size();

    if (!scale) delete scale;
    scale = new Scale(2.5, 2.5, ui->image->width(), ui->image->height());

    if (!image) delete image;
    image = new QImage(ui->image->width(), ui->image->height(), QImage::Format_RGB32);

//    ScreenPoint p = scale->castToScreen(RealPoint(0, 0));

//    image->setPixel(p.x, p.y, qRgb(255, 255, 255));
//    ui->image->setPixmap(QPixmap::fromImage(*image));

//    RealPoint s = scale->castToReal(ScreenPoint(ui->image->width(), ui->image->height()));
//    qDebug() << s.x << s.y;

    bool mark_white = false;
    double a = 0.238, b = 0.519;
    double limit = 2.0;

    for (int x = 0; x < ui->image->width(); x++)
    {
        for (int y = 0; y < ui->image->height(); y++)
        {
            RealPoint R = scale->castToReal(ScreenPoint(x, y));
            mark_white = true;

            for (int i = 0; i < 250; i++)
            {
                double tmp = R.x * R.x - R.y * R.y + a;
                R.y = 2 * R.x * R.y + b;
                R.x = tmp;

                if (std::sqrt(R.x * R.x + R.y * R.y) > limit)
                {
                    mark_white = false;
                    break;
                }
            }

            if (mark_white)
                image->setPixel(x, y, qRgb(255, 255, 255));
        }
    }

    ui->image->setPixmap(QPixmap::fromImage(*image));
}
