//
// Created by nikita on 20.06.19.
//

#ifndef PATH_PLANNING_PATHPLANNER_H
#define PATH_PLANNING_PATHPLANNER_H

#include "HighwayMap.h"
#include "SystemState.h"

struct Path {
    Path(vector<double> x, vector<double> y);

    vector<double> x;
    vector<double> y;
};

class PathPlanner {
public:
    Path generate_path(SystemState& systemState);
private:
    HighwayMap highway_map;
    double max_s = 6945.554;
};

#endif //PATH_PLANNING_PATHPLANNER_H
