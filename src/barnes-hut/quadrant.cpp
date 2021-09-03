//
// Created by Macross on 8/17/2021.
//

#include "include/barnes-hut/quadrant.hpp"

namespace space
{
    sQuadrant::sQuadrant(sPoint _center, double quadrant_length, sQuadrant *parent)
    {
        this->center = _center;
        this->length = quadrant_length;
        this->quarter_length = quadrant_length / 4;
        this->parent = parent;
    }


    double sQuadrant::GetLength()
    {
        return this->length;
    }


    sPoint sQuadrant::GetPoint()
    {
        return this->center;
    }


    sQuadrant sQuadrant::GetParent()
    {
        return *this->parent;
    }


    bool sQuadrant::IsEmpty()
    {
        return this->object == nullptr;
    }


    bool sQuadrant::IsInternal()
    {
        return this->quadrant[NORTH_WEST] != nullptr ||
               this->quadrant[NORTH_EAST] != nullptr ||
               this->quadrant[SOUTH_WEST] != nullptr ||
               this->quadrant[SOUTH_EAST] != nullptr;
    }


    bool sQuadrant::IsExternal()
    {
        return this->quadrant[NORTH_WEST] == nullptr &&
               this->quadrant[NORTH_EAST] == nullptr &&
               this->quadrant[SOUTH_WEST] == nullptr &&
               this->quadrant[SOUTH_EAST] == nullptr;
    }


    sQuadrant *sQuadrant::GetQuadrant(int subquadrant)
    {
        return this->quadrant[subquadrant];
    }


    sObject *sQuadrant::GetObject()
    {
        // need to check that _quadrant is between 0 and 3?
        return this->object;
    }


    void sQuadrant::SetObject(sObject &_object)
    {
        this->object = &_object;
    }


    sObject &sQuadrant::RemoveObject()
    {
        sObject *temp = this->object;
        this->object = nullptr;
        return *temp;
    }


    sQuadrant *sQuadrant::NewSubQuadrant(int subquadrant)
    {
        if (this->object == nullptr) {
            std::cout << "The current quadrant does not contain an object, a subquadrant was not created\n";
        }

        if (this->quadrant[subquadrant] != nullptr) {
            std::cout << Quadrant(subquadrant) << " subquadrant already exists\n";
        }

        if (subquadrant == NORTH_WEST) {
            this->quadrant[subquadrant] = new sQuadrant(
                    sPoint(this->center.GetX() - this->quarter_length, this->center.GetY() + quarter_length),
                    this->length / 2,
                    this);
        }
        else if (subquadrant == NORTH_EAST) {
            this->quadrant[subquadrant] = new sQuadrant(
                    sPoint(this->center.GetX() + this->quarter_length, this->center.GetY() + quarter_length),
                    this->length / 2,
                    this);
        }
        else if (subquadrant == SOUTH_WEST) {
            this->quadrant[subquadrant] = new sQuadrant(
                    sPoint(this->center.GetX() - this->quarter_length, this->center.GetY() - quarter_length),
                    this->length / 2,
                    this);
        }
        else { // SOUTH_EAST
            this->quadrant[subquadrant] = new sQuadrant(
                    sPoint(this->center.GetX() + this->quarter_length, this->center.GetY() - quarter_length),
                    this->length / 2,
                    this);
        }

        return this->quadrant[subquadrant];
    }
}