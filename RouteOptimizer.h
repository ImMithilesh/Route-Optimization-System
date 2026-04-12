#ifndef ROUTEOPTIMIZER_H
#define ROUTEOPTIMIZER_H

#include "Graph.h"
#include <vector>
#include <queue>

struct PathNode {
    int nodeId;
    int distance;
     vector<int> path;
};

class RouteOptimizer {
private:
    const Graph& graph;
    VehicleType currentVehicle;
    
public:
    RouteOptimizer(const Graph& g);
    
    void setVehicle(VehicleType type);
    VehicleType getVehicle() const;
    
     vector<int> findShortestPath(int start, int end);
    int getShortestDistance(int start, int end);
    
    void printRoute(const  vector<int>& path) const;
};

#endif // ROUTEOPTIMIZER_H