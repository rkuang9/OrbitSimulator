//
// Created by Macross on 8/17/2021.
//

#include "include/barnes-hut/quadrant.hpp"

namespace space
{
    sQuadrant::sQuadrant(sPoint center, double quadrant_length, sQuadrant *parent)
    {
        this->center = center;
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


    sQuadrant *sQuadrant::GetParent()
    {
        return this->parent;
    }


    bool sQuadrant::IsEmpty()
    {
        for (auto &i : this->object) {
            if (i != nullptr) {
                return false;
            }
        }

        return true;
    }


    bool sQuadrant::IsEmpty(int subquadrant)
    {
        return this->object[subquadrant] == nullptr;
    }


    sObject &sQuadrant::GetObject(int subquadrant)
    {
        // need to check that _quadrant is between 0 and 4?
        return *this->object[subquadrant];
    }


    void sQuadrant::SetObject(sObject &_object, int subquadrant)
    {
        this->object[subquadrant] = &_object;
    }


    sObject &sQuadrant::RemoveObject(int subquadrant)
    {
        sObject &temp = *this->object[subquadrant];
        this->object[subquadrant] = nullptr;
        return temp;
    }


    sQuadrant *sQuadrant::NewSubQuadrant(int subquadrant)
    {
        sPoint point{};

        if (subquadrant == NORTH_WEST) {
            point.SetXY(this->center.x - this->quarter_length, this->center.y + quarter_length);
        }
        else if (subquadrant == NORTH_EAST) {
            point.SetXY(this->center.x + this->quarter_length, this->center.y + quarter_length);
        }
        else if (subquadrant == SOUTH_WEST) {
            point.SetXY(this->center.x - this->quarter_length, this->center.y - quarter_length);
        }
        else { // SOUTH_EAST
            point.SetXY(this->center.x + this->quarter_length, this->center.y - quarter_length);
        }

        this->quadrant[subquadrant] = new sQuadrant(point, this->length / 2, this);
        return this->quadrant[subquadrant];
    }
}




/*



    bool sQuadrant::IsEmptyNW()
    {
        return this->northwest_object == nullptr;
    }


    bool sQuadrant::IsEmptyNE()
    {
        return this->northeast == nullptr;
    }


    bool sQuadrant::IsEmptySW()
    {
        return this->southwest == nullptr;
    }


    bool sQuadrant::IsEmptySE()
    {
        return this->southeast == nullptr;
    }


    sQuadrant *sQuadrant::NewSubQuadrantNW()
    {
        this->northwest = new sQuadrant(
                sPoint(this->center.x - this->quarter_length, this->center.y + quarter_length),
                this->length / 2,
                this);
        return this->northwest;
    }


    sQuadrant *sQuadrant::NewSubQuadrantNE()
    {
        this->northeast = new sQuadrant(
                sPoint(this->center.x + this->quarter_length, this->center.y + quarter_length),
                this->length / 2,
                this);
        return this->northeast;
    }


    sQuadrant *sQuadrant::NewSubQuadrantSW()
    {
        this->southwest = new sQuadrant(
                sPoint(this->center.x - this->quarter_length, this->center.y - quarter_length),
                this->length / 2,
                this);
        return this->southwest;
    }


    sQuadrant *sQuadrant::NewSubQuadrantSE()
    {
        this->southeast = new sQuadrant(
                sPoint(this->center.x + this->quarter_length, this->center.y - quarter_length),
                this->length / 2,
                this);
        return this->southeast;
    }





    void sQuadrant::SetObjectNW(sObject &object)
    {
        this->northwest_object = &object;
    }


    void sQuadrant::SetObjectNE(sObject &object)
    {
        this->northeast_object = &object;
    }


    void sQuadrant::SetObjectSW(sObject &object)
    {
        this->southwest_object = &object;
    }


    void sQuadrant::SetObjectSE(sObject &object)
    {
        this->southeast_object = &object;
    }




    sObject *sQuadrant::GetObjectNW()
    {
        return this->northwest_object;
    }


    sObject *sQuadrant::GetObjectNE()
    {
        return this->northeast_object;
    }


    sObject *sQuadrant::GetObjectSW()
    {
        return this->southwest_object;
    }


    sObject *sQuadrant::GetObjectSE()
    {
        return this->southeast_object;
    }






    sObject *sQuadrant::RemoveObjectNW()
    {
        sObject *temp = this->northwest_object;
        this->northwest_object = nullptr;
        return temp;
    }


    sObject *sQuadrant::RemoveObjectNE()
    {
        sObject *temp = this->northeast_object;
        this->northeast_object = nullptr;
        return temp;
    }


    sObject *sQuadrant::RemoveObjectSW()
    {
        sObject *temp = this->southwest_object;
        this->southwest_object = nullptr;
        return temp;
    }


    sObject *sQuadrant::RemoveObjectSE()
    {
        sObject *temp = this->southeast_object;
        this->southeast_object = nullptr;
        return temp;
    }
 */