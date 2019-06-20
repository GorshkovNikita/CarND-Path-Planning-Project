//
// Created by nikita on 20.06.19.
//

#ifndef PATH_PLANNING_PATHPLANNERPROTOCOL_H
#define PATH_PLANNING_PATHPLANNERPROTOCOL_H

#include <string>
#include <string_view>
#include "PathPlanner.h"

using std::string;
using std::string_view;

class PathPlannerProtocol {
public:
    string processMessage(string_view data);

private:
    PathPlanner pathPlanner;
};


#endif //PATH_PLANNING_PATHPLANNERPROTOCOL_H
