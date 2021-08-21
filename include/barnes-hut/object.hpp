//
// Created by Macross on 2/14/2021.
//

#ifndef SIMULATOR_OBJECT_H
#define SIMULATOR_OBJECT_H

#include <iostream>
#include <cmath>

#include "include/barnes-hut/point.hpp"

namespace space {
    struct ObjectProperties {
        double x, y;
        double velocity, velocity_x, velocity_y;
        double accel, accel_x, accel_y;
        double momentum, momentum_x, momentum_y;
        double force, force_x, force_y;
    };

    class sObject {
    public:
        sPoint point;
        ObjectProperties properties;
        double x = NAN, y = NAN;
        double mass = NAN;        // kg
        double velocity = NAN;
        std::string name;
        bool is_com = false;   // identifies object as center of mass object or a real object

        double radius = NAN;
        double volume = NAN;
        double density = NAN;

        double G_constant = 6.673e-11;

        double momentum = NAN;
        double acceleration = NAN;
        double force_x = NAN;
        double force_y = NAN;

        // constructors, destructor
        sObject();

        // center of mass object
        sObject(const sObject& object);

        // initialize object constructor
        sObject(double x, double y, double mass, double velocity, std::string name);

        // create empty COM object
        void COM(const sObject& object);

        bool operator == (const sObject& object) const;


        // destructor
        ~sObject();

        // formulas
        double GetForce(const sObject &other_object) const;
        double GetDistance(const sObject &other_object) const;
        double RocheLimit(const sObject &other_object) const;

        void UpdateCOM(sObject& object);


        

        


        void SetRadius(double radius);

        // accessors
        double GetX() const;
        double GetY() const;
        double GetMass() const;
        std::string GetName() const;
        bool IsCOM() const;
        void display() const;
    };
}
#endif //SIMULATOR_OBJECT_H
