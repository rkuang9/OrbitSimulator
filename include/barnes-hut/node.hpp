//
// Created by Macross on 8/17/2021.
//

#ifndef ORBITSIMULATOR_NODE_HPP
#define ORBITSIMULATOR_NODE_HPP

#include "include/barnes-hut/object.hpp"

namespace space {
    class Node
    {
        bool is_com = false;

        space::sObject *object = nullptr;
        Node *northeast = nullptr;
        Node *northwest = nullptr;
        Node *southwest = nullptr;
        Node *southeast = nullptr;

        Node(space::sObject &_object);

        bool IsEmpty();

        bool IsCOM();

        bool IsExternal();

        // convert object to center of mass, returns a copy of former object
        space::sObject ConvertToCom();


    };
}


#endif //ORBITSIMULATOR_NODE_HPP
