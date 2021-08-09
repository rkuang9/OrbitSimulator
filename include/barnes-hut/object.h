//
// Created by Macross on 2/14/2021.
//

#ifndef SIMULATOR_OBJECT_H
#define SIMULATOR_OBJECT_H

#include <iostream>
#include <cmath>


namespace space {
    struct ObjectProperties {
        double x, y;
        double velocity, velocity_x, velocity_y;
        double accel, accel_x, accel_y;
        double momentum, momentum_x, momentum_y;
        double force, force_x, force_y;
    };

    class object {
    public:
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
        object();

        // center of mass object
        object(const object& object);

        // initialize object constructor
        object(double x, double y, double mass, double velocity, std::string name);

        // create empty COM object
        void COM(const object& object);

        bool operator == (const object& object) const;


        // destructor
        ~object();

        // formulas
        double GetForce(const object &other_object) const;
        double GetDistance(const object &other_object) const;
        double RocheLimit(const object &other_object) const;

        void UpdateCOM(object& object);


        

        


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
