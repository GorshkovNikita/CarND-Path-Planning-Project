//
// Created by nikita on 20.06.19.
//

#ifndef PATH_PLANNING_SYSTEMSTATE_H
#define PATH_PLANNING_SYSTEMSTATE_H

#include <vector>

using std::vector;

struct CarState {
    CarState(double carX, double carY, double carS, double carD, double carYaw, double carSpeed) :
            x(carX), y(carY), s(carS), d(carD), yaw(carYaw), speed(carSpeed) {}

    double x;
    double y;
    double s;
    double d;
    double yaw;
    double speed;
};

struct VehicleState {
    VehicleState(int id, double x, double y, double vx, double vy, double s, double d) :
        id(id), x(x), y(y), vx(vx), vy(vy), s(s), d(d) {}

    int id;
    double x;
    double y;
    double vx;
    double vy;
    double s;
    double d;
};

struct SystemState {
    SystemState(const CarState &carState, vector<VehicleState> vehiclesStates,
                vector<double> previousPathX, vector<double> previousPathY, double endPathS, double endPathD) :
                car_state(carState), vehicles_states(std::move(vehiclesStates)), previous_path_x(std::move(previousPathX)),
                previous_path_y(std::move(previousPathY)), end_path_s(endPathS), end_path_d(endPathD) {}

    CarState car_state;
    vector<VehicleState> vehicles_states;
    vector<double> previous_path_x;
    vector<double> previous_path_y;
    double end_path_s;
    double end_path_d;
};

#endif //PATH_PLANNING_SYSTEMSTATE_H
