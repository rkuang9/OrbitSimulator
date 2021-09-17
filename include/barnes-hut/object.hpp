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
        double net_force = 0.00;
        double net_force_x = 0.00;
        double net_force_y = 0.00;


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
        double GetForce(const sObject &other_object);

        void UpdateForce(const sObject &other_object);

        /** Getters and Setters */
        double GetMass() const;

        std::string GetName() const;

        double GetX();

        double GetY();

        double GetNetForce();

        void SetX(double x);

        void SetY(double y);

        void SetXY(double x, double y);

        sPoint &GetPoint();

        void SetPoint(sPoint &point);

        bool IsCOM();

        void SetIsCOM(bool is_parent);
    };
}
#endif //SIMULATOR_OBJECT_H
