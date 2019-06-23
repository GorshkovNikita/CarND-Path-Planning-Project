//
// Created by nikita on 20.06.19.
//

#include "PathPlannerProtocol.h"
#include "json.hpp"
#include "helpers.h"

using nlohmann::json;

string PathPlannerProtocol::processMessage(string_view data) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (data.size() && data.size() > 2 && data[0] == '4' && data[1] == '2') {

        auto s = hasData(data.data());

        if (s != "") {
            auto j = json::parse(s);

            string event = j[0].get<string>();

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

                auto msg = "42[\"control\"," + msgJson.dump() + "]";

                return msg;
            }
        } else {
            // Manual driving
            std::string msg = "42[\"manual\",{}]";
            return msg;
        }
    }
    return std::__cxx11::string();
}
