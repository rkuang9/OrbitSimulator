//
// Created by Macross on 2/14/2021.
//

#ifndef SIMULATOR_OBJECT_H
#define SIMULATOR_OBJECT_H

#include <iostream>
#include <cmath>

#include "include/barnes-hut/point.hpp"

namespace space
{
    class sObject
    {
    public:
        sPoint point;
        std::string name;

        double mass = NAN;
        double velocity = NAN;
        double accel = NAN;
        double momentum = NAN;
        double force = NAN;

        bool is_com = false;

    public:
        // constructors, destructor
        sObject() = default;

        // copy constructor, should never run
        sObject(const sObject &object) = default;

        // destructor
        ~sObject() = default;

        // initialize object constructor
        sObject(sPoint point, double mass, double velocity, std::string name);

        // create empty COM object
        sObject* CreateCOM(sObject &object);

        // update a COM object
        void UpdateCOM(sObject &object);

        // formulas
        double GetForce(const sObject &other_object) const;

        bool IsCOM();

        /** Getters and Setters */
        double GetMass() const;

        std::string GetName() const;

        double GetX();

        double GetY();

        void SetX(double x);

        void SetY(double y);

        void SetXY(double x, double y);

        sPoint &GetPoint();

        void SetPoint(sPoint &point);

        void SetIsCOM(bool is_parent);
    };
}
#endif //SIMULATOR_OBJECT_H
