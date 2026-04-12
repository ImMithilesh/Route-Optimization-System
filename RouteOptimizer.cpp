#include "RouteOptimizer.h"
#include <iostream>
#include <algorithm>

RouteOptimizer::RouteOptimizer(const Graph& g) : graph(g), currentVehicle(CAR) {}

void RouteOptimizer::setVehicle(VehicleType type) {
    currentVehicle = type;
}

VehicleType RouteOptimizer::getVehicle() const {
    return currentVehicle;
}

 vector<int> RouteOptimizer::findShortestPath(int start, int end) {
    int nodeCount = graph.getNodeCount();
     vector<int> distances(nodeCount,  numeric_limits<int>::max());
     vector<int> predecessors(nodeCount, -1);
     vector<bool> visited(nodeCount, false);
    
    distances[start] = 0;
    
    // Priority queue: (distance, node)
     priority_queue< pair<int, int>, 
                        vector< pair<int, int>>, 
                        greater< pair<int, int>>> pq;
    
    pq.push({0, start});
    
    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();
        
        if (visited[current]) {
            continue;
        }
        
        visited[current] = true;
        
        if (current == end) {
            break;
        }
        
        for (const auto& edge : graph.getAdjacentEdges(current)) {
            int neighbor = edge.destination;
            
            // Get weight based on current vehicle type
            int weight = edge.weight; // Default weight
            auto it = edge.vehicleWeights.find(currentVehicle);
            if (it != edge.vehicleWeights.end()) {
                weight = it->second;
            }
            
            if (!visited[neighbor] && distances[current] + weight < distances[neighbor]) {
                distances[neighbor] = distances[current] + weight;
                predecessors[neighbor] = current;
                pq.push({distances[neighbor], neighbor});
            }
        }
    }
    
    // Reconstruct path
     vector<int> path;
    if (distances[end] !=  numeric_limits<int>::max()) {
        int current = end;
        while (current != -1) {
            path.push_back(current);
            current = predecessors[current];
        }
         reverse(path.begin(), path.end());
    }
    
    return path;
}

int RouteOptimizer::getShortestDistance(int start, int end) {
     vector<int> path = findShortestPath(start, end);
    
    if (path.empty()) {
        return -1; // No path exists
    }
    
    int distance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int current = path[i];
        int next = path[i + 1];
        
        for (const auto& edge : graph.getAdjacentEdges(current)) {
            if (edge.destination == next) {
                // Get weight based on current vehicle type
                int weight = edge.weight; // Default weight
                auto it = edge.vehicleWeights.find(currentVehicle);
                if (it != edge.vehicleWeights.end()) {
                    weight = it->second;
                }
                distance += weight;
                break;
            }
        }
    }
    
    return distance;
}

void RouteOptimizer::printRoute(const  vector<int>& path) const {
    if (path.empty()) {
         cout << "No route found!" <<  endl;
        return;
    }
    
     cout << "Optimal Route (" << graph.getVehicleTypeName(currentVehicle) << "): ";
    for (size_t i = 0; i < path.size(); ++i) {
         cout << graph.getNodeName(path[i]);
        if (i < path.size() - 1) {
             cout << " -> ";
        }
    }
     cout <<  endl;
    
    int distance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int current = path[i];
        int next = path[i + 1];
        
        for (const auto& edge : graph.getAdjacentEdges(current)) {
            if (edge.destination == next) {
                // Get weight based on current vehicle type
                int weight = edge.weight; // Default weight
                auto it = edge.vehicleWeights.find(currentVehicle);
                if (it != edge.vehicleWeights.end()) {
                    weight = it->second;
                }
                distance += weight;
                break;
            }
        }
    }
    
     cout << "Total Distance: " << distance << " units" <<  endl;
}