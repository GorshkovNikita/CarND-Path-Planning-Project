//
// Created by nikita on 20.06.19.
//

#include <string>
#include <sstream>
#include <fstream>
#include "HighwayMap.h"

using std::string;
using std::ifstream;

HighwayMap::HighwayMap() {
    string map_filename = "../data/highway_map.csv";
    ifstream map_ifstream(map_filename.c_str(), std::ifstream::in);

    string line;
    while (getline(map_ifstream, line)) {
        std::istringstream iss(line);
        double x;
        double y;
        float s;
        float d_x;
        float d_y;
        iss >> x;
        iss >> y;
        iss >> s;
        iss >> d_x;
        iss >> d_y;
        waypoints_x.push_back(x);
        waypoints_y.push_back(y);
        waypoints_s.push_back(s);
        waypoints_dx.push_back(d_x);
        waypoints_dy.push_back(d_y);
    }
}
