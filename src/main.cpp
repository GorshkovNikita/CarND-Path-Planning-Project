#include <uWS/uWS.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"
#include "json.hpp"
#include "helpers.h"
#include "PathPlanner.h"

using nlohmann::json;
using std::string;
using std::vector;

int main() {
    uWS::Hub h;
    PathPlanner pathPlanner;

    h.onMessage([&pathPlanner] (uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
        if (length > 2 && data[0] == '4' && data[1] == '2') {

            auto s = hasData(data);

            if (!s.empty()) {
                auto j = json::parse(s);

                auto event = j[0].get<string>();

                if (event == "telemetry") {
                    // j[1] is the data JSON object

                    // Main car's localization Data
                    CarState car_state(j[1]["x"], j[1]["y"], j[1]["s"], j[1]["d"], j[1]["yaw"], j[1]["speed"]);

                    // Previous path data given to the Planner
                    vector<double> previous_path_x = j[1]["previous_path_x"];
                    vector<double> previous_path_y = j[1]["previous_path_y"];
                    // Previous path's end s and d values
                    double end_path_s = j[1]["end_path_s"];
                    double end_path_d = j[1]["end_path_d"];

                    // Sensor Fusion Data, a list of all other cars on the same side
                    //   of the road.
                    vector<vector<double>> sensor_fusion = j[1]["sensor_fusion"];

                    vector<VehicleState> vehicles_states;
                    for (vector<double> vehicle_state : sensor_fusion) {
                        VehicleState vehicleState(
                                (int)vehicle_state[0], vehicle_state[1],
                                vehicle_state[2], vehicle_state[3], vehicle_state[4],
                                vehicle_state[5], vehicle_state[6]
                        );
                        vehicles_states.push_back(vehicleState);
                    }

                    SystemState systemState(car_state, vehicles_states, previous_path_x, previous_path_y, end_path_s, end_path_d);


                    Path path = pathPlanner.generate_path(systemState);

                    json msgJson;
                    msgJson["next_x"] = path.x;
                    msgJson["next_y"] = path.y;

                    std::string msg = "42[\"control\"," + msgJson.dump() + "]";
                    ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
                }
            } else {
                // Manual driving
                std::string msg = "42[\"manual\",{}]";
                ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
            }
        }
    });

    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
        std::cout << "Connected!!!" << std::endl;
    });

    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
        ws.close();
        std::cout << "Disconnected" << std::endl;
    });

    int port = 4567;
    if (h.listen(port)) {
        std::cout << "Listening to port " << port << std::endl;
    } else {
        std::cerr << "Failed to listen to port" << std::endl;
        return -1;
    }

    h.run();
}