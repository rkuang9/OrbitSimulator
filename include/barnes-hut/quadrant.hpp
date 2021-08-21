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


        // an array of 4, each representing the 4 possible quadrants
        sQuadrant *quadrant[4] = {nullptr};
        sObject *object[4] = {nullptr};

        // top left coordinate of the quadrant
        sPoint center;

        // length of the sqare quadrant
        double length = NAN;
        double quarter_length = NAN;

    public:
        sQuadrant(sPoint center, double quadrant_length, sQuadrant *parent);

        double GetLength();

        sPoint GetPoint();

        sQuadrant *GetParent();

        bool IsEmpty();

        bool IsEmpty(int quadrant);

        sObject *GetObject(int quadrant);

        void SetObject(sObject &object, int quadrant);

        sObject *RemoveObject(int quadrant);


        sQuadrant *NewSubQuadrant(int quadrant);

    };
}

#endif //ORBITSIMULATOR_QUADRANT_HPP



/*

sObject *northwest_object = nullptr;
sObject *northeast_object = nullptr;
sObject *southwest_object = nullptr;
sObject *southeast_object = nullptr;


sQuadrant *northwest = nullptr;
sQuadrant *northeast = nullptr;
sQuadrant *southwest = nullptr;
sQuadrant *southeast = nullptr;

sObject *RemoveObjectNW();

sObject *RemoveObjectNE();

sObject *RemoveObjectSW();

sObject *RemoveObjectSE();


sQuadrant *NewSubQuadrantNW();

sQuadrant *NewSubQuadrantNE();

sQuadrant *NewSubQuadrantSW();

sQuadrant *NewSubQuadrantSE();


bool IsEmptyNW();

bool IsEmptyNE();

bool IsEmptySW();

bool IsEmptySE();


void SetObjectNW(sObject &object);

void SetObjectNE(sObject &object);

void SetObjectSW(sObject &object);

void SetObjectSE(sObject &object);


sObject *GetObjectNW();

sObject *GetObjectNE();

sObject *GetObjectSW();

sObject *GetObjectSE();
 */
