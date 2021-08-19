//
// Created by Macross on 8/17/2021.
//

#include "include/barnes-hut/quadrant.hpp"
#include "include/barnes-hut/object.hpp"

namespace space {
    sQuadrant::sQuadrant(sPoint top_left_point, double quadrant_length, sQuadrant *parent) {
        this->top_left = top_left_point;
        this->length = quadrant_length;
        this->parent = parent;
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


    sQuadrant* sQuadrant::NewSubQuadrantNW() {
        this->northwest = new sQuadrant(
                this->top_left,
                this->length / 2,
                this);
        return this->northwest;
    }


    sQuadrant* sQuadrant::NewSubQuadrantNE() {
        this->northeast = new sQuadrant(sPoint(
                this->top_left.GetX() + this->length / 2,
                this->top_left.GetY()),
                this->length / 2,
                this);
        return this->northeast;
    }


    sQuadrant* sQuadrant::NewSubQuadrantSW() {
        this->southwest = new sQuadrant(sPoint(
                this->top_left.GetX(),
                this->top_left.GetY() + this->length / 2),
                this->length / 2,
                this);
        return this->southwest;
    }


    sQuadrant* sQuadrant::NewSubQuadrantSE() {
        this->southeast = new sQuadrant(sPoint(
                this->top_left.GetX() + this->length / 2,
                this->top_left.GetY() + this->length / 2),
                this->length / 2,
                this);
        return this->southeast;
    }


    double sQuadrant::GetWidth() {
        return this->length;
    }


    double sQuadrant::GetHeight() {
        return this->length;
    }
}