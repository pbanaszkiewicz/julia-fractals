#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateSliderLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scale;
    delete image;
}

void MainWindow::on_pbRun_clicked()
{
    QApplication::setOverrideCursor(Qt::BusyCursor);

    if (!scale) delete scale;
    scale = new Scale(2.5, 2.5, ui->image->width(), ui->image->height());

    if (!image) delete image;
    image = new QImage(ui->image->width(), ui->image->height(), QImage::Format_RGB32);

    int i, max_iterations = ui->sliderMaxIt->value();
    bool AA = ui->cbAntialiasing->isChecked();
    double a = ui->parameterA->value(), b = ui->parameterB->value();
    double limit = ui->escapeLimit->value();

    for (int x = 0; x < ui->image->width(); x++)
    {
        for (int y = 0; y < ui->image->height(); y++)
        {
            RealPoint R = scale->castToReal(ScreenPoint(x, y));

            i = computeEscape(R, a, b, limit, max_iterations);

            if (AA)
            {
                double dx = scale->r_w / scale->s_w / 4.0, dy = scale->r_h / scale->s_h / 4.0;

                std::vector<int> v;
                v.push_back(i);
                v.push_back(computeEscape(RealPoint(R.x - dx, R.y - dy), a, b, limit, max_iterations));
                v.push_back(computeEscape(RealPoint(R.x - dx, R.y + dy), a, b, limit, max_iterations));
                v.push_back(computeEscape(RealPoint(R.x + dx, R.y + dy), a, b, limit, max_iterations));
                v.push_back(computeEscape(RealPoint(R.x + dx, R.y - dy), a, b, limit, max_iterations));

                // count min escape value
                //std::vector<int>::iterator min = std::min_element(v.begin(), v.end());
                //i = *min;

                // count average escape value
                i = std::accumulate(v.begin(), v.end(), 0) / v.size();
            }

            image->setPixel(x, y, pixelColor(i, max_iterations));
        }
    }

    ui->image->setPixmap(QPixmap::fromImage(*image));

    QApplication::restoreOverrideCursor();
}


QRgb MainWindow::pixelColor(int iterations_count, int max_iterations)
{
    double r, g, b;
    double L, d = 256. / 20.;

    switch (ui->cbColoring->currentIndex())
    {
    case 0:
        // "black-white"
        if (iterations_count >= max_iterations) return QColor(255, 255, 255).rgb();
        else return QColor(0, 0, 0).rgb();

    case 1:
        // "gray"
        return QColor(iterations_count / max_iterations * 255, iterations_count / max_iterations * 255, iterations_count / max_iterations * 255).rgb();

    case 2:
        // "trigonometric"
        r = 127.0 * (1 - std::cos(M_PI * iterations_count / max_iterations));
        if (r < 0) r = 0;
        g = 127.0 * (1 - std::cos(1.5 * M_PI * iterations_count / max_iterations));
        if (g < 0) g = 0;
        b = 127.0 * (1 - std::cos(1.9 * M_PI * iterations_count / max_iterations));
        if (b < 0) b = 0;
        return QColor(r, g, b).rgb();

    default:
        // "rainbow-ish"
        L = (1 - double(iterations_count) / max_iterations) * 100.;
        if (L <= 0) return QColor(0, 0, 0).rgb();
        else if (L < 20) return QColor(255 - d * L, 0, 255).rgb();
        else if (L < 40) return QColor(0, d * (L - 20), 255).rgb();
        else if (L < 60) return QColor(0, 255, 255 - d * (L - 40)).rgb();
        else if (L < 80) return QColor(d * (L - 60), 255, 0).rgb();
        else if (L < 100) return QColor(255, 255 - d * (L - 80), 0).rgb();
        else return QColor(0, 0, 0).rgb();
    }
}

void MainWindow::updateSliderLabels()
{
    ui->LMaxIt->setText(QString::number(ui->sliderMaxIt->value()));
}

void MainWindow::on_sliderMaxIt_valueChanged(int value)
{
    ui->LMaxIt->setText(QString::number(value));
}

int MainWindow::computeEscape(RealPoint R, double param_a, double param_b, double limit, int max_iterations)
{
    int i;
    for (i = 0; i < max_iterations; i++)
    {
        double tmp = R.x * R.x - R.y * R.y + param_a;
        R.y = 2 * R.x * R.y + param_b;
        R.x = tmp;

        if (std::sqrt(R.x * R.x + R.y * R.y) > limit)
        {
            break;
        }
    }
    return i;
}
