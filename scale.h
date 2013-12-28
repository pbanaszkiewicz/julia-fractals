#ifndef SCALE_H
#define SCALE_H

#include "point.cpp"

typedef Point<long> ScreenPoint;
typedef Point<double> RealPoint;

class Scale
{
public:
    Scale(double real_width, double real_height, int screen_width, int screen_height);

    ScreenPoint castToScreen(RealPoint r);
    RealPoint castToReal(ScreenPoint s);

private:
    double r_w, r_h;
    int s_w, s_h;

    double a1, b1, a2, b2;  // coefficients used in calculating real-to-screen
    double a3, b3, a4, b4;  // coefficients used in calculating screen-to-real
    void calculate_coefficients();
};

#endif // SCALE_H
