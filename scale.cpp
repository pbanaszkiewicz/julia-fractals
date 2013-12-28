#include "scale.h"

Scale::Scale(double real_width, double real_height, int screen_width, int screen_height)
    : r_w(real_width), r_h(real_height), s_w(screen_width), s_h(screen_height)
{
    // compute all coefficients beforehand //
    calculate_coefficients();
}

void Scale::calculate_coefficients()
{
    // real-to-screen conversion
    a1 = s_w / r_w;
    b1 = 0.5 * s_w;
    a2 = -s_h / r_h;
    b2 = 0.5 * s_h;

    // screen-to-real conversion
    a3 = r_w / s_w;
    b3 = -0.5 * r_w;
    a4 = -r_h / s_h;
    b4 = 0.5 * r_h;
}

ScreenPoint Scale::castToScreen(RealPoint r)
{
    return ScreenPoint(a1 * r.x + b1, a2 * r.y + b2);
}

RealPoint Scale::castToReal(ScreenPoint s)
{
    return RealPoint(a3 * s.x + b3, a4 * s.y + b4);
}
