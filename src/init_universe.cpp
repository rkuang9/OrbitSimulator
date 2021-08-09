//
// Created by Macross on 2/16/2021.
//

#ifndef SIMULATOR_INITIALIZEOBJECTS_CPP
#define SIMULATOR_INITIALIZEOBJECTS_CPP

#include <vector>
#include "include/barnes-hut/object.h"

// https://nssdc.gsfc.nasa.gov/planetary/factsheet/
void CreateObjects(std::vector<space::object> &objects)
{
    const double AU = 1.496e11;
    const double G_constant = 6.673e-11;
    const double c = 2.9979e8;
    const double planck = 6.626e-34;
    const double light_year = 9.461e15;
    objects.emplace_back(space::object(0, 0, 1.989e30, 0, "Sun"));
    objects.emplace_back(space::object(0.390 * AU, 1, 3.300e23, 47.4e6, "Mercury"));
    objects.emplace_back(space::object(0.723 * AU, 2, 4.870e24, 35.0e6, "Venus"));
    objects.emplace_back(space::object(1.000 * AU, 3, 5.972e24, 29.8e6, "Earth"));
    objects.emplace_back(space::object(1.524 * AU, 4, 6.420e23, 24.1e6, "Mars"));
    objects.emplace_back(space::object(5.203 * AU, 5, 1.898e27, 13.1e6, "Jupiter"));
    objects.emplace_back(space::object(9.539 * AU, 6, 5.680e26, 9.70e6, "Saturn"));
    objects.emplace_back(space::object(19.18 * AU, 7, 8.680e25, 6.80e6, "Uranus"));
    objects.emplace_back(space::object(30.06 * AU, 8, 1.020e26, 5.40e6, "Neptune"));
    objects.push_back(space::object(39.53 * AU, 9, 1.460e22, 4.70e6, "Pluto"));
}

#endif //SIMULATORIN_ITIALIZEOBJECTS_CPP



