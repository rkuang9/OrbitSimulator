//
// Created by Macross on 4/10/2021.
//

#include "include/barnes-hut/quadtree.hpp"


namespace space
{
    Quadtree::Quadtree()
    {
        this->root = new sQuadrant(sPoint(0, 0), 1921.56 * AU, nullptr);
        this->current = this->root;
    }


    void Quadtree::Insert(sObject &object)
    {
        // find the correct subquadrant by comparing quadrant center to object's point
        int insert_quadrant = this->current->GetPoint().Compare(object.point);

        // insert object into the correct subquadrant if it doesn't already contain one
        if (this->current->IsEmpty(insert_quadrant)) {
            this->current->SetObject(object, insert_quadrant);
        }
        // if an object already exists in the subquadrant, recursively divide and insert to it
        else {
            this->current = this->current->NewSubQuadrant(insert_quadrant);
            this->Insert(this->current->GetParent()->RemoveObject(insert_quadrant));
            this->Insert(object);
        }
    }
}

