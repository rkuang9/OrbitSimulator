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
    class Quadtree
    {
    private:
        int size = 0;
        int height = 0;

        sQuadrant *root = nullptr;
        sQuadrant *current = nullptr;


    public:
        Quadtree();
        void Insert(sObject &object);
    };
}


#endif //SIMULATOR_QUADTREE_H
