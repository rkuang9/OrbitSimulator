//
// Created by Macross on 8/18/2021.
//
#pragma once
#ifndef ORBITSIMULATOR_POINT_HPP
#define ORBITSIMULATOR_POINT_HPP

#include <iostream>

namespace space
{
    namespace constants
    {
        const double AU = 1.496e11;
        const double ly = 9.461e15;
        const double G = 6.673e-11;
    }

    enum Quadrant
    {
        NORTH_WEST = 0,
        NORTH_EAST = 1,
        SOUTH_WEST = 2,
        SOUTH_EAST = 3,
    };

    class sPoint
    {
    public:
        double x;
        double y;

        sPoint();

        sPoint(const sPoint &point) = default;

        sPoint(double x, double y);

        int Compare(const sPoint &point) const;

        double DistanceTo(const sPoint &point);

        double AngularSeparation(const sPoint &point);

        bool IsValid() const;

        std::string GetCoordinateString() const;

        /** Getters Setters */
        double GetX();

        double GetY();

        void SetX(double x);

        void SetY(double y);

        void SetXY(double x, double y);
    };
}


#endif //ORBITSIMULATOR_POINT_HPP
