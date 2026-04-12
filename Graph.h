#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <map>
#include <limits>
using namespace std;
enum VehicleType {
    CAR,
    BICYCLE,
    WALKING
};

struct Edge {
    int destination;
    int weight;
     map<VehicleType, int> vehicleWeights; // Different weights for different vehicles
};

class Graph {
private:
     vector< vector<Edge>> adjacencyList;
     map<int,  string> nodeNames;
    int nodeCount;

public:
    Graph(int nodes);
    ~Graph();
    
    void addNode(int id, const  string& name);
    void addEdge(int source, int destination, int weight);
    void addBidirectionalEdge(int node1, int node2, int weight);
    void addEdgeWithVehicleWeights(int source, int destination, const  map<VehicleType, int>& weights);
    void addBidirectionalEdgeWithVehicleWeights(int node1, int node2, const  map<VehicleType, int>& weights);
    
    int getNodeCount() const;
     string getNodeName(int id) const;
     vector<Edge> getAdjacentEdges(int node) const;
    
    void printGraph() const;
     string getVehicleTypeName(VehicleType type) const;
};

#endif // GRAPH_H