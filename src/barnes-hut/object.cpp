//
// Created by Macross on 2/14/2021.
//

#include "include/barnes-hut/object.hpp"
#include <cmath>


namespace space
{

    sObject::sObject(sPoint _point, double mass, double velocity, std::string name)
    {
        this->point = _point;
        this->mass = mass;
        this->velocity = velocity;
        this->name = std::move(name);
        this->velocity = velocity;
    }


    sObject *sObject::CreateCOM(sObject &object)
    {
        this->point = sPoint(object.GetPoint().GetX(), object.GetPoint().GetY());
        this->mass = object.mass;
        this->is_com = true;
        return this;
    }


    void sObject::UpdateCOM(sObject &object)
    {
        if (this->is_com) {
            this->mass += object.mass;
            this->point.SetX((this->GetX() * this->mass + object.GetX() * object.GetMass()) / this->mass);
            this->point.SetY((this->GetY() * this->mass + object.GetY() * object.GetMass()) / this->mass);
        }
        else {
            std::cout << "tried to update an object that is not com and failed\n";
        }
    }


    double sObject::GetForce(const sObject &other_object)
    {
        return space::constants::G * this->mass * other_object.mass /
               pow(this->point.DistanceTo(other_object.point), 2);
    }


    void sObject::UpdateForce(const sObject &other_object)
    {
        this->net_force += space::constants::G * this->mass * other_object.mass /
                           pow(this->point.DistanceTo(other_object.point), 2);
    }


    bool sObject::IsCOM()
    {
        return this->is_com;
    }


    double sObject::GetMass() const
    {
        return this->mass;
    }


    std::string sObject::GetName() const
    {
        return this->name;
    }


    /** Getters and Setters */
    double sObject::GetX()
    {
        return this->point.GetX();
    }


    double sObject::GetY()
    {
        return this->point.GetY();
    }


    double sObject::GetNetForce()
    {
        return this->net_force;
    }


    void sObject::SetX(double x)
    {
        this->point.SetX(x);
    }


    void sObject::SetY(double y)
    {
        this->point.SetY(y);
    }


    void sObject::SetXY(double x, double y)
    {
        this->point.SetX(x);
        this->point.SetY(y);
    }


    sPoint &sObject::GetPoint()
    {
        // this is a reference return type so be careful when setting
        // another object's point
        return this->point;
    }


    void sObject::SetPoint(sPoint &_point)
    {
        this->point = _point;
    }


    void sObject::SetIsCOM(bool is_parent)
    {
        this->is_com = is_parent;
    }
}















/*
 * Roche Limit is the distance at which one celestial body will be ripped apart due to tidal forces exerted
 * by another more massive body
 *
 * @param other_object     the other object in which to calculate the Roche Limit with
 * @return double,         Roche Limit distance in meters
 */
/*
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
}*/