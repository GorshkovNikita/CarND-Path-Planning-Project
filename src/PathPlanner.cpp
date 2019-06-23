//
// Created by nikita on 20.06.19.
//

#include <vector>
#include <iostream>
#include "PathPlanner.h"
#include "helpers.h"

using std::vector;

Path::Path(vector<double> x, vector<double> y) : x(std::move(x)), y(std::move(y)) {}

Path PathPlanner::generate_path(SystemState &systemState) {
    vector<double> path_x;
    vector<double> path_y;

    double pos_x;
    double pos_y;
    double angle;
    int path_size = systemState.previous_path_x.size();
    std::cout << "path size " << path_size << std::endl;
//    vector<double> xy = getXY(
//            systemState.end_path_s, systemState.end_path_d, highway_map.waypoints_s,
//            highway_map.waypoints_x, highway_map.waypoints_y
//    );
//    std::cout << systemState.end_path_d << std::endl;
//    std::cout << xy[0] << ' ' << xy[1] << std::endl;
//    std::cout << systemState.car_state.x << ' ' << systemState.car_state.y << std::endl;
//    std::cout << "==============" << std::endl;

    vector<double> frenet_pos;
//    std::cout << systemState.end_path_s << ' ' << systemState.end_path_d << std::endl << std::endl;

    for (int i = 0; i < path_size; ++i) {
        path_x.push_back(systemState.previous_path_x[i]);
        path_y.push_back(systemState.previous_path_y[i]);
    }

    if (path_size == 0) {
        frenet_pos = getFrenet(systemState.car_state.x, systemState.car_state.y, systemState.car_state.yaw, highway_map.waypoints_x, highway_map.waypoints_y);
        pos_x = systemState.car_state.x;
        pos_y = systemState.car_state.y;
        angle = deg2rad(systemState.car_state.yaw);
    } else {
        frenet_pos = {systemState.end_path_s, systemState.end_path_d};
        pos_x = systemState.previous_path_x[path_size-1];
        pos_y = systemState.previous_path_y[path_size-1];

        double pos_x2 = systemState.previous_path_x[path_size-2];
        double pos_y2 = systemState.previous_path_y[path_size-2];
        angle = atan2(pos_y-pos_y2, pos_x-pos_x2);
    }

    double dist_inc = 0.50; // speed
    for (int i = 0; i < 50 - path_size; ++i) {
        vector<double> xy = getXY(
                frenet_pos[0] + dist_inc * i, frenet_pos[1], highway_map.waypoints_s,
                highway_map.waypoints_x, highway_map.waypoints_y
        );
//        path_x.push_back(pos_x + (dist_inc * i) * cos(angle));
//        path_y.push_back(pos_y + (dist_inc * i) * sin(angle));
        std::cout << xy[0] << ' ' << xy[1] << std::endl;
        std::cout << pos_x << ' ' << pos_y << std::endl;
        std::cout << "=============" << std::endl;
        path_x.push_back(xy[0]);
        path_y.push_back(xy[1]);
    }

    return Path(path_x, path_y);
}
