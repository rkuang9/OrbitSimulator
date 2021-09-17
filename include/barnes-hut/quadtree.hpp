//
// Created by Macross on 4/10/2021.
//

#ifndef SIMULATOR_QUADTREE_H
#define SIMULATOR_QUADTREE_H

#include "include/barnes-hut/point.hpp"
#include "include/list.hpp"
#include "include/barnes-hut/quadrant.hpp"
#include "include/barnes-hut/object.hpp"


namespace space
{
    class sQuadtree
    {
    private:
        sQuadrant *root = nullptr;
        sQuadrant *current = nullptr;

        int size = 0;
        int height = 0;
        double width = 0;

        void PointCurrentTo(sQuadrant *point_to);

        void InsertInternal(sObject *new_object, int quadrant);

        void InsertExternal(sObject *new_object, int quadrant);

        void ClearQuadrant(int quadrant);

    public:
        explicit sQuadtree(double width);

        sQuadtree(double width, space::list<sObject *> &universe);

        sQuadrant *GetRoot();

        sQuadrant *GetCurrent();

        void Insert(sObject *new_object);
    };
}


#endif //SIMULATOR_QUADTREE_H
