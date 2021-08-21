//
// Created by Macross on 8/18/2021.
//
#pragma once
#ifndef ORBITSIMULATOR_POINT_HPP
#define ORBITSIMULATOR_POINT_HPP

namespace space
{
    const double AU = 1.496e11;

    enum
    {
        NORTH_WEST = 0,
        NORTH_EAST = 1,
        SOUTH_WEST = 2,
        SOUTH_EAST = 3,
    };

    struct sPoint
    {

        double x, y;

        sPoint() = default;

        sPoint(double x, double y);

        double GetX();

        double GetY();

        void SetX(double x);

        void SetY(double y);

        void SetXY(double x, double y);

        int Compare(sPoint target_point);

        double DistanceTo(sPoint point);
    };
}


#endif //ORBITSIMULATOR_POINT_HPP
