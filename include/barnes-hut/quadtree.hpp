//
// Created by Macross on 4/10/2021.
//

#ifndef SIMULATOR_QUADTREE_H
#define SIMULATOR_QUADTREE_H

#include "include/barnes-hut/object.hpp"
#include "include/list.hpp"

namespace space
{


    /**
     * http://arborjs.org/docs/barnes-hut
     */
    class Quadtree
    {
    private:
        int size = 0;
        int height = 0;


    public:
        Quadtree(space::list<space::sObject> &universe);

        bool IsEmpty();

    };
}


#endif //SIMULATOR_QUADTREE_H
