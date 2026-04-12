#include "Graph.h"
#include <iostream>
using namespace std;

Graph::Graph(int nodes) : nodeCount(nodes) {
    adjacencyList.resize(nodes);
}

Graph::~Graph() {}

void Graph::addNode(int id, const string& name) {
    if (id >= 0 && id < nodeCount) {
        nodeNames[id] = name;
    }
}

void Graph::addEdge(int source, int destination, int weight) {
    if (source >= 0 && source < nodeCount && 
        destination >= 0 && destination < nodeCount) {
        adjacencyList[source].push_back({destination, weight});
    }
}

void Graph::addBidirectionalEdge(int node1, int node2, int weight) {
    addEdge(node1, node2, weight);
    addEdge(node2, node1, weight);
}

void Graph::addEdgeWithVehicleWeights(int source, int destination, const map<VehicleType, int>& weights) {
    if (source >= 0 && source < nodeCount && 
        destination >= 0 && destination < nodeCount) {
        Edge newEdge;
        newEdge.destination = destination;
        newEdge.weight = weights.at(CAR); // Default to car weight
        newEdge.vehicleWeights = weights;
        adjacencyList[source].push_back(newEdge);
    }
}

void Graph::addBidirectionalEdgeWithVehicleWeights(int node1, int node2, const map<VehicleType, int>& weights) {
    addEdgeWithVehicleWeights(node1, node2, weights);
    addEdgeWithVehicleWeights(node2, node1, weights);
}

int Graph::getNodeCount() const {
    return nodeCount;
}

string Graph::getNodeName(int id) const {
    auto it = nodeNames.find(id);
    if (it != nodeNames.end()) {
        return it->second;
    }
    return "Unknown";
}

vector<Edge> Graph::getAdjacentEdges(int node) const {
    if (node >= 0 && node < nodeCount) {
        return adjacencyList[node];
    }
    return vector<Edge>();
}

void Graph::printGraph() const {
    cout << "Graph Structure:\n";
    for (int i = 0; i < nodeCount; ++i) {
        cout << getNodeName(i) << " -> ";
        for (const auto& edge : adjacencyList[i]) {
            cout << getNodeName(edge.destination) << " (weight: " << edge.weight << ") ";
        }
        cout << endl;
    }
}

string Graph::getVehicleTypeName(VehicleType type) const {
    switch (type) {
        case CAR: return "Car";
        case BICYCLE: return "Bicycle";
        case WALKING: return "Walking";
        default: return "Unknown";
    }
}