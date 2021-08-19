//
// Created by Macross on 8/18/2021.
//

#include "include/barnes-hut/point.hpp"

namespace space
{
    sPoint::sPoint(double _x, double _y)
    {
        this->x = _x;
        this->y = _y;
    }

    double sPoint::GetX()
    {
        return this->x;
    }

    double sPoint::GetY()
    {
        return this->y;
    }

    void sPoint::SetX(double _x)
    {
        this->x = _x;
    }

    void sPoint::SetY(double _y)
    {
        this->y = _y;
    }

    void sPoint::SetXY(double _x, double _y)
    {
        this->x = _x;
        this->y = _y;
    }

}
