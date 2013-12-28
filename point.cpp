#ifndef _H_POINT_
#define _H_POINT_

template <class T>
class Point
{
public:
    Point(T x, T y) : x(x), y(y) {}
    T x;
    T y;
};

#include <QDebug>
template <class T>
QDebug& operator<<(QDebug &dbg, const Point<T> &p)
{
    dbg.nospace() << "(" << p.x << ", " << p.y << ")";

    return dbg.space();
}

#endif
