//
// Created by Macross on 8/18/2021.
//

#include "include/barnes-hut/point.hpp"
#include <iostream>
#include <cmath>



namespace space
{
    sPoint::sPoint()
    {
        //std::cout << "sPoint NAN constructor ran\n";
        this->x = NAN;
        this->y = NAN;
    }

    sPoint::sPoint(double _x, double _y)
    {
        //std::cout << std::fixed << "sPoint normal constructor (" << _x << ", " << _y << ")\n";
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

    int sPoint::Compare(const sPoint& target_point) const
    {
        if (target_point.x < this->x) {
            if (target_point.y > this->y) {
                return NORTH_WEST;
            }
            else if (target_point.y < this->y) {
                return SOUTH_WEST;
            }
            else if (target_point.y == this->y) {
                return NORTH_WEST; // WEST will go NORTH_WEST
            }
        }
        else if (target_point.x > this->x) {
            if (target_point.y > this->y) {
                return NORTH_EAST;
            }
            else if (target_point.y < this->y) {
                return SOUTH_EAST;
            }
            else if (target_point.y == this->y) {
                return SOUTH_EAST; // EAST will go SOUTH_EAST
            }
        }
        else if (target_point.x == this->x && target_point.y != this->y) {
            if (target_point.y > this->y) {
                return NORTH_EAST; // NORTH will go NORTH_EAST
            }
            else if (target_point.y < this->y) {
                return SOUTH_WEST; // SOUTH will go SOUTH_WEST
            }
        }

        throw std::invalid_argument("Point occupies the same position");
    }

    double sPoint::DistanceTo(const sPoint &point)
    {
        return sqrt((this->y - point.y) * (this->y - point.y) +
                    (this->x - point.x) * (this->x - point.x));
    }


    bool sPoint::IsValid() const
    {
        return this->x != NAN && this->y != NAN;
    }


    std::string sPoint::GetCoordinateString() const
    {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }
}