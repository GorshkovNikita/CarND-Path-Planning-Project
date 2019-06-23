//
// Created by nikita on 20.06.19.
//

#include <vector>
#include "PathPlanner.h"
#include "helpers.h"

using std::vector;

Path::Path(vector<double> x, vector<double> y) : x(std::move(x)), y(std::move(y)) {}

Path PathPlanner::generate_path(SystemState &systemState) {
    vector<double> path_x;
    vector<double> path_y;

    /**
     * TODO: define a path made up of (x,y) points that the car will visit
     *   sequentially every .02 seconds
     */
    double dist_inc = 0.25;
    for (int i = 0; i < 50; ++i) {
        path_x.push_back(systemState.car_state.x + (dist_inc * i) * cos(deg2rad(systemState.car_state.yaw)));
        path_y.push_back(systemState.car_state.y + (dist_inc * i) * sin(deg2rad(systemState.car_state.yaw)));
    }

    return Path(path_x, path_y);
}
