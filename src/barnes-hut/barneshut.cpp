//
// Created by Macross on 9/3/2021.
//

#include "include/barnes-hut/barneshut.hpp"

namespace space
{
    BarnesHut::BarnesHut(list<sObject *> &universe, double width, double theta, double time_step)
    {
        if (theta >= 1 || theta <= 0) {
            throw std::invalid_argument("theta must be between 0 and 1 exclusive");
        }
        else {
            this->theta = theta;
        }

        if (time_step <= 0) {
            throw std::invalid_argument("time step must be greater than 0");
        }
        else {
            this->time_step = time_step;
        }

        this->universe = universe;

        this->quadtree = new sQuadtree(width, universe);
    }


    double BarnesHut::WidthDistanceRatio(sObject &object, const sQuadrant &quadrant)
    {
        return quadrant.length / (quadrant.GetObject()->GetPoint().DistanceTo(object.GetPoint()));
    }


    sQuadtree BarnesHut::GetQuadTree()
    {
        if (this->quadtree == nullptr) {
            throw std::invalid_argument("missing quadtree");
        }

        return *this->quadtree;
    }


    void BarnesHut::UpdateForcesInOrder(sObject &object, sQuadrant *subquadrant)
    {
        // stop traversing deeper into a sub-quadrant or when the object is compared to itself

        if (subquadrant == nullptr || &object == subquadrant->GetObject()) {
            return;
        }



        double ratio = this->WidthDistanceRatio(object, *subquadrant);

        // if the quadrant is far enough to be considered a point or it's a leaf
        if ( (ratio < this->theta && subquadrant->GetObject()->IsCOM()) || subquadrant->IsExternal() ) {
            std::cout << object.GetName() << "-" << subquadrant->GetObject()->GetName() << " ("
                      << subquadrant->GetObject()->GetMass() << ") "
                      << "sd ratio: " << ratio << " < " << this->theta << ", distance: " <<
                      object.GetPoint().DistanceTo(subquadrant->GetObject()->GetPoint()) << ", stopping" << std::endl;
            object.UpdateForce(*subquadrant->GetObject());
            return;
        }
        else if (subquadrant->IsExternal()) {
            std::cout << object.GetName() << " (External) -" << subquadrant->GetObject()->GetName() << " ("
            << subquadrant->GetObject()->GetMass() << ") "
            << "sd ratio: " << ratio << " < " << this->theta << ", stopping" << std::endl;
            std::cout << "this is a leaf node whose sd ratio is greater than " << this->theta << "\n";
            object.UpdateForce(*subquadrant->GetObject());
            return;
        }
        else {
            std::cout << "sd ratio between " << object.GetName() << " and " << subquadrant->GetObject()->GetName() <<
                      " is " << ratio << ", greater than " << this->theta << std::endl;
        }

        this->UpdateForcesInOrder(object, subquadrant->GetQuadrant(NORTH_WEST));

        this->UpdateForcesInOrder(object, subquadrant->GetQuadrant(NORTH_EAST));

        this->UpdateForcesInOrder(object, subquadrant->GetQuadrant(SOUTH_WEST));

        this->UpdateForcesInOrder(object, subquadrant->GetQuadrant(SOUTH_EAST));
    }
}

