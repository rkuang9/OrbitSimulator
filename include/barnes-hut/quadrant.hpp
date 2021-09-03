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

namespace space {
    class sQuadrant {

    public:
        std::string test = "";
        // a pointer to the parent quadrant of which this is a subquadrant of
        sQuadrant *parent = nullptr;

        // each element representing the 4 possible quadrants objects contained within
        sQuadrant *quadrant[4] = {nullptr};

        //sObject *object[4] = {nullptr};
        sObject *object = nullptr;

        // center coordinate of the quadrant
        sPoint center;

        // length of the sqare quadrant
        double length = NAN;
        double quarter_length = NAN;

        bool is_internal = false;

    public:
        /**
         * Constructor, sets the quadrant center, length, and parent quadrant
         * @param center            an sPoint, the center of this quadrant
         * @param quadrant_length   length of this quadrant
         * @param parent            parent of the quadrant to which this is subquadrant of
         */
        sQuadrant(sPoint center, double quadrant_length, sQuadrant *parent);

        // need to make sure this never runs
        sQuadrant(const sQuadrant &copy) = default;

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
        sQuadrant GetParent();

        /**
         * Check that a qudrant does not contain any objects
         * @return   TRUE if quadrant is empty, FALSE if quadrant contains an object
         */
        bool IsEmpty();

        /**
         * Check that a quadrant contains sub-quadrants, is an internal node (quadrant)
         * @return
         */
        bool IsInternal();

        /**
         * Check that a quadrant does not have sub-quadrants, is an external node (quadrant)
         * @return
         */
        bool IsExternal();

        /**
         * @param subquadrant    the sub-quadrant enum value
         * @return   a pointer to the sub-quadrant
         */
        sQuadrant *GetQuadrant(int subquadrant);

        /**
         * Get the quadrant's object
         * @return   a pointer to the quadrant's object
         */
        sObject *GetObject();

        /**
         * Add a heap allocated sObject to a sub-quadrant
         * @param object   object to insert
         */
        void SetObject(sObject &object);

        /**
         * Remove an sObject from its quadrant return its location
         * @param subquadrant   enums NORTH_WEST, NORTH_EAST, SOUTH_WEST, or SOUTH_EAST
         * @return   a reference to the object
         */
        sObject& RemoveObject();

        /**
         * Subdivide a sub-quadrant
         * @return   a pointer to the quadrant which contains the new sub-quadrants
         */
        sQuadrant *NewSubQuadrant(int subquadrant);

    };
}

#endif //ORBITSIMULATOR_QUADRANT_HPP