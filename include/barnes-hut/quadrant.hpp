//
// Created by Macross on 8/17/2021.
//

#ifndef ORBITSIMULATOR_QUADRANT_HPP
#define ORBITSIMULATOR_QUADRANT_HPP


#include "include/barnes-hut/point.hpp"
#include "include/barnes-hut/object.hpp"

/**
 * A quadrant is a square in space containing 4 subquarants.
 * Each subquadrant can contain up to 1 object
 *
 */

namespace space
{
    class sQuadrant
    {
    private:
        sQuadrant *parent = nullptr;

        sQuadrant *northwest = nullptr;
        sQuadrant *northeast = nullptr;
        sQuadrant *southwest = nullptr;
        sQuadrant *southeast = nullptr;

        sObject *northwest_object = nullptr;
        sObject *northeast_object = nullptr;
        sObject *southwest_object = nullptr;
        sObject *southeast_object = nullptr;

        // top left coordinate of the quadrant
        sPoint top_left = sPoint();

        // length of the sqare quadrant
        double length = 0;

    public:
        sQuadrant(sPoint top_left_point, double quadrant_length, sQuadrant *parent);

        void SetObjectNW(sObject &object);

        void SetObjectNE(sObject &object);

        void SetObjectSW(sObject &object);

        void SetObjectSE(sObject &object);

        sObject *GetObjectNW();

        sObject *GetObjectNE();

        sObject *GetObjectSW();

        sObject *GetObjectSE();

        sQuadrant *NewSubQuadrantNW();

        sQuadrant *NewSubQuadrantNE();

        sQuadrant *NewSubQuadrantSW();

        sQuadrant *NewSubQuadrantSE();

        double GetWidth();

        double GetHeight();
    };
}

#endif //ORBITSIMULATOR_QUADRANT_HPP
