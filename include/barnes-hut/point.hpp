//
// Created by Macross on 8/18/2021.
//

#ifndef ORBITSIMULATOR_POINT_HPP
#define ORBITSIMULATOR_POINT_HPP

namespace space {
    struct sPoint {
        double x, y;

        sPoint() = default;

        sPoint(double x, double y);

        double GetX();

        double GetY();

        void SetX(double x);

        void SetY(double y);

        void SetXY(double x, double y);
    };
}


#endif //ORBITSIMULATOR_POINT_HPP
