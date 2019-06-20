//
// Created by nikita on 20.06.19.
//

#ifndef PATH_PLANNING_HIGHWAYMAP_H
#define PATH_PLANNING_HIGHWAYMAP_H

#include <vector>

using std::vector;

class HighwayMap {
public:
    HighwayMap();

    vector<double> waypoints_x;
    vector<double> waypoints_y;
    vector<double> waypoints_s;
    vector<double> waypoints_dx;
    vector<double> waypoints_dy;
};


#endif //PATH_PLANNING_HIGHWAYMAP_H
