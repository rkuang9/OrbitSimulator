//
// Created by Macross on 8/17/2021.
//

#include "include/barnes-hut/node.hpp"

namespace space
{
    Node::Node(space::sObject &_object)
    {
        this->object = &_object;
    }

    bool Node::IsEmpty()
    {
        return this->object == nullptr;
    }

    bool Node::IsCOM()
    {
        return this->is_com;
    }

    bool Node::IsExternal()
    {
        return this->northeast == nullptr && this->northwest == nullptr &&
               this->southwest == nullptr && this->southeast == nullptr;
    }
}