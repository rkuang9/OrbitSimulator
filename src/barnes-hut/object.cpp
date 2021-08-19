//
// Created by Macross on 2/14/2021.
//

#include "include/barnes-hut/object.hpp"
#include <cmath>


namespace space {
    sObject::sObject() = default;

    /*Object::Object(const Object &copy_object) {

    }*/


    sObject::sObject(double x, double y, double mass, double velocity, std::string name) {
        this->x = x;
        this->y = y;
        this->mass = mass;
        this->velocity = velocity;
        this->name = std::move(name);
        this->properties.x = x;
        this->properties.y = y;
        this->properties.velocity = velocity;
    }


    // center of mass (copy) constructor
    sObject::sObject(const sObject &object) {
        std::cout << "copy ran\n";
        this->x = object.x;
        this->y = object.y;
        this->mass = object.mass;
        this->is_com = true;
    }


    void sObject::COM(const sObject &object) {
        this->x = object.x;
        this->y = object.y;
        this->mass = object.mass;
        this->is_com = true;
        this->name = "COM mass " + std::to_string(this->mass);
    }


    double sObject::GetForce(const sObject &other_object) const {
        this->velocity;//Force = G * m1 * m2/ r^2
        return 0;
    }


    double sObject::GetDistance(const sObject &other_object) const {
        return sqrt((this->y - other_object.GetY()) * (this->y - other_object.GetY()) +
                    (this->x - other_object.GetX()) * (this->x - other_object.GetX()));
    }


    // set radius, also set volume assuming all objects are approximately a sphere
    void sObject::SetRadius(double _radius) {
        this->radius = _radius;
        this->volume = 4 * M_PI * this->radius * this->radius * this->radius / 3;

        this->density = this->mass / this->volume;
    }


    /**
     * Roche Limit is the distance at which one celestial body will be ripped apart due to tidal forces exerted
     * by another more massive body
     *
     * @param other_object     the other object in which to calculate the Roche Limit with
     * @return double,         Roche Limit distance in meters
     */
    double sObject::RocheLimit(const sObject &other_object) const {
        double larger_mass_radius;
        double larger_mass_density;
        double smaller_mass_density;

        if (this->mass > other_object.mass) {
            larger_mass_radius = this->radius;
            larger_mass_density = this->density;
            smaller_mass_density = other_object.density;
        } else {
            larger_mass_radius = other_object.radius;
            larger_mass_density = other_object.density;
            smaller_mass_density = this->density;
        }

        return larger_mass_radius * pow(2 * larger_mass_density / smaller_mass_density, 1 / 3);
    }


    void sObject::UpdateCOM(sObject &object) {
        if (!this->is_com) {
            return;
        }

        double total_mass = this->mass + object.mass;
        this->x = (this->x * this->mass + object.GetX() * object.GetMass()) / total_mass;
        this->y = (this->y * this->mass + object.GetY() * object.GetMass()) / total_mass;
        this->mass = total_mass;
        this->name = "COM mass " + std::to_string(this->mass);
    }


    // destructor
    sObject::~sObject() = default;


    double sObject::GetX() const {
        return this->x;
    }

    double sObject::GetY() const {
        return this->y;
    }

    double sObject::GetMass() const {
        return this->mass;
    }

    bool sObject::IsCOM() const {
        return this->is_com;
    }

    // display object's physical properties
    void sObject::display() const {
        std::cout << "\nPosition: (" << this->x << ", " << this->y << ")\n";
        std::cout << "Radius: " << this->radius << "\n";
        std::cout << "Velocity: " << this->velocity << "\n";
        std::cout << "Acceleration: " << this->acceleration << "\n";
    }

    std::string sObject::GetName() const {
        return this->name;
    }


    /**
     * Overloaded equality operator to check if two objects are identical
     * @param object
     * @return boolean,   TRUE if the object is identical in physical properties, else FALSE
     */
    bool sObject::operator==(const sObject &object) const {
        return object.name == this->name &&
               object.mass == this->mass &&
               object.radius == this->radius &&
               object.volume == this->volume &&
               object.density == this->density;
    }
}

