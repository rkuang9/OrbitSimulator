//
// Created by Macross on 9/3/2021.
//

#ifndef ORBITSIMULATOR_BARNESHUT_HPP
#define ORBITSIMULATOR_BARNESHUT_HPP

#include "include/barnes-hut/object.hpp"
#include "include/barnes-hut/quadrant.hpp"
#include "include/barnes-hut/quadtree.hpp"
#include "include/list.hpp"

namespace space
{
    class BarnesHut
    {
    private:
        double theta = 0.5;   // default 0.5, widely used
        double time_step = 0.3; // simulation loop time interval
        list<sObject*> universe; // containing list of bodies
        sQuadtree *quadtree = nullptr;


    public:
        BarnesHut(list<sObject*> &universe, double width, double theta, double time_step);

        static double WidthDistanceRatio(sObject &object, const sQuadrant &quadrant);

        sQuadtree GetQuadTree();

        /**
         * Traverse tree in-order, if the quadrant's sd-ratio is less theta
         * update the current object's force using the quadrant's object
         * and skip all sub-quadrants
         * @param object
         * @param subquadrant
         */
        void UpdateForcesInOrder(sObject &object, sQuadrant *subquadrant);
    };
}


#endif //ORBITSIMULATOR_BARNESHUT_HPP
