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
        // a pointer to the parent quadrant of which this is a subquadrant of
        sQuadrant *parent = nullptr;

        // each element representing the 4 possible quadrants objects contained within
        sQuadrant *quadrant[4] = {nullptr};
        sObject *object[4] = {nullptr};

        // top left coordinate of the quadrant
        sPoint center;

        // length of the sqare quadrant
        double length = NAN;
        double quarter_length = NAN;

    public:
        /**
         * Constructor, sets the quadrant center, length, and parent quadrant
         * @param center            an sPoint, the center of this quadrant
         * @param quadrant_length   length of this quadrant
         * @param parent            parent of the quadrant to which this is subquadrant of
         */
        sQuadrant(sPoint center, double quadrant_length, sQuadrant *parent);

        /**
         * @return   the quadrant's length
         */
        double GetLength();

        /**
         * @return   the qudrant's sPoint, the center
         */
        sPoint GetPoint();

        /**
         * @return   a pointer to the quadrant's parent
         */
        sQuadrant *GetParent();

        /**
         * Check that a qudrant does not contain any objects
         * @return
         */
        bool IsEmpty();

        /**
         * Check that a sub-quadrant does not contain an sObject
         *
         * @param quadrant
         * @return   TRUE if sub-quadrant is empty, FALSE if contains an sObject
         */
        bool IsEmpty(int quadrant);

        /**
         * Get the sObject from a quadrant
         * @param quadrant   enums NORTH_WEST, NORTH_EAST, SOUTH_WEST,or SOUTH_EAST
         * @return   a reference to the sub-quadrant's object
         */
        sObject &GetObject(int subquadrant);

        /**
         * Add an sObject to a sub-quadrant
         * @param object   object to insert
         * @param subquadrant   enums NORTH_WEST, NORTH_EAST, SOUTH_WEST,or SOUTH_EAST
         */
        void SetObject(sObject &object, int subquadrant);

        /**
         * Remove an sObject from its quadrant return its location
         *
         * @param subquadrant   enums NORTH_WEST, NORTH_EAST, SOUTH_WEST, or SOUTH_EAST
         * @return   a reference to the object
         */
        sObject &RemoveObject(int subquadrant);

        /**
         * Subdivide a sub-quadrant
         * @param subquadrant   enums NORTH_WEST, NORTH_EAST, SOUTH_WEST, or SOUTH_EAST
         * @return   a pointer to the quadrant which contains the new sub-quadrants
         */
        sQuadrant *NewSubQuadrant(int subquadrant);

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
