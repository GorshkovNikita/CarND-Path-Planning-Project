//
// Created by nikita on 20.06.19.
//

#include "PathPlannerProtocol.h"
#include "helpers.h"
#include "json.hpp"

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
                double car_x = j[1]["x"];
                double car_y = j[1]["y"];
                double car_s = j[1]["s"];
                double car_d = j[1]["d"];
                double car_yaw = j[1]["yaw"];
                double car_speed = j[1]["speed"];

                // Previous path data given to the Planner
                auto previous_path_x = j[1]["previous_path_x"];
                auto previous_path_y = j[1]["previous_path_y"];
                // Previous path's end s and d values
                double end_path_s = j[1]["end_path_s"];
                double end_path_d = j[1]["end_path_d"];

                // Sensor Fusion Data, a list of all other cars on the same side
                //   of the road.
                auto sensor_fusion = j[1]["sensor_fusion"];

                json msgJson;

                vector<double> next_x_vals;
                vector<double> next_y_vals;

                /**
                 * TODO: define a path made up of (x,y) points that the car will visit
                 *   sequentially every .02 seconds
                 */
                double dist_inc = 0.25;
                for (int i = 0; i < 50; ++i) {
                    next_x_vals.push_back(car_x + (dist_inc * i) * cos(deg2rad(car_yaw)));
                    next_y_vals.push_back(car_y + (dist_inc * i) * sin(deg2rad(car_yaw)));
                }

                msgJson["next_x"] = next_x_vals;
                msgJson["next_y"] = next_y_vals;

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